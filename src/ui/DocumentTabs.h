#pragma once

#include <filesystem>
#include <memory>
#include <string>

#include "Widget.h"
#include "command/Command.h"

namespace ui {

class DocumentTabs : public Widget {
  std::filesystem::path openedFilePath;
  std::shared_ptr<command::Command<std::filesystem::path>> openCommand;

 public:
  ~DocumentTabs() override = default;

  void update() override;

  void setOpenedFile(std::string newName);

  void setOpenCommand(
      std::shared_ptr<command::Command<std::filesystem::path>> command);
};

}  // namespace ui
