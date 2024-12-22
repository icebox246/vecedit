#include "RendererVisitor.h"

#include "../CircleFigure.h"
#include "../FigureGroup.h"
#include "../RectFigure.h"

void figure::visitor::RendererVisitor::visit(
    std::shared_ptr<FigureGroup> group) {
  for (auto fig : group->getChildren()) {
    fig->accept(*this);
  }
}

void figure::visitor::RendererVisitor::visit(std::shared_ptr<RectFigure> rect) {
  DrawRectangleRec(rect->getRectangle(), rect->getFill());
  DrawRectangleLinesEx(rect->getRectangle(), rect->getStrokeWeight(),
                       rect->getStroke());
}

void figure::visitor::RendererVisitor::visit(
    std::shared_ptr<CircleFigure> circle) {
  DrawCircleV(circle->getOrigin(), circle->getRadius(), circle->getStroke());
  DrawCircleV(circle->getOrigin(),
              circle->getRadius() - circle->getStrokeWeight(),
              circle->getFill());
}
