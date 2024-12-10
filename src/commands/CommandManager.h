#pragma once

#include <memory>
#include <stack>

#include "Command.h"

namespace command {

class CommandManager {
  std::stack<std::shared_ptr<Command>> doneCommands;
  std::stack<std::shared_ptr<Command>> undoneCommands;

 public:
  void addCommand(std::shared_ptr<Command> newCmd);

  void undo();
  void redo();
};

}  // namespace command
