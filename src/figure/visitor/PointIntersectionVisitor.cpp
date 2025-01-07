#include "PointIntersectionVisitor.h"

#include <ranges>

#include "../CircleFigure.h"
#include "../FigureGroup.h"
#include "../PolyFigure.h"
#include "../RectFigure.h"

figure::visitor::PointIntersectionVisitor::PointIntersectionVisitor(
    Vector2 point)
    : point(point) {}

bool figure::visitor::PointIntersectionVisitor::intersects() {
  return intersectingFigure != nullptr;
}

std::shared_ptr<figure::Figure>
figure::visitor::PointIntersectionVisitor::getIntersectingFigure() {
  return intersectingFigure;
}

void figure::visitor::PointIntersectionVisitor::visit(
    std::shared_ptr<FigureGroup> group) {
  for (auto fig : std::ranges::reverse_view(group->getChildren())) {
    fig->accept(*this);

    if (intersects())
      return;
  }
}

void figure::visitor::PointIntersectionVisitor::visit(
    std::shared_ptr<RectFigure> rect) {
  auto r = rect->getRectangle();

  if (CheckCollisionPointRec(point, r)) {
    intersectingFigure = rect;
  }
}

void figure::visitor::PointIntersectionVisitor::visit(
    std::shared_ptr<CircleFigure> circle) {
  if (CheckCollisionPointCircle(point, circle->getOrigin(),
                                circle->getRadius())) {
    intersectingFigure = circle;
  }
}

void figure::visitor::PointIntersectionVisitor::visit(
    std::shared_ptr<PolyFigure> poly) {
  Vector2 points[poly->getPointCount()];
  points[0] = poly->getOrigin();
  for (int i = 1; i < poly->getPointCount(); i++) {
    points[i] = poly->getOrigin() + poly->getOffsets()[i - 1];
  }

  if (CheckCollisionPointPoly(point, points, poly->getPointCount())) {
    intersectingFigure = poly;
    return;
  }

  for (int i = 0; i < poly->getPointCount(); i++) {
    if (CheckCollisionPointLine(point, points[i],
                                points[(i + 1) % poly->getPointCount()],
                                poly->getStrokeWeight() * 0.5f)) {
      intersectingFigure = poly;
      return;
    }
  }
}
