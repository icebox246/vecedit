#include "IconButton.h"

ui::IconButton::IconButton(GuiIconName icon) : icon(icon) {}

void ui::IconButton::update() {
  if (GuiButton(rect, GuiIconText(icon, ""))) {
    if (strategy)
      strategy->execute();
  }
}

void ui::IconButton::setStrategy(
    std::shared_ptr<strategy::Strategy<>> newStrategy) {
  strategy = std::move(newStrategy);
}
