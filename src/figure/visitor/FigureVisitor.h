#pragma once

#include <memory>

namespace figure {

class FigureGroup;
class RectFigure;
class CircleFigure;
class PolyFigure;

}  // namespace figure

namespace figure::visitor {

class FigureVisitor {
 public:
  virtual ~FigureVisitor() = default;

  virtual void visit(std::shared_ptr<FigureGroup> rect) = 0;
  virtual void visit(std::shared_ptr<RectFigure> rect) = 0;
  virtual void visit(std::shared_ptr<CircleFigure> circle) = 0;
  virtual void visit(std::shared_ptr<PolyFigure> poly) = 0;
};

}  // namespace figure::visitor
