#pragma once

#include <raylib.h>

namespace ui {

class Widget {
 protected:
  Rectangle rect;

 public:
  virtual ~Widget() = default;

  virtual void update() = 0;
  virtual void setRect(const Rectangle& rect) { this->rect = rect; }
};

}  // namespace ui
