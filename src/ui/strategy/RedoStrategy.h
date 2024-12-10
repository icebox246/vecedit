#pragma once

#include <memory>

#include "../Editor.h"
#include "Strategy.h"

namespace ui::strategy {

class RedoStrategy : public Strategy<> {
  std::shared_ptr<Editor> editor;

 public:
  RedoStrategy(std::shared_ptr<Editor> editor) : editor(std::move(editor)) {}
  ~RedoStrategy() override = default;

  void execute() override { editor->redo(); }
};

}  // namespace ui::strategy
