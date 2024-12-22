#pragma once

#include <memory>

#include "../Editor.h"
#include "Strategy.h"

namespace ui::strategy {

class OpenDocumentStrategy : public Strategy<std::shared_ptr<Document>> {
  std::shared_ptr<Editor> editor;

 public:
  OpenDocumentStrategy(std::shared_ptr<Editor> editor);
  ~OpenDocumentStrategy() override = default;

  void execute(std::shared_ptr<Document> doc) override;
};

}  // namespace ui::strategy
