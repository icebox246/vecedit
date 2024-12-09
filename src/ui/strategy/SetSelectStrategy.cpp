#include "SetSelectStrategy.h"

#include <cassert>

ui::strategy::SetSelectStrategy::SetSelectStrategy(
    std::shared_ptr<Editor> editor)
    : editor(std::move(editor)) {
  assert(this->editor);
}

void ui::strategy::SetSelectStrategy::execute() {
  editor->setMode(Editor::Mode::Select);
  editor->setCursorIcon(ICON_NONE);
}
