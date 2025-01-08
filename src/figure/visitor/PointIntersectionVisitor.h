#pragma once

#include <raylib.h>
#include <cassert>
#include <memory>

#include "../Figure.h"
#include "FigureVisitor.h"

namespace figure::visitor {

class PointIntersectionVisitor : public FigureVisitor {
  Vector2 point;
  std::shared_ptr<figure::Figure> intersectingFigure;

 public:
  PointIntersectionVisitor(Vector2 point);
  virtual ~PointIntersectionVisitor() = default;

  bool intersects();
  std::shared_ptr<figure::Figure> getIntersectingFigure();

  void visit(std::shared_ptr<FigureGroup> group) override;
  void visit(std::shared_ptr<RectFigure> rect) override;
  void visit(std::shared_ptr<CircleFigure> circle) override;
  void visit(std::shared_ptr<PolyFigure> poly) override;
};

}  // namespace figure::visitor
