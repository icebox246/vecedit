#pragma once

#include <memory>

#include "../Editor.h"
#include "Strategy.h"

namespace ui::strategy {

class SetSelectStrategy : public Strategy<> {
  std::shared_ptr<Editor> editor;

 public:
  SetSelectStrategy(std::shared_ptr<Editor> editor);
  ~SetSelectStrategy() override = default;

  void execute() override;
};

}  // namespace ui::strategy
