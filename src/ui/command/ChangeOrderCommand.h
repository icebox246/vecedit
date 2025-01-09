#pragma once

#include <memory>

#include "../../figure/FigureGroup.h"
#include "Command.h"

namespace command {

class ChangeOrderCommand : public Command {
  std::shared_ptr<figure::Figure> fig;
  int delta;
  std::size_t oldIndex, newIndex;

 public:
  ChangeOrderCommand(std::shared_ptr<figure::Figure> fig, int delta)
      : fig(std::move(fig)), delta(delta) {}
  ~ChangeOrderCommand() override = default;

  void execute() override {
    auto p = fig->getParent();
    if (!p)
      return;

    oldIndex = p->getChildIndex(fig);
    if (delta > 0 && oldIndex + delta >= p->getChildren().size())
      newIndex = oldIndex;
    else if (delta < 0 && -delta > oldIndex)
      newIndex = oldIndex;
    else
      newIndex = oldIndex + delta;

    p->removeChild(fig);
    p->addChild(fig, newIndex);
  }

  void unexecute() override {
    auto p = fig->getParent();
    if (!p)
      return;

    p->removeChild(fig);
    p->addChild(fig, oldIndex);
  }
};

}  // namespace command
