#pragma once

namespace figure {

class FigureGroup;
class RectFigure;
class CircleFigure;

}  // namespace figure

namespace figure::visitor {

class FigureVisitor {
 public:
  virtual ~FigureVisitor() = default;

  virtual void visit(FigureGroup& rect) = 0;
  virtual void visit(RectFigure& rect) = 0;
  virtual void visit(CircleFigure& circle) = 0;
};

}  // namespace figure::visitor
