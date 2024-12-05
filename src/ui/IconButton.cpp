#include "IconButton.h"

ui::IconButton::IconButton(GuiIconName icon) : icon(icon) {}

void ui::IconButton::update() {
  if (GuiButton(rect, GuiIconText(icon, ""))) {
    if (command)
      command->execute();
  }
}

void ui::IconButton::setCommand(
    std::shared_ptr<command::Command<>> newCommand) {
  command = std::move(newCommand);
}
