#pragma once

#include <memory>

#include "../PointEditor.h"
#include "../CircleFigure.h"

namespace figure::adapter {

class CircleFigurePointEditor : public PointEditor {
  std::shared_ptr<CircleFigure> circle;

 public:
  CircleFigurePointEditor(std::shared_ptr<CircleFigure> circle);
  ~CircleFigurePointEditor() override = default;

  std::vector<Point> getEditPoints() override;
  void updatePointPosition(std::size_t pointId, Vector2 newPos) override;
};

};  // namespace figure::adapter
