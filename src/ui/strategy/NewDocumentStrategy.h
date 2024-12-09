#pragma once

#include <memory>

#include "../DocumentTabs.h"
#include "Strategy.h"

namespace ui::strategy {

class NewDocumentStrategy : public Strategy<> {
  std::shared_ptr<DocumentTabs> tabs;
  int newNameCounter = 0;

 public:
  NewDocumentStrategy(std::shared_ptr<DocumentTabs> tabs);
  ~NewDocumentStrategy() override = default;

  void execute() override;
};

}  // namespace ui::strategy
