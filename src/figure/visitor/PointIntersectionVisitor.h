#pragma once

#include <raylib.h>
#include <cassert>

#include "FigureVisitor.h"

namespace figure::visitor {

class PointIntersectionVisitor : public FigureVisitor {
  Vector2 point;
  bool gotIntersection = false;

 public:
  PointIntersectionVisitor(Vector2 point);
  virtual ~PointIntersectionVisitor() = default;

  bool intersects();

  void visit(FigureGroup& group) override {
    assert(false && "TODO: unimplemented");
  }
  void visit(RectFigure& rect) override;
  void visit(CircleFigure& circle) override;
};

}  // namespace figure::visitor
