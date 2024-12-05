#include "RectFigure.h"

#include "adapter/RectFigurePointEditor.h"

void figure::RectFigure::setDimensions(Vector2 newDimensions) {
  if (newDimensions.x < 0) {
    newDimensions.x = 0;
  }
  if (newDimensions.y < 0) {
    newDimensions.y = 0;
  }
  dimensions = newDimensions;
}

Rectangle figure::RectFigure::getRectangle() {
  return {origin.x, origin.y, dimensions.x, dimensions.y};
}

std::shared_ptr<figure::PointEditor> figure::RectFigure::makePointEditor() {
  return std::make_shared<adapter::RectFigurePointEditor>(shared_from_this());
}
