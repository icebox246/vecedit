#pragma once

#include <cassert>
#include "FigureVisitor.h"

namespace figure::visitor {

class RendererVisitor : public FigureVisitor {
 public:
  virtual ~RendererVisitor() = default;

  void visit(std::shared_ptr<FigureGroup> group) override;
  void visit(std::shared_ptr<RectFigure> rect) override;
  void visit(std::shared_ptr<CircleFigure> circle) override;
  void visit(std::shared_ptr<PolyFigure> poly) override;
};

}  // namespace figure::visitor
