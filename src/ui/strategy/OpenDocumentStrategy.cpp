#include "OpenDocumentStrategy.h"

#include <cassert>

ui::strategy::OpenDocumentStrategy::OpenDocumentStrategy(
    std::shared_ptr<Editor> editor)
    : editor(editor) {
  assert(editor);
}

void ui::strategy::OpenDocumentStrategy::execute(std::filesystem::path docName) {
  auto doc = Document::getDocument(docName);

  editor->setDocument(std::move(doc));
}
