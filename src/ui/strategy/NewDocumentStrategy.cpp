#include "NewDocumentStrategy.h"

#include <format>

#include "../../Document.h"

ui::strategy::NewDocumentStrategy::NewDocumentStrategy(
    std::shared_ptr<DocumentTabs> tabs)
    : tabs(std::move(tabs)) {}

void ui::strategy::NewDocumentStrategy::execute() {
  // TODO use actual filepath selection dialog to set the filepath
  auto filePath = std::filesystem::current_path() /
                  std::format("new_{:02}", newNameCounter++);

  // TODO set some info if needed
  auto doc = Document::getDocument(filePath);
  doc->setDimenstions({200, 300});

  if (tabs)
    tabs->setOpenedFile(filePath);
}
