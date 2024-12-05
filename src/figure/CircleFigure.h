#pragma once

#include "FigureBase.h"

namespace figure {

class CircleFigure : public FigureBase<CircleFigure> {
  float radius;

 public:
  ~CircleFigure() override = default;

  void setRadius(float newRadius);
  float getRadius();

  std::shared_ptr<PointEditor> makePointEditor() override;
};

}  // namespace figure
