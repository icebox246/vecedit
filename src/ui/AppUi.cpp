#include "AppUi.h"

#include <raygui.h>
#include <raylib.h>

#include "../figure/CircleFigure.h"
#include "../figure/RectFigure.h"
#include "DocumentTabs.h"
#include "IconButton.h"
#include "strategy/NewDocumentStrategy.h"
#include "strategy/OpenDocumentStrategy.h"
#include "strategy/SetFigureInsertStrategy.h"
#include "strategy/SetSelectStrategy.h"

ui::AppUi::AppUi()
    : tabBar(std::make_shared<DocumentTabs>()),
      toolbar(std::make_shared<Toolbar>()),
      editor(std::make_shared<Editor>()) {
  auto newDocButton = std::make_shared<IconButton>(ICON_FILE_ADD);
  auto saveDocButton = std::make_shared<IconButton>(ICON_FILE_SAVE_CLASSIC);
  auto loadDocButton = std::make_shared<IconButton>(ICON_FOLDER_FILE_OPEN);

  auto selectButton = std::make_shared<IconButton>(ICON_CURSOR_CLASSIC);

  auto insertRectButton = std::make_shared<IconButton>(ICON_PLAYER_STOP);
  auto insertCircleButton = std::make_shared<IconButton>(ICON_PLAYER_RECORD);

  {
    auto newDocStrat = std::make_shared<strategy::NewDocumentStrategy>(tabBar);

    newDocButton->setStrategy(newDocStrat);
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

  toolbar->addWidget(std::move(newDocButton));
  toolbar->addWidget(std::move(saveDocButton));
  toolbar->addWidget(std::move(loadDocButton));
  toolbar->addWidget(nullptr);
  toolbar->addWidget(std::move(selectButton));
  toolbar->addWidget(nullptr);
  toolbar->addWidget(std::move(insertRectButton));
  toolbar->addWidget(std::move(insertCircleButton));
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
