#pragma once

#include <memory>

#include "../figure/Figure.h"
#include "Command.h"

namespace command {

class MovePointCommand : public Command {
  std::shared_ptr<figure::Figure> fig;
  std::size_t pointId;
  Vector2 oldPos, newPos;

 public:
  MovePointCommand(std::shared_ptr<figure::Figure> fig,
                   std::size_t pointId,
                   Vector2 oldPos,
                   Vector2 newPos)
      : fig(std::move(fig)), pointId(pointId), oldPos(oldPos), newPos(newPos) {}
  ~MovePointCommand() override = default;

  void execute() override {
    auto editor = fig->makePointEditor();
    editor->updatePointPosition(pointId, newPos);
  }

  void unexecute() override {
    auto editor = fig->makePointEditor();
    editor->updatePointPosition(pointId, oldPos);
  }
};

}  // namespace command
