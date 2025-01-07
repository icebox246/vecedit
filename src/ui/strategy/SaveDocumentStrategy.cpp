#include "SaveDocumentStrategy.h"

ui::strategy::SaveDocumentStrategy::SaveDocumentStrategy(
    std::shared_ptr<Editor> editor)
    : editor(std::move(editor)) {}

void ui::strategy::SaveDocumentStrategy::execute() {
  editor->saveDocument();
}
