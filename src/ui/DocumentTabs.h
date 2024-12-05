#pragma once

#include <memory>
#include <string>

#include "Widget.h"
#include "command/Command.h"

namespace ui {

class DocumentTabs : public Widget {
  std::string openedFileName;
  std::shared_ptr<command::Command<std::string_view>> openCommand;

 public:
  ~DocumentTabs() override = default;

  void update() override;

  void setOpenedFile(std::string newName);

  void setOpenCommand(
      std::shared_ptr<command::Command<std::string_view>> command);
};

}  // namespace ui
