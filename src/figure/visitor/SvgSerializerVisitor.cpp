#include "SvgSerializerVisitor.h"

#include <format>
#include <fstream>
#include "../CircleFigure.h"
#include "../FigureGroup.h"
#include "../PolyFigure.h"
#include "../RectFigure.h"

static std::string colorToHex(Color color) {
  return std::format("{:02x}{:02x}{:02x}{:02x}", color.r, color.g, color.b,
                     color.a);
}

static std::string makeStyleStringForFigure(figure::Figure& fig) {
  return std::format(
      "fill:#{};stroke:#{};stroke-width:{};stroke-linecap:round;stroke-"
      "linejoin:round;stroke-miterlimit:5;paint-order:fill markers stroke",
      colorToHex(fig.getFill()), colorToHex(fig.getStroke()),
      fig.getStrokeWeight());
}

figure::visitor::SvgSerializerVisitor::SvgSerializerVisitor(
    Vector2 dimensions) {
  ss << std::format(
      R"(<?xml version="1.0" encoding="UTF-8" standalone="no"?>
        <!-- Created with VecEdit -->
        <svg
         viewBox="0 0 {} {}"
         version="1.1"
         id="svg1"
         xmlns="http://www.w3.org/2000/svg"
         xmlns:svg="http://www.w3.org/2000/svg">
        )",
      (int)dimensions.x, (int)dimensions.y);
}

void figure::visitor::SvgSerializerVisitor::saveToFile(
    const std::filesystem::path& filepath) {
  ss << "</svg>";

  auto fp = filepath;
  if (fp.extension() != ".svg") {
    fp.replace_filename(std::format("{}.svg", fp.filename().string()));
  }

  TraceLog(LOG_INFO, TextFormat("Saved to %s", fp.c_str()));

  std::ofstream of(fp);
  of << ss.str();
}

void figure::visitor::SvgSerializerVisitor::visit(
    std::shared_ptr<FigureGroup> group) {
  for (auto fig : group->getChildren()) {
    fig->accept(*this);
  }
}

void figure::visitor::SvgSerializerVisitor::visit(
    std::shared_ptr<RectFigure> rect) {
  auto r = rect->getRectangle();
  ss << std::format(R"(<rect style="{}"
          x="{}" y="{}" width="{}" height="{}" />)",
                    makeStyleStringForFigure(*rect), r.x, r.y, r.width,
                    r.height);
}

void figure::visitor::SvgSerializerVisitor::visit(
    std::shared_ptr<CircleFigure> circle) {
  auto c = circle->getOrigin();
  ss << std::format(R"(<circle style="{}"
          cx="{}" cy="{}" r="{}" />)",
                    makeStyleStringForFigure(*circle), c.x, c.y,
                    circle->getRadius());
}

void figure::visitor::SvgSerializerVisitor::visit(
    std::shared_ptr<PolyFigure> poly) {
  auto origin = poly->getOrigin();
  ss << std::format(R"(<path style="{}" d="M {} {})",
                    makeStyleStringForFigure(*poly), origin.x, origin.y);
  for (auto offset : poly->getOffsets()) {
    auto point = origin + offset;
    ss << std::format(" L {} {}", point.x, point.y);
  }
  ss << std::format(R"( L {} {}" />)", origin.x, origin.y);
}
