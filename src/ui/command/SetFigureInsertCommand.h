#pragma once

#include <memory>

#include "../../figure/Figure.h"
#include "../Editor.h"
#include "Command.h"

namespace ui::command {

class SetFigureInsertCommand : public Command<> {
  std::shared_ptr<Editor> editor;
  std::shared_ptr<figure::Figure> figurePrototype;
  GuiIconName icon;

 public:
  SetFigureInsertCommand(std::shared_ptr<Editor> editor,
                         std::shared_ptr<figure::Figure> figurePrototype,
                         GuiIconName icon);
  ~SetFigureInsertCommand() override = default;

  void execute() override;
};

}  // namespace ui::command
