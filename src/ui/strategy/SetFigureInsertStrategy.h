#pragma once

#include <memory>

#include "../../figure/Figure.h"
#include "../Editor.h"
#include "Strategy.h"

namespace ui::strategy {

class SetFigureInsertStrategy : public Strategy<> {
  std::shared_ptr<Editor> editor;
  std::shared_ptr<figure::Figure> figurePrototype;
  GuiIconName icon;

 public:
  SetFigureInsertStrategy(std::shared_ptr<Editor> editor,
                          std::shared_ptr<figure::Figure> figurePrototype,
                          GuiIconName icon);
  ~SetFigureInsertStrategy() override = default;

  void execute() override;
};

}  // namespace ui::strategy
