#pragma once

#include <cassert>
#include <memory>

#include "../../figure/Figure.h"
#include "Command.h"

namespace command {

class ToggleVisibilityCommand : public Command {
  std::shared_ptr<figure::Figure> figure;

 public:
  ToggleVisibilityCommand(std::shared_ptr<figure::Figure> figure)
      : figure((assert(figure), std::move(figure))) {}
  ~ToggleVisibilityCommand() override = default;

  void execute() override { figure->setVisible(!figure->getVisible()); }

  void unexecute() override { figure->setVisible(!figure->getVisible()); }
};

}  // namespace command
