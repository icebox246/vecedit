#pragma once

#include <memory>
#include <vector>

#include "Widget.h"

namespace ui {

class Toolbar : public Widget {
  std::vector<std::shared_ptr<Widget>> widgets;

 public:
  ~Toolbar() override = default;

  void update() override;
  void setRect(const Rectangle& rect) override;

  void addWidget(std::shared_ptr<Widget> tool);
};

}  // namespace ui
