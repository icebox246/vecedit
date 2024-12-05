#pragma once

#include <memory>

#include "../Editor.h"
#include "Command.h"

namespace ui::command {

class OpenDocumentCommand : public Command<std::string_view> {
  std::shared_ptr<Editor> editor;
  int newNameCounter = 0;

 public:
  OpenDocumentCommand(std::shared_ptr<Editor> editor);
  ~OpenDocumentCommand() override = default;

  void execute(std::string_view docName) override;
};

}  // namespace ui::command
