#pragma once

#include <raygui.h>
#include <memory>

#include "Widget.h"
#include "strategy/Strategy.h"

namespace ui {

class IconButton : public Widget {
  GuiIconName icon;
  std::shared_ptr<strategy::Strategy<>> strategy;

 public:
  IconButton(GuiIconName icon);
  void update() override;

  void setStrategy(std::shared_ptr<strategy::Strategy<>> newStrategy);
};

}  // namespace ui
