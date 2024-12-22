#include "PointIntersectionVisitor.h"

#include <ranges>

#include "../CircleFigure.h"
#include "../FigureGroup.h"
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
