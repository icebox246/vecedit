#pragma once

#include <raygui.h>
#include <memory>

#include "strategy/Strategy.h"

namespace ui {

class KeyboardShortcut {
  std::shared_ptr<strategy::Strategy<>> strategy;
  int key, mod;

 public:
  KeyboardShortcut(int key, int mod = 0) : key(key), mod(mod) {}
  void update() {
    if (IsKeyPressed(key) && (mod == 0 || IsKeyDown(mod)))
      strategy->execute();
  }

  void setStrategy(std::shared_ptr<strategy::Strategy<>> newStrategy) {
    strategy = std::move(newStrategy);
  }
};

}  // namespace ui
