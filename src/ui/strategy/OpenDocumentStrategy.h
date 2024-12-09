#pragma once

#include <memory>

#include "../Editor.h"
#include "Strategy.h"

namespace ui::strategy {

class OpenDocumentStrategy : public Strategy<std::filesystem::path> {
  std::shared_ptr<Editor> editor;

 public:
  OpenDocumentStrategy(std::shared_ptr<Editor> editor);
  ~OpenDocumentStrategy() override = default;

  void execute(std::filesystem::path docName) override;
};

}  // namespace ui::strategy
