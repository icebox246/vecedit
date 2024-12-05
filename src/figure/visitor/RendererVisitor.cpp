#include "RendererVisitor.h"

#include "../CircleFigure.h"
#include "../RectFigure.h"

void figure::visitor::RendererVisitor::visit(RectFigure& rect) {
  DrawRectangleRec(rect.getRectangle(), rect.getFill());
  DrawRectangleLinesEx(rect.getRectangle(), rect.getStrokeWeight(),
                       rect.getStroke());
}

void figure::visitor::RendererVisitor::visit(CircleFigure& circle) {
  DrawCircleV(circle.getOrigin(), circle.getRadius(), circle.getStroke());
  DrawCircleV(circle.getOrigin(), circle.getRadius() - circle.getStrokeWeight(),
              circle.getFill());
}
