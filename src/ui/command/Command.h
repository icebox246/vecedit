#pragma once

namespace ui::command {

template <typename... Args>
class Command {
 public:
  virtual ~Command() = default;

  virtual void execute(Args... args) = 0;
};

}  // namespace ui::command
