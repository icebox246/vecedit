#include "FigureGroupPointEditor.h"

figure::adapter::FigureGroupPointEditor::FigureGroupPointEditor(
    std::shared_ptr<FigureGroup> group)
    : group(std::move(group)) {}

std::vector<figure::adapter::FigureGroupPointEditor::Point>
figure::adapter::FigureGroupPointEditor::getEditPoints() {
  return {
      {
          .id = 0,
          .type = PointType::Origin,
          .pos = group->getOrigin(),
      },
  };
}

void figure::adapter::FigureGroupPointEditor::updatePointPosition(
    std::size_t pointId,
    Vector2 newPos) {
  assert(pointId == 0);
  group->setOrigin(newPos);
}
