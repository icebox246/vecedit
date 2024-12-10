#pragma once

#include <memory>

#include "../Editor.h"
#include "Strategy.h"

namespace ui::strategy {

class UndoStrategy : public Strategy<> {
  std::shared_ptr<Editor> editor;

 public:
  UndoStrategy(std::shared_ptr<Editor> editor) : editor(std::move(editor)) {}
  ~UndoStrategy() override = default;

  void execute() override { editor->undo(); }
};

}  // namespace ui::strategy
