#pragma once

#include <raygui.h>
#include <memory>

#include "Widget.h"
#include "command/Command.h"

namespace ui {

class IconButton : public Widget {
  GuiIconName icon;
  std::shared_ptr<command::Command<>> command;

 public:
  IconButton(GuiIconName icon);
  void update() override;

  void setCommand(std::shared_ptr<command::Command<>> newCommand);
};

}  // namespace ui
