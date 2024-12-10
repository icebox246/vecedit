#pragma once

#include <raygui.h>
#include <memory>
#include <optional>

#include "../Document.h"
#include "FigurePropertiesPanel.h"
#include "Widget.h"

namespace ui {

class Editor : Widget {
 public:
  enum class Mode { Select, Insert };

 private:
  std::shared_ptr<Document> doc;
  Camera2D camera = {};
  Mode mode = Mode::Select;
  std::shared_ptr<figure::Figure> figurePrototype;

  std::shared_ptr<figure::Figure> selectedFigure = {};
  std::optional<std::size_t> draggedPointId = {};
  Vector2 mouseDragStartPos;

  std::shared_ptr<FigurePropertiesPanel> propsPanel;

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

 private:
  bool isFocused();
  Vector2 getCursorPos();
  void processModeSelect();
  void processModeInsert();
  void selectFigure(std::shared_ptr<figure::Figure> figure);
};

}  // namespace ui
