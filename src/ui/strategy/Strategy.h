#pragma once

namespace ui::strategy {

template <typename... Args>
class Strategy {
 public:
  virtual ~Strategy() = default;

  virtual void execute(Args... args) = 0;
};

}  // namespace ui::strategy
