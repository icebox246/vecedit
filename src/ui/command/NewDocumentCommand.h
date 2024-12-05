#pragma once

#include <memory>

#include "../DocumentTabs.h"
#include "Command.h"

namespace ui::command {

class NewDocumentCommand : public Command<> {
  std::shared_ptr<DocumentTabs> tabs;
  int newNameCounter = 0;

 public:
  NewDocumentCommand(std::shared_ptr<DocumentTabs> tabs);
  ~NewDocumentCommand() override = default;

  void execute() override;
};

}  // namespace ui::command
