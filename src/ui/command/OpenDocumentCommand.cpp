#include "OpenDocumentCommand.h"

#include <cassert>

ui::command::OpenDocumentCommand::OpenDocumentCommand(
    std::shared_ptr<Editor> editor)
    : editor(editor) {
  assert(editor);
}

void ui::command::OpenDocumentCommand::execute(std::filesystem::path docName) {
  auto doc = Document::getDocument(docName);

  editor->setDocument(std::move(doc));
}
