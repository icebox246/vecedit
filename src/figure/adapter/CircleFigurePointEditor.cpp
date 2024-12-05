#include "CircleFigurePointEditor.h"

#include <raylib.h>
#include <raymath.h>

namespace {

enum class SpecialPointIds : std::size_t {
  CircleOrigin,
  CircleRadiusHandle,
};

}

figure::adapter::CircleFigurePointEditor::CircleFigurePointEditor(
    std::shared_ptr<CircleFigure> circle)
    : circle(std::move(circle)) {
  assert(this->circle);
}

std::vector<figure::adapter::CircleFigurePointEditor::Point>
figure::adapter::CircleFigurePointEditor::getEditPoints() {
  return {
      Point{
          .id = static_cast<std::size_t>(SpecialPointIds::CircleOrigin),
          .type = PointType::Origin,
          .pos = circle->getOrigin(),
      },
      Point{
          .id = static_cast<std::size_t>(SpecialPointIds::CircleRadiusHandle),
          .type = PointType::Resize,
          .pos = circle->getOrigin() + Vector2{1, 0} * circle->getRadius(),
      },

  };
}

void figure::adapter::CircleFigurePointEditor::updatePointPosition(
    std::size_t pointId,
    Vector2 newPos) {
  switch (static_cast<SpecialPointIds>(pointId)) {
    case SpecialPointIds::CircleOrigin:
      circle->setOrigin(newPos);
      break;
    case SpecialPointIds::CircleRadiusHandle:
      circle->setRadius((newPos - circle->getOrigin()).x);
      break;
  }
}
