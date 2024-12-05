#pragma once

#include <memory>

#include "../PointEditor.h"
#include "../RectFigure.h"

namespace figure::adapter {

class RectFigurePointEditor : public PointEditor {
  std::shared_ptr<RectFigure> rect;

 public:
  ~RectFigurePointEditor() override = default;
  RectFigurePointEditor(std::shared_ptr<RectFigure> rect);

  std::vector<Point> getEditPoints() override;
  void updatePointPosition(std::size_t pointId, Vector2 newPos) override;
};

};  // namespace figure::adapter
