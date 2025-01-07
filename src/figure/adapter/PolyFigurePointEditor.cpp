#include "PolyFigurePointEditor.h"

#include <raymath.h>

#include "../PolyFigure.h"

using namespace figure::adapter;

figure::adapter::PolyFigurePointEditor::PolyFigurePointEditor(
    std::shared_ptr<PolyFigure> poly)
    : poly(std::move(poly)) {}

std::vector<PolyFigurePointEditor::Point>
figure::adapter::PolyFigurePointEditor::getEditPoints() {
  std::vector<PolyFigurePointEditor::Point> res;

  res.push_back({
      .id = 0,
      .type = PointEditor::PointType::Origin,
      .pos = poly->getOrigin(),
  });

  std::size_t idxGen = 1;
  for (auto& o : poly->getOffsets()) {
    res.push_back({
        .id = idxGen++,
        .type = PointEditor::PointType::Resize,
        .pos = poly->getOrigin() + o,
    });
  }

  return res;
}

void figure::adapter::PolyFigurePointEditor::updatePointPosition(
    std::size_t pointId,
    Vector2 newPos) {
  if (pointId == 0) {
    poly->setOrigin(newPos);
    return;
  }
  poly->setOffset(pointId - 1, newPos - poly->getOrigin());
}
