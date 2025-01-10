#include "FigureHierarchyPanel.h"

#include <ranges>

#include "../ui/command/ToggleVisibilityCommand.h"
#include "../figure/CircleFigure.h"
#include "../figure/PolyFigure.h"
#include "../figure/RectFigure.h"
#include "Editor.h"

namespace {

using namespace figure;

class HierarchyTreeRendererVisitor : public visitor::FigureVisitor {
  static constexpr auto ItemHeight = 20;
  static constexpr auto IndentWidth = 10;

  Rectangle rect;
  const std::unordered_set<std::shared_ptr<figure::Figure>>& markedFigures;
  std::shared_ptr<figure::Figure>& figureToSelect;
  std::shared_ptr<figure::Figure>& figureToToggleVisibility;
  Vector2 offset{0, 0};
  int indentLevel = 0;

 public:
  HierarchyTreeRendererVisitor(
      Rectangle rect,
      const std::unordered_set<std::shared_ptr<figure::Figure>>& markedFigures,
      std::shared_ptr<figure::Figure>& figureToSelect,
      std::shared_ptr<figure::Figure>& figureToToggleVisibility)
      : rect(rect),
        markedFigures(markedFigures),
        figureToSelect(figureToSelect),
        figureToToggleVisibility(figureToToggleVisibility) {}

  void visit(std::shared_ptr<FigureGroup> group) override {
    if (group->getParent()) {
      simpleFigVisit(group, "Group");
    } else {
      simpleFigVisit(group, "Root");
    }
    indentLevel++;
    offset.x += IndentWidth;
    for (auto c : std::ranges::reverse_view(group->getChildren())) {
      c->accept(*this);
    }
    offset.x -= IndentWidth;
    indentLevel--;
  }

  void visit(std::shared_ptr<RectFigure> rect) override {
    simpleFigVisit(rect, "Rectangle");
  }

  void visit(std::shared_ptr<CircleFigure> circle) override {
    simpleFigVisit(circle, "Circle");
  }

  void visit(std::shared_ptr<PolyFigure> poly) override {
    switch (poly->getPointCount()) {
      case 2:
        simpleFigVisit(poly, "Line");
        break;
      case 3:
        simpleFigVisit(poly, "Triangle");
        break;
      default:
        simpleFigVisit(poly, "Polygon");
        break;
    }
  }

 private:
  void simpleFigVisit(std::shared_ptr<Figure> fig, std::string name) {
    Rectangle r = {rect.x + offset.x, rect.y + offset.y,
                   rect.width - offset.x - ItemHeight, ItemHeight};
    if (GuiLabelButton(r, name.c_str())) {
      figureToSelect = fig;
    }
    if (GuiLabelButton(
            Rectangle{rect.x + rect.width - ItemHeight, rect.y + offset.y,
                      ItemHeight, ItemHeight},
            GuiIconText(fig->getVisible() ? ICON_EYE_ON : ICON_EYE_OFF, ""))) {
      figureToToggleVisibility = fig;
    }

    if (markedFigures.contains(fig)) {
      DrawRectangleLinesEx(r, 1, SKYBLUE);
    }
    for (int i = 0; i < indentLevel; i++) {
      DrawLine(rect.x + 4 + IndentWidth * i, rect.y + offset.y,
               rect.x + 4 + IndentWidth * i, rect.y + offset.y + ItemHeight,
               GRAY);
    }

    offset.y += ItemHeight;
  }
};

}  // namespace

void ui::FigureHierarchyPanel::update() {
  if (!doc)
    return;

  GuiPanel(rect, "Hierarchy");

  auto innerRect = rect;
  innerRect.y += 32;
  innerRect.height -= 32;
  innerRect.x += 4;
  innerRect.width -= 8;
  std::shared_ptr<Figure> figureToSelect = nullptr;
  std::shared_ptr<Figure> figureToToggleVisibility = nullptr;
  HierarchyTreeRendererVisitor vis(innerRect, markedFigures, figureToSelect,
                                   figureToToggleVisibility);

  figureToSelect = nullptr;

  doc->getRoot()->accept(vis);

  if (figureToSelect) {
    auto ownEditor = editor.lock();
    assert(ownEditor);
    ownEditor->selectFigure(figureToSelect, IsKeyDown(KEY_LEFT_SHIFT));
    ownEditor->setMode(Editor::Mode::Select);
  }

  if (figureToToggleVisibility)
    doc->getCommandManager().addAndExecCommand(
        std::make_shared<command::ToggleVisibilityCommand>(
            figureToToggleVisibility));
}

void ui::FigureHierarchyPanel::setDocument(std::shared_ptr<Document> newDoc) {
  doc = std::move(newDoc);
  unmarkFigures();
}

void ui::FigureHierarchyPanel::markFigure(std::shared_ptr<figure::Figure> fig) {
  markedFigures.insert(fig);
}

void ui::FigureHierarchyPanel::unmarkFigures() {
  markedFigures.clear();
}

void ui::FigureHierarchyPanel::setEditor(
    std::weak_ptr<class Editor> newEditor) {
  editor = newEditor;
}
