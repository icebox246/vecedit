#include "Editor.h"

#include <raygui.h>
#include <raymath.h>
#include <format>
#include <utility>

#include "../commands/AddFigureCommand.h"
#include "../commands/ChangeOrderCommand.h"
#include "../commands/GroupFiguresCommand.h"
#include "../commands/MovePointCommand.h"
#include "../figure/Figure.h"
#include "../figure/visitor/PointIntersectionVisitor.h"
#include "../figure/visitor/RendererVisitor.h"
#include "../figure/visitor/SvgSerializerVisitor.h"
#include "../util.h"

namespace {
constexpr auto PropsPanelWidth = 300;
constexpr auto HierarchyPanelWidth = 200;
}  // namespace

ui::Editor::Editor()
    : propsPanel(std::make_shared<FigurePropertiesPanel>()),
      hierarchyPanel(std::make_shared<FigureHierarchyPanel>()) {
  resetCamera();
}

void ui::Editor::update() {
  if (!doc) {
    DrawRectangleRec(rect, RAYWHITE);

    Rectangle r = {rect.x + rect.width / 2 - 100, rect.y + rect.height / 2 - 10,
                   200, 20};

    GuiLabel(r, GuiIconText(ICON_FILE_ADD, "Create new document"));
    return;
  }

  doc->getRoot()->updateParent();

  if (isFocused()) {
    if (IsKeyDown(KEY_LEFT_CONTROL)) {
      camera.zoom *= 1 + GetMouseWheelMoveV().y * 0.05;
    } else if (!isOnMaxOS() && IsKeyDown(KEY_LEFT_SHIFT)) {
      camera.target.x += GetMouseWheelMoveV().y * -15 / camera.zoom;
    } else {
      camera.target += GetMouseWheelMoveV() * -15 / camera.zoom;
    }
  }

  BeginScissorMode(rect.x + HierarchyPanelWidth, rect.y,
                   rect.width - PropsPanelWidth - HierarchyPanelWidth,
                   rect.height);
  ClearBackground(GRAY);
  if (isFocused()) {
    DrawRectangleLines(rect.x + 1, rect.y + 1, rect.width - 1 - PropsPanelWidth,
                       rect.height - 1, BLUE);
  }
  BeginMode2D(camera);

  {
    DrawRectangleV({5, 5}, doc->getDimenstions(), DARKGRAY);
    DrawRectangleV({0, 0}, doc->getDimenstions(), WHITE);

    auto renderer = figure::visitor::RendererVisitor();
    doc->getRoot()->accept(renderer);
  }

  switch (mode) {
    case Mode::Select:
      processModeSelect();
      break;
    case Mode::Insert:
      processModeInsert();
      break;
  }

  EndMode2D();

  {
    Rectangle r = {rect.x + HierarchyPanelWidth, rect.y + rect.height - 20,
                   rect.width - PropsPanelWidth - HierarchyPanelWidth, 20};

    std::string modeString;
    switch (mode) {
      case Mode::Select:
        modeString = "SELECT";
        break;
      case Mode::Insert:
        modeString = "INSERT";
        break;
    }

    auto cursor = getCursorPos();

    auto path = doc->getFilePath();

    auto statusLine =
        std::format("Mode: {}  |  File: {}  |  Cursor: {:7.2f}, {:7.2f}",
                    modeString, path.string(), cursor.x, cursor.y);

    GuiStatusBar(r, statusLine.c_str());
  }

  GuiDrawIcon(cursorIcon, GetMouseX() + 10, GetMouseY() + 20, 1, DARKGRAY);

  EndScissorMode();

  propsPanel->update();
  hierarchyPanel->update();
}

void ui::Editor::setRect(const Rectangle& rect) {
  Widget::setRect(rect);

  camera.offset =
      Vector2{rect.x, rect.y} +
      Vector2{rect.width - PropsPanelWidth + HierarchyPanelWidth, rect.height} *
          0.5f;

  propsPanel->setRect({rect.x + rect.width - PropsPanelWidth, rect.y,
                       PropsPanelWidth, rect.height});

  hierarchyPanel->setRect({rect.x, rect.y, HierarchyPanelWidth, rect.height});
}

void ui::Editor::setDocument(std::shared_ptr<Document> newDoc) {
  hierarchyPanel->setEditor(shared_from_this());
  auto oldDoc = std::exchange(this->doc, newDoc);

  selectFigure(nullptr);

  if (!oldDoc)
    resetCamera();

  propsPanel->setDocument(doc);
  hierarchyPanel->setDocument(doc);
}

void ui::Editor::resetCamera() {
  camera.zoom = 1;
  if (doc) {
    camera.target = doc->getDimenstions() * 0.5f;
  }
}

void ui::Editor::setMode(Mode newMode) {
  mode = newMode;
}

void ui::Editor::setFigurePrototype(std::shared_ptr<figure::Figure> newProto) {
  figurePrototype = std::move(newProto);
}

void ui::Editor::setCursorIcon(GuiIconName icon) {
  cursorIcon = icon;
}

