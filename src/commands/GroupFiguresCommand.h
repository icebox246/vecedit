#pragma once

#include <memory>

#include "../figure/Figure.h"
#include "../figure/FigureGroup.h"
#include "Command.h"

namespace command {

class GroupFiguresCommand : public Command {
  struct OldParentInfo {
    std::shared_ptr<figure::FigureGroup> parent;
    std::size_t index;
    std::shared_ptr<figure::Figure> figure;
  };

  std::shared_ptr<figure::FigureGroup> parent;
  std::shared_ptr<figure::FigureGroup> group;
  std::vector<OldParentInfo> infos;

 public:
  GroupFiguresCommand(std::shared_ptr<figure::FigureGroup> parent,
                      std::shared_ptr<figure::FigureGroup> group)
      : parent(std::move(parent)), group(std::move(group)) {}
  ~GroupFiguresCommand() override = default;

  void execute() override {
    infos.clear();

    for (auto& f : group->getChildren()) {
      auto p = f->getParent();
      auto i = p->getChildIndex(f);
      infos.push_back(OldParentInfo{p, i, f});
    }

    std::sort(infos.begin(), infos.end(),
              [](auto& a, auto& b) { return a.index < b.index; });

    for (auto& f : group->getChildren()) {
      auto p = f->getParent();
      p->removeChild(f);
    }

    parent->addChild(group);
  }

  void unexecute() override {
    parent->removeChild(group);

    for (auto& info : infos) {
      info.parent->addChild(info.figure, info.index);
    }
  }
};

}  // namespace command
