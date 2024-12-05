#include "CircleFigure.h"

#include "adapter/CircleFigurePointEditor.h"

void figure::CircleFigure::setRadius(float newRadius) {
  if (newRadius < 0)
    newRadius = 0;

  radius = newRadius;
}

float figure::CircleFigure::getRadius() {
  return radius;
}

std::shared_ptr<figure::PointEditor> figure::CircleFigure::makePointEditor() {
  return std::make_shared<adapter::CircleFigurePointEditor>(shared_from_this());
}
