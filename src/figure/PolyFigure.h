#pragma once

#include "FigureBase.h"
#include "adapter/PolyFigurePointEditor.h"

#include <raymath.h>

namespace figure {

class PolyFigure : public FigureBase<PolyFigure> {
  std::vector<Vector2> pointOffsets;

 public:
  PolyFigure(std::size_t pointCount) : pointOffsets(pointCount - 1) {}
  ~PolyFigure() override = default;

  std::size_t getPointCount() { return pointOffsets.size() + 1; }

  void initializeRegularPolygon(float radius) {
    Vector2 center = {0, radius};
    for (int i = 1; i < getPointCount(); i++) {
      float alpha = -i * PI * 2 / getPointCount();
      pointOffsets[i - 1] = center + Vector2{sinf(alpha), -cosf(alpha)} * radius;
    }
  }

  void setOffset(std::size_t index, Vector2 value) {
    pointOffsets[index] = value;
  }

  const std::vector<Vector2>& getOffsets() const { return pointOffsets; }

  std::shared_ptr<PointEditor> makePointEditor() override {
    return std::make_shared<adapter::PolyFigurePointEditor>(shared_from_this());
  }
};

}  // namespace figure
