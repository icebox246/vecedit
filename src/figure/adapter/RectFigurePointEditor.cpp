#include "RectFigurePointEditor.h"

#include <raymath.h>

namespace {

enum class SpecialPointIds : std::size_t {
  RectOrigin,
  RectResizer,
};

}

figure::adapter::RectFigurePointEditor::RectFigurePointEditor(
    std::shared_ptr<RectFigure> rect)
    : rect(std::move(rect)) {
  assert(this->rect);
}

std::vector<figure::adapter::RectFigurePointEditor::Point>
figure::adapter::RectFigurePointEditor::getEditPoints() {
  auto r = rect->getRectangle();
  return {
      Point{
          .id = static_cast<std::size_t>(SpecialPointIds::RectOrigin),
          .type = PointType::Origin,
          .pos = rect->getOrigin(),
      },
      Point{
          .id = static_cast<std::size_t>(SpecialPointIds::RectResizer),
          .type = PointType::Resize,
          .pos = rect->getOrigin() + Vector2{r.width, r.height},
      },
  };
}

void figure::adapter::RectFigurePointEditor::updatePointPosition(
    std::size_t pointId,
    Vector2 newPos) {
  switch (static_cast<SpecialPointIds>(pointId)) {
    case SpecialPointIds::RectOrigin:
      rect->setOrigin(newPos);
      break;
    case SpecialPointIds::RectResizer:
      rect->setDimensions(newPos - rect->getOrigin());
      break;
  }
}