bool ui::Editor::isFocused() {
  auto realRect = Rectangle{rect.x + HierarchyPanelWidth, rect.y,
                            rect.width - PropsPanelWidth - HierarchyPanelWidth,
                            rect.height};
  return CheckCollisionPointRec(GetMousePosition(), realRect);
}

Vector2 ui::Editor::getCursorPos() {
  auto mouseScreen = GetMousePosition();
  auto mouse = GetScreenToWorld2D(mouseScreen, camera);
  return mouse;
}

void ui::Editor::processModeSelect() {
  if (!isFocused())
    return;

  auto cursor = getCursorPos();

  bool clickHandled = false;

  if (selectedFigure) {
    auto pointEditor = selectedFigure->makePointEditor();
    auto points = pointEditor->getEditPoints();

    if (draggedPointId && IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
      auto moveCmd = std::make_shared<command::MovePointCommand>(
          selectedFigure, *draggedPointId, mouseDragStartPos, cursor);

      doc->getCommandManager().addCommand(moveCmd);

      draggedPointId.reset();
    }

    for (auto& p : points) {
      Color fill;
      switch (p.type) {
        case figure::PointEditor::PointType::Origin:
          fill = ORANGE;
          break;
        case figure::PointEditor::PointType::Resize:
          fill = BLUE;
          break;
        case figure::PointEditor::PointType::HiddenClickable:
          fill = ColorAlpha(BLACK, 0);
          break;
      }

      auto radius = 5 / camera.zoom;

      DrawCircleV(p.pos, radius, fill);

      Color stroke = BLACK;
      if (Vector2DistanceSqr(p.pos, cursor) <= radius * radius) {
        stroke = YELLOW;

        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
          clickHandled = true;
          draggedPointId = p.id;
          mouseDragStartPos = cursor;
        }
      }

      DrawCircleLinesV(p.pos, radius, stroke);

      if (draggedPointId == p.id) {
        pointEditor->updatePointPosition(p.id, cursor);
      }
    }
  }

  if (!clickHandled && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
    figure::visitor::PointIntersectionVisitor intersectionVisitor(cursor);
    doc->getRoot()->accept(intersectionVisitor);

    if (intersectionVisitor.intersects()) {
      selectFigure(intersectionVisitor.getIntersectingFigure(),
                   IsKeyDown(KEY_LEFT_SHIFT));
    } else {
      selectFigure(nullptr);
    }
  }
}

void ui::Editor::processModeInsert() {
  if (!isFocused())
    return;

  if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
    auto newFigure = figurePrototype->clone();
    auto cursor = getCursorPos();
    newFigure->setOrigin(cursor);

    // TODO: support other parents than root of document
    auto addCmd =
        std::make_shared<command::AddFigureCommand>(doc->getRoot(), newFigure);
    addCmd->execute();
    doc->getCommandManager().addCommand(addCmd);

    selectFigure(newFigure);

    TraceLog(
        LOG_DEBUG,
        std::format("Placed figure at ({},{})", cursor.x, cursor.y).c_str());
  }
}

void ui::Editor::selectFigure(std::shared_ptr<figure::Figure> figure,
                              bool multi) {
  if (multi && selectedFigure) {
    if (!transientGroup) {
      auto oldFig = selectedFigure;

      transientGroup = std::make_shared<figure::FigureGroup>();
      transientGroup->addChild(selectedFigure);
      selectFigure(transientGroup);
      hierarchyPanel->markFigure(oldFig);
    }

    transientGroup->addChild(figure);
    hierarchyPanel->markFigure(figure);

    return;
  }

  if (figure != transientGroup) {
    transientGroup.reset();
  }
  propsPanel->setFigure(figure);

  hierarchyPanel->unmarkFigures();
  if (figure) {
    hierarchyPanel->markFigure(figure);
  }

  selectedFigure = std::move(figure);
  draggedPointId = {};
}

void ui::Editor::undo() {
  if (doc)
    doc->getCommandManager().undo();
}

void ui::Editor::redo() {
  if (doc)
    doc->getCommandManager().redo();
}

void ui::Editor::groupFigures() {
  if (!transientGroup || !doc)
    return;

  auto groupCmd = std::make_shared<command::GroupFiguresCommand>(
      transientGroup->getChildren().front()->getParent(), transientGroup);

  doc->getCommandManager().addAndExecCommand(std::move(groupCmd));

  selectFigure(std::move(transientGroup));
}

void ui::Editor::changeFigureOrder(int delta) {
  if (!selectedFigure || !doc || transientGroup)
    return;

  auto changeOrderCmd =
      std::make_shared<command::ChangeOrderCommand>(selectedFigure, delta);

  doc->getCommandManager().addAndExecCommand(std::move(changeOrderCmd));
}

void ui::Editor::saveDocument() {
  if (!doc)
    return;

  figure::visitor::SvgSerializerVisitor serializer(doc->getDimenstions());

  doc->getRoot()->accept(serializer);

  serializer.saveToFile(doc->getFilePath());
}
