#include "Editor.h"

#include <raygui.h>
#include <raymath.h>
#include <format>
#include <ranges>
#include <utility>

#include "../commands/AddFigureCommand.h"
#include "../commands/MovePointCommand.h"
#include "../figure/visitor/PointIntersectionVisitor.h"
#include "../figure/visitor/RendererVisitor.h"
#include "../util.h"

namespace {
constexpr auto PropsPanelWidth = 300;
}

ui::Editor::Editor() : propsPanel(std::make_shared<FigurePropertiesPanel>()) {
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

  if (isFocused()) {
    if (IsKeyDown(KEY_LEFT_CONTROL)) {
      camera.zoom *= 1 + GetMouseWheelMoveV().y * 0.05;
    } else if (!isOnMaxOS() && IsKeyDown(KEY_LEFT_SHIFT)) {
      camera.target.x += GetMouseWheelMoveV().y * -15 / camera.zoom;
    } else {
      camera.target += GetMouseWheelMoveV() * -15 / camera.zoom;
    }
  }

  BeginScissorMode(rect.x, rect.y, rect.width - PropsPanelWidth, rect.height);
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
    for (const auto& f : doc->getFigures()) {
      f->accept(renderer);
    }
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
    Rectangle r = {rect.x, rect.y + rect.height - 20,
                   rect.width - PropsPanelWidth, 20};

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
}

void ui::Editor::setRect(const Rectangle& rect) {
  Widget::setRect(rect);

  camera.offset = Vector2{rect.x, rect.y} +
                  Vector2{rect.width - PropsPanelWidth, rect.height} * 0.5f;

  propsPanel->setRect({rect.x + rect.width - PropsPanelWidth, rect.y,
                       PropsPanelWidth, rect.height});
}

void ui::Editor::setDocument(std::shared_ptr<Document> newDoc) {
  auto oldDoc = std::exchange(this->doc, newDoc);

  selectFigure(nullptr);

  if (!oldDoc)
    resetCamera();
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
  auto realRect =
      Rectangle{rect.x, rect.y, rect.width - PropsPanelWidth, rect.height};
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
    bool selectionFound = false;

    figure::visitor::PointIntersectionVisitor intersectionVisitor(cursor);
    for (auto fig : std::ranges::reverse_view(doc->getFigures())) {
      fig->accept(intersectionVisitor);

      if (intersectionVisitor.intersects()) {
        selectFigure(fig);
        selectionFound = true;
        break;
      }
    }

    if (!selectionFound)
      selectFigure(nullptr);
  }
}

void ui::Editor::processModeInsert() {
  if (!isFocused())
    return;

  if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
    auto newFigure = figurePrototype->clone();
    auto cursor = getCursorPos();
    newFigure->setOrigin(cursor);

    auto addCmd = std::make_shared<command::AddFigureCommand>(doc, newFigure);
    addCmd->execute();
    doc->getCommandManager().addCommand(addCmd);

    selectFigure(newFigure);

    TraceLog(
        LOG_DEBUG,
        std::format("Placed figure at ({},{})", cursor.x, cursor.y).c_str());
  }
}

void ui::Editor::selectFigure(std::shared_ptr<figure::Figure> figure) {
  propsPanel->setFigure(figure);
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
