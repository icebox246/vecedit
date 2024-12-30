#pragma once

#include <memory>

#include "../Editor.h"
#include "Strategy.h"

namespace ui::strategy {

class SaveDocumentStrategy : public Strategy<> {
  std::shared_ptr<Editor> editor;
  int newNameCounter = 0;

 public:
  SaveDocumentStrategy(std::shared_ptr<Editor> editor);
  ~SaveDocumentStrategy() override = default;

  void execute() override;
};

}  // namespace ui::strategy
