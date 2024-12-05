#pragma once

#include <raylib.h>
#include <vector>

namespace figure {

class PointEditor {
 public:
  enum class PointType {
    Origin,
    Resize,
    HiddenClickable,
  };

  struct Point {
    std::size_t id;
    PointType type;
    Vector2 pos;
  };

  virtual ~PointEditor() = default;

  virtual std::vector<Point> getEditPoints() = 0;
  virtual void updatePointPosition(std::size_t pointId, Vector2 newPos) = 0;
};

}  // namespace figure
