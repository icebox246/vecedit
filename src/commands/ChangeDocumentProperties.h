#pragma once

#include <memory>

#include "../Document.h"
#include "Command.h"

namespace command {

class ChangeDocumentPropertiesCommand : public Command {
  std::shared_ptr<Document> doc;

  std::filesystem::path oldPath;
  Vector2 oldDimensions;

  std::filesystem::path newPath;
  Vector2 newDimensions;

 public:
  ChangeDocumentPropertiesCommand(std::shared_ptr<Document> doc,
                                  std::filesystem::path newPath,
                                  Vector2 newDimensions)
      : doc(std::move(doc)), newPath(newPath), newDimensions(newDimensions) {}
  ~ChangeDocumentPropertiesCommand() override = default;

  void execute() override {
    oldPath = doc->getFilePath();
    oldDimensions = doc->getDimensions();

    doc->setFilePath(newPath);
    doc->setDimenstions(newDimensions);
  }

  void unexecute() override {
    doc->setFilePath(oldPath);
    doc->setDimenstions(oldDimensions);
  }
};

}  // namespace command
