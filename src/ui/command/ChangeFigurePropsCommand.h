#pragma once

#include <memory>

#include "../../figure/Figure.h"
#include "Command.h"

namespace command {

class ChangeFigurePropsCommand : public Command {
 public:
  struct FigureProps {
    Color fill;
    Color stroke;
    float strokeWeight;

    static FigureProps makePropsFromFig(figure::Figure& fig) {
      return {
          .fill = fig.getFill(),
          .stroke = fig.getStroke(),
          .strokeWeight = fig.getStrokeWeight(),
      };
    }

    bool operator==(const FigureProps& o) const {
      return ColorIsEqual(fill, o.fill) && ColorIsEqual(stroke, o.stroke) &&
             strokeWeight == o.strokeWeight;
    }
  };

 private:
  std::shared_ptr<figure::Figure> fig;
  FigureProps oldProps, newProps;

 public:
  ChangeFigurePropsCommand(std::shared_ptr<figure::Figure> fig,
                           FigureProps oldProps,
                           FigureProps newProps)
      : fig(std::move(fig)), oldProps(oldProps), newProps(newProps) {}

  void execute() override {
    fig->setFill(newProps.fill);
    fig->setStroke(newProps.stroke);
    fig->setStrokeWeight(newProps.strokeWeight);
  }

  void unexecute() override {
    fig->setFill(oldProps.fill);
    fig->setStroke(oldProps.stroke);
    fig->setStrokeWeight(oldProps.strokeWeight);
  }
};

}  // namespace command
