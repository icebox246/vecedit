#include "SetFigureInsertCommand.h"

#include <cassert>

ui::command::SetFigureInsertCommand::SetFigureInsertCommand(
    std::shared_ptr<Editor> editor,
    std::shared_ptr<figure::Figure> figurePrototype,
    GuiIconName icon)
    : editor(std::move(editor)),
      figurePrototype(std::move(figurePrototype)),
      icon(icon) {
  assert(this->editor);
  assert(this->figurePrototype);
}

void ui::command::SetFigureInsertCommand::execute() {
  editor->setMode(Editor::Mode::Insert);
  editor->setFigurePrototype(figurePrototype);
  editor->setCursorIcon(icon);
}
