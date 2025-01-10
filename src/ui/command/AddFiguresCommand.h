#pragma once

#include <memory>

#include "../../figure/Figure.h"
#include "../../figure/FigureGroup.h"
#include "Command.h"

namespace command {

class AddFiguresCommand : public Command {
  std::shared_ptr<figure::FigureGroup> parent;
  std::vector<std::shared_ptr<figure::Figure>> figs;

 public:
  AddFiguresCommand(std::shared_ptr<figure::FigureGroup> parent,
                    std::vector<std::shared_ptr<figure::Figure>> figs)
      : parent(std::move(parent)), figs(std::move(figs)) {}
  ~AddFiguresCommand() override = default;

  void execute() override {
    for (auto fig : figs)
      parent->addChild(fig);
  }

  void unexecute() override {
    for (auto fig : figs)
      parent->removeChild(fig);
  }
};

}  // namespace command
