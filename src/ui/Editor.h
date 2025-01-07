#pragma once

#include <raygui.h>
#include <memory>
#include <optional>

#include "../Document.h"
#include "FigureHierarchyPanel.h"
#include "FigurePropertiesPanel.h"
#include "Widget.h"

namespace ui {

class Editor : public Widget, public std::enable_shared_from_this<Editor> {
 public:
  enum class Mode { Select, Insert };

 private:
  std::shared_ptr<Document> doc;
  Camera2D camera = {};
  Mode mode = Mode::Select;
  std::shared_ptr<figure::Figure> figurePrototype;

  std::shared_ptr<figure::Figure> selectedFigure = {};
  std::shared_ptr<figure::FigureGroup> transientGroup = {};
  std::optional<std::size_t> draggedPointId = {};
  Vector2 mouseDragStartPos;

  std::shared_ptr<FigurePropertiesPanel> propsPanel;
  std::shared_ptr<FigureHierarchyPanel> hierarchyPanel;

  GuiIconName cursorIcon = ICON_NONE;

 public:
  Editor();
  ~Editor() override = default;

  void update() override;
  void setRect(const Rectangle& rect) override;

  void setDocument(std::shared_ptr<Document> doc);
  void resetCamera();
  void setMode(Mode newMode);
  void setFigurePrototype(std::shared_ptr<figure::Figure> newProto);
  void setCursorIcon(GuiIconName icon);
  void undo();
  void redo();
  void groupFigures();
  void ungroupFigures();
  void changeFigureOrder(int delta);

  void saveDocument();

  void selectFigure(std::shared_ptr<figure::Figure> figure, bool multi = false);

 private:
  bool isFocused();
  Vector2 getCursorPos();
  void processModeSelect();
  void processModeInsert();
};

}  // namespace ui
