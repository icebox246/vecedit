#pragma once

#pragma once

#include <memory>

#include "../FigureGroup.h"
#include "../PointEditor.h"

namespace figure::adapter {

class FigureGroupPointEditor : public PointEditor {
  std::shared_ptr<FigureGroup> group;

 public:
  FigureGroupPointEditor(std::shared_ptr<FigureGroup> group);
  ~FigureGroupPointEditor() override = default;

  std::vector<Point> getEditPoints() override;
  void updatePointPosition(std::size_t pointId, Vector2 newPos) override;
};

};  // namespace figure::adapter
