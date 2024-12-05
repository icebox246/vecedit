#pragma once

#include <raylib.h>

#include "FigureVisitor.h"

namespace figure::visitor {

class PointIntersectionVisitor : public FigureVisitor {
  Vector2 point;
  bool gotIntersection = false;

 public:
  PointIntersectionVisitor(Vector2 point);
  virtual ~PointIntersectionVisitor() = default;

  bool intersects();

  void visit(RectFigure& rect) override;
  void visit(CircleFigure& circle) override;
};

}  // namespace figure::visitor
