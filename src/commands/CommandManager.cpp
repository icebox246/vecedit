#include "CommandManager.h"

void command::CommandManager::addCommand(std::shared_ptr<Command> newCmd) {
  doneCommands.emplace(std::move(newCmd));

  while (!undoneCommands.empty())
    undoneCommands.pop();
}

void command::CommandManager::addAndExecCommand(
    std::shared_ptr<Command> newCmd) {
  addCommand(newCmd);

  newCmd->execute();
}

void command::CommandManager::undo() {
  if (doneCommands.empty())
    return;

  auto cmd = doneCommands.top();
  cmd->unexecute();
  doneCommands.pop();
  undoneCommands.push(std::move(cmd));
}

void command::CommandManager::redo() {
  if (undoneCommands.empty())
    return;

  auto cmd = undoneCommands.top();
  cmd->execute();
  undoneCommands.pop();
  doneCommands.push(std::move(cmd));
}
