#pragma once

#include "FigureVisitor.h"

namespace figure::visitor {

class RendererVisitor : public FigureVisitor {
 public:
  virtual ~RendererVisitor() = default;

  void visit(RectFigure& rect) override;
  void visit(CircleFigure& circle) override;
};

}  // namespace figure::visitor
