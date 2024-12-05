#pragma once

#include <memory>

#include "../Editor.h"
#include "Command.h"

namespace ui::command {

class SetSelectCommand : public Command<> {
  std::shared_ptr<Editor> editor;

 public:
  SetSelectCommand(std::shared_ptr<Editor> editor);
  ~SetSelectCommand() override = default;

  void execute() override;
};

}  // namespace ui::command
