#include "RendererVisitor.h"

#include "../CircleFigure.h"
#include "../FigureGroup.h"
#include "../PolyFigure.h"
#include "../RectFigure.h"

#include <raymath.h>

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
  DrawCircleV(circle->getOrigin(),
              circle->getRadius() + circle->getStrokeWeight() * 0.5f,
              circle->getStroke());
  DrawCircleV(circle->getOrigin(),
              circle->getRadius() - circle->getStrokeWeight() * 0.5f,
              circle->getFill());
}

void figure::visitor::RendererVisitor::visit(std::shared_ptr<PolyFigure> poly) {
  Vector2 points[poly->getPointCount() + 1];
  points[poly->getPointCount()] = points[0] = poly->getOrigin();
  for (int i = 1; i < poly->getPointCount(); i++) {
    points[i] = poly->getOrigin() + poly->getOffsets()[i - 1];
  }
  DrawTriangleFan(points, poly->getPointCount() + 1, poly->getFill());

  for (int i = 0; i < poly->getPointCount(); i++) {
    DrawLineEx(points[i], points[i + 1], poly->getStrokeWeight(),
               poly->getStroke());
    DrawCircleV(points[i], poly->getStrokeWeight() * 0.5f, poly->getStroke());
  }
}
