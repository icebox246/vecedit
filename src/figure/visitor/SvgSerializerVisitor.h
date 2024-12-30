#pragma once

#include <raylib.h>
#include <filesystem>
#include <sstream>

#include "FigureVisitor.h"

namespace figure::visitor {

class SvgSerializerVisitor : public FigureVisitor {
  std::stringstream ss;

 public:
  SvgSerializerVisitor(Vector2 dimensions);
  virtual ~SvgSerializerVisitor() = default;

  void saveToFile(const std::filesystem::path& filepath);

  void visit(std::shared_ptr<FigureGroup> group) override;
  void visit(std::shared_ptr<RectFigure> rect) override;
  void visit(std::shared_ptr<CircleFigure> circle) override;
};

}  // namespace figure::visitor
