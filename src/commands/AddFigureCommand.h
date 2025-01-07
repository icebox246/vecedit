#pragma once

#include <memory>

#include "../figure/Figure.h"
#include "../figure/FigureGroup.h"
#include "Command.h"

namespace command {

class AddFigureCommand : public Command {
  std::shared_ptr<figure::FigureGroup> parent;
  std::shared_ptr<figure::Figure> fig;

 public:
  AddFigureCommand(std::shared_ptr<figure::FigureGroup> parent,
                   std::shared_ptr<figure::Figure> fig)
      : parent(std::move(parent)), fig(std::move(fig)) {}
  ~AddFigureCommand() override = default;

  void execute() override { parent->addChild(fig); }

  void unexecute() override { parent->removeChild(fig); }
};

}  // namespace command
