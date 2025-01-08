#pragma once

#include <memory>

#include "../PointEditor.h"

namespace figure {
class PolyFigure;
}

namespace figure::adapter {

class PolyFigurePointEditor : public PointEditor {
  std::shared_ptr<PolyFigure> poly;

 public:
  ~PolyFigurePointEditor() override = default;
  PolyFigurePointEditor(std::shared_ptr<PolyFigure> poly);

  std::vector<Point> getEditPoints() override;
  void updatePointPosition(std::size_t pointId, Vector2 newPos) override;
};

};  // namespace figure::adapter
