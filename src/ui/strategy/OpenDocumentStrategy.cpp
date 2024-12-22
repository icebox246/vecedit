#include "OpenDocumentStrategy.h"

#include <cassert>

ui::strategy::OpenDocumentStrategy::OpenDocumentStrategy(
    std::shared_ptr<Editor> editor)
    : editor(editor) {
  assert(editor);
}

void ui::strategy::OpenDocumentStrategy::execute(std::shared_ptr<Document> doc) {
  editor->setDocument(std::move(doc));
}
