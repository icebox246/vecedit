#pragma once

#include <functional>

#include "Strategy.h"

namespace ui::strategy {

template <typename... Args>
class FunctorStrategy : public Strategy<Args...> {
  std::function<void(Args...)> f;

 public:
  FunctorStrategy(std::function<void(Args...)>&& f) : f(std::move(f)) {}
  virtual ~FunctorStrategy() = default;

  void execute(Args... args) override { f(args...); }
};

}  // namespace ui::strategy
