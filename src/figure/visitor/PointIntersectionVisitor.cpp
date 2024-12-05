#include "PointIntersectionVisitor.h"

#include "../CircleFigure.h"
#include "../RectFigure.h"

figure::visitor::PointIntersectionVisitor::PointIntersectionVisitor(
    Vector2 point)
    : point(point) {}

bool figure::visitor::PointIntersectionVisitor::intersects() {
  return gotIntersection;
}

void figure::visitor::PointIntersectionVisitor::visit(RectFigure& rect) {
  auto r = rect.getRectangle();

  gotIntersection = CheckCollisionPointRec(point, r);
}

void figure::visitor::PointIntersectionVisitor::visit(CircleFigure& circle) {
  gotIntersection =
      CheckCollisionPointCircle(point, circle.getOrigin(), circle.getRadius());
}
