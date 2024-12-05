#pragma once

#include "FigureBase.h"

namespace figure {

class RectFigure : public FigureBase<RectFigure> {
  Vector2 dimensions;

 public:
  ~RectFigure() override = default;

  void setDimensions(Vector2 newDimensions);
  Rectangle getRectangle();

  std::shared_ptr<PointEditor> makePointEditor() override;
};

}  // namespace figure
