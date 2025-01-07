#include "AppUi.h"

#include <raygui.h>
#include <raylib.h>

#include "../figure/CircleFigure.h"
#include "../figure/PolyFigure.h"
#include "../figure/RectFigure.h"
#include "DocumentTabs.h"
#include "IconButton.h"
#include "strategy/FunctorStrategy.h"
#include "strategy/NewDocumentStrategy.h"
#include "strategy/OpenDocumentStrategy.h"
#include "strategy/RedoStrategy.h"
#include "strategy/SaveDocumentStrategy.h"
#include "strategy/SetFigureInsertStrategy.h"
#include "strategy/SetSelectStrategy.h"
#include "strategy/UndoStrategy.h"

ui::AppUi::AppUi()
    : tabBar(std::make_shared<DocumentTabs>()),
      toolbar(std::make_shared<Toolbar>()),
      editor(std::make_shared<Editor>()) {
  auto newDocButton = std::make_shared<IconButton>(ICON_FILE_ADD);
  auto saveDocButton = std::make_shared<IconButton>(ICON_FILE_SAVE_CLASSIC);
  auto undoButton = std::make_shared<IconButton>(ICON_UNDO);
  auto redoButton = std::make_shared<IconButton>(ICON_REDO);

  auto selectButton = std::make_shared<IconButton>(ICON_CURSOR_CLASSIC);

  auto insertRectButton = std::make_shared<IconButton>(ICON_PLAYER_STOP);
  auto insertCircleButton = std::make_shared<IconButton>(ICON_PLAYER_RECORD);
  auto insertPolyButton = std::make_shared<IconButton>(ICON_STAR);
  auto insertLineButton = std::make_shared<IconButton>(ICON_CROSSLINE);

  auto groupButton = std::make_shared<IconButton>(ICON_LINK);
  auto ungroupButton = std::make_shared<IconButton>(ICON_LINK_BROKE);
  auto moveHigherButton = std::make_shared<IconButton>(ICON_STEP_OUT);
  auto moveLowerButton = std::make_shared<IconButton>(ICON_STEP_INTO);
  auto removeFigureButton = std::make_shared<IconButton>(ICON_FILE_DELETE);
  auto dupFigureButton = std::make_shared<IconButton>(ICON_FILE_COPY);

  {
    auto newDocStrat = std::make_shared<strategy::NewDocumentStrategy>(tabBar);

    newDocButton->setStrategy(newDocStrat);
  }

  {
    auto saveDocStrat =
        std::make_shared<strategy::SaveDocumentStrategy>(editor);

    saveDocButton->setStrategy(saveDocStrat);
  }

  {
    auto undoStrat = std::make_shared<strategy::UndoStrategy>(editor);

    undoButton->setStrategy(undoStrat);
  }

  {
    auto redoStrat = std::make_shared<strategy::RedoStrategy>(editor);

    redoButton->setStrategy(redoStrat);
  }

  {
    auto openStrat = std::make_shared<strategy::OpenDocumentStrategy>(editor);

    tabBar->setOpenStrategy(openStrat);
  }

  {
    auto selectStrat = std::make_shared<strategy::SetSelectStrategy>(editor);

    selectButton->setStrategy(selectStrat);
  }

  {
    auto rect = std::make_shared<figure::RectFigure>();
    rect->setDimensions({40, 40});
    rect->setFill(PINK);
    rect->setStroke(BLACK);
    rect->setStrokeWeight(1);

    auto setRectStrat = std::make_shared<strategy::SetFigureInsertStrategy>(
        editor, rect, ICON_PLAYER_STOP);

    insertRectButton->setStrategy(setRectStrat);
  }

  {
    auto circle = std::make_shared<figure::CircleFigure>();
    circle->setRadius(20);
    circle->setFill(PINK);
    circle->setStroke(BLACK);
    circle->setStrokeWeight(1);

    auto setCircleStrat = std::make_shared<strategy::SetFigureInsertStrategy>(
        editor, circle, ICON_PLAYER_RECORD);

    insertCircleButton->setStrategy(setCircleStrat);
  }

  {
    auto poly = std::make_shared<figure::PolyFigure>(5);
    poly->initializeRegularPolygon(20);
    poly->setFill(PINK);
    poly->setStroke(BLACK);
    poly->setStrokeWeight(1);

    auto setPolyStrat = std::make_shared<strategy::SetFigureInsertStrategy>(
        editor, poly, ICON_STAR);

    insertPolyButton->setStrategy(setPolyStrat);
  }

  {
    auto line = std::make_shared<figure::PolyFigure>(2);
    line->setOffset(0, {30, 30});
    line->setStroke(BLACK);
    line->setStrokeWeight(3);

    auto setLineStrat = std::make_shared<strategy::SetFigureInsertStrategy>(
        editor, line, ICON_CROSSLINE);

    insertLineButton->setStrategy(setLineStrat);
  }

  {
    auto groupStrat = std::make_shared<strategy::FunctorStrategy<>>(
        [this]() { editor->groupFigures(); });

    groupButton->setStrategy(groupStrat);
  }

  {
    auto ungroupStrat = std::make_shared<strategy::FunctorStrategy<>>(
        [this]() { editor->ungroupFigures(); });

    ungroupButton->setStrategy(ungroupStrat);
  }

  {
    auto moveLowerStrat = std::make_shared<strategy::FunctorStrategy<>>(
        [this]() { editor->changeFigureOrder(-1); });

    moveLowerButton->setStrategy(moveLowerStrat);
  }

  {
    auto moveHigherStrat = std::make_shared<strategy::FunctorStrategy<>>(
        [this]() { editor->changeFigureOrder(+1); });

    moveHigherButton->setStrategy(moveHigherStrat);
  }

  {
    auto removeStrat = std::make_shared<strategy::FunctorStrategy<>>(
        [this]() { editor->removeFigure(); });

    removeFigureButton->setStrategy(removeStrat);
  }

  {
    auto removeStrat = std::make_shared<strategy::FunctorStrategy<>>(
        [this]() { editor->duplicateFigure(); });

    dupFigureButton->setStrategy(removeStrat);
  }

  toolbar->addWidget(std::move(newDocButton));
  toolbar->addWidget(std::move(saveDocButton));
  toolbar->addWidget(nullptr);
  toolbar->addWidget(std::move(undoButton));
  toolbar->addWidget(std::move(redoButton));
  toolbar->addWidget(nullptr);
  toolbar->addWidget(std::move(selectButton));
  toolbar->addWidget(nullptr);
  toolbar->addWidget(std::move(insertRectButton));
  toolbar->addWidget(std::move(insertCircleButton));
  toolbar->addWidget(std::move(insertPolyButton));
  toolbar->addWidget(std::move(insertLineButton));
  toolbar->addWidget(nullptr);
  toolbar->addWidget(std::move(groupButton));
  toolbar->addWidget(std::move(ungroupButton));
  toolbar->addWidget(std::move(moveLowerButton));
  toolbar->addWidget(std::move(moveHigherButton));
  toolbar->addWidget(std::move(removeFigureButton));
  toolbar->addWidget(std::move(dupFigureButton));
}

void ui::AppUi::update() {
  tabBar->update();
  toolbar->update();
  editor->update();
}

void ui::AppUi::setRect(const Rectangle& rect) {
  Widget::setRect(rect);
  tabBar->setRect({rect.x, rect.y, rect.width, 24});
  toolbar->setRect({rect.x, rect.y + 24, rect.width, 32});
  editor->setRect(
      {rect.x, rect.y + 24 + 32, rect.width, rect.height - 24 - 32});
}
