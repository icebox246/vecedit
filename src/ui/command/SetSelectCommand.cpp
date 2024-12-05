#include "SetSelectCommand.h"

#include <cassert>

ui::command::SetSelectCommand::SetSelectCommand(std::shared_ptr<Editor> editor)
    : editor(std::move(editor)) {
  assert(this->editor);
}

void ui::command::SetSelectCommand::execute() {
  editor->setMode(Editor::Mode::Select);
  editor->setCursorIcon(ICON_NONE);
}
