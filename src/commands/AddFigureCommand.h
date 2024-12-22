#pragma once

#include <memory>

#include "../Document.h"
#include "../figure/Figure.h"
#include "Command.h"

namespace command {

class AddFigureCommand : public Command {
  std::shared_ptr<Document> doc;
  std::shared_ptr<figure::Figure> fig;

 public:
  AddFigureCommand(std::shared_ptr<Document> doc,
                   std::shared_ptr<figure::Figure> fig)
      : doc(std::move(doc)), fig(std::move(fig)) {}
  ~AddFigureCommand() override = default;

  void execute() override { doc->getRoot()->addChild(fig); }

  void unexecute() override { doc->getRoot()->removeChild(fig); }
};

}  // namespace command
