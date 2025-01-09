#pragma once

#include <memory>

#include "../../figure/Figure.h"
#include "../../figure/FigureGroup.h"
#include "Command.h"

namespace command {

class UngroupFiguresCommand : public Command {
  std::shared_ptr<figure::FigureGroup> parent;
  std::size_t oldIndex;
  std::shared_ptr<figure::FigureGroup> group;

 public:
  UngroupFiguresCommand(std::shared_ptr<figure::FigureGroup> group)
      : group(std::move(group)) {}
  ~UngroupFiguresCommand() override = default;

  void execute() override {
    parent = group->getParent();
    assert(parent);
    oldIndex = parent->getChildIndex(group);

    parent->removeChild(group);

    for (auto& c : group->getChildren()) {
      parent->addChild(c);
    }
  }

  void unexecute() override {
    for (auto& c : group->getChildren()) {
      parent->removeChild(c);
    }

    parent->addChild(group, oldIndex);
  }
};

}  // namespace command
