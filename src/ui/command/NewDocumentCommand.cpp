#include "NewDocumentCommand.h"

#include <format>

#include "../../Document.h"

ui::command::NewDocumentCommand::NewDocumentCommand(
    std::shared_ptr<DocumentTabs> tabs)
    : tabs(std::move(tabs)) {}

void ui::command::NewDocumentCommand::execute() {
  auto fileName = std::format("new_{:02}", newNameCounter++);

  // TODO set some info if needed
  auto doc = Document::getDocument(fileName);
  doc->setDimenstions({200, 300});

  if (tabs)
    tabs->setOpenedFile(fileName);
}
