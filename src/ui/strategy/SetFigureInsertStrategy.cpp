#include "SetFigureInsertStrategy.h"

#include <cassert>

ui::strategy::SetFigureInsertStrategy::SetFigureInsertStrategy(
    std::shared_ptr<Editor> editor,
    std::shared_ptr<figure::Figure> figurePrototype,
    GuiIconName icon)
    : editor(std::move(editor)),
      figurePrototype(std::move(figurePrototype)),
      icon(icon) {
  assert(this->editor);
  assert(this->figurePrototype);
}

void ui::strategy::SetFigureInsertStrategy::execute() {
  editor->setMode(Editor::Mode::Insert);
  editor->setFigurePrototype(figurePrototype);
  editor->setCursorIcon(icon);
}
