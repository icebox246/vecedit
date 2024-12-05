#pragma once

#include <memory>

#include "../Editor.h"
#include "Command.h"

namespace ui::command {

class OpenDocumentCommand : public Command<std::filesystem::path> {
  std::shared_ptr<Editor> editor;
  int newNameCounter = 0;

 public:
  OpenDocumentCommand(std::shared_ptr<Editor> editor);
  ~OpenDocumentCommand() override = default;

  void execute(std::filesystem::path docName) override;
};

}  // namespace ui::command
