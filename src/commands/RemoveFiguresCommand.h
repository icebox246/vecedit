#pragma once

#include <memory>

#include "../figure/FigureGroup.h"
#include "Command.h"

namespace command {

class RemoveFiguresCommand : public Command {
  struct PlaceBackInfo {
    std::shared_ptr<figure::FigureGroup> parent;
    std::size_t index;
    std::shared_ptr<figure::Figure> figure;
  };

  std::vector<std::shared_ptr<figure::Figure>> figures;
  std::vector<PlaceBackInfo> infos;

 public:
  RemoveFiguresCommand(std::vector<std::shared_ptr<figure::Figure>> figures)
      : figures(std::move(figures)) {}
  ~RemoveFiguresCommand() override = default;

  void execute() override {
    infos.clear();

    for (auto& f : figures) {
      auto p = f->getParent();
      auto i = p->getChildIndex(f);
      infos.push_back(PlaceBackInfo{p, i, f});
    }

    std::sort(infos.begin(), infos.end(),
              [](auto& a, auto& b) { return a.index < b.index; });

    for (auto& f : figures) {
      auto p = f->getParent();
      p->removeChild(f);
    }
  }

  void unexecute() override {
    for (auto& info : infos) {
      info.parent->addChild(info.figure, info.index);
    }
  }
};

}  // namespace command
