#include "AppUi.h"

#include <raygui.h>
#include <raylib.h>

#include "../figure/CircleFigure.h"
#include "../figure/PolyFigure.h"
#include "../figure/RectFigure.h"
#include "../util.h"
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
  {
    auto openStrat = std::make_shared<strategy::OpenDocumentStrategy>(editor);

    tabBar->setOpenStrategy(openStrat);
  }

  setupFileOperationButtons();
  setupUndoRedoButtons();
  setupMoveButtons();
  setupInsertRectButton();
  setupInsertCircleButton();
  setupInsertPolyButton();
  setupInsertLineButton();
  setupGroupButtons();
  setupOrderChangeButtons();
  setupFigureExistenceButtons();
  setupSettingsButtons();
}

void ui::AppUi::update() {
  tabBar->update();
  toolbar->update();
  editor->update();

  if (editor->getMode() != Editor::Mode::DocumentProperties) {
    for (auto& ks : shortcuts) {
      ks.update();
    }
  }
}

void ui::AppUi::setRect(const Rectangle& rect) {
  Widget::setRect(rect);
  tabBar->setRect({rect.x, rect.y, rect.width, 24});
  toolbar->setRect({rect.x, rect.y + 24, rect.width, 32});
  editor->setRect(
      {rect.x, rect.y + 24 + 32, rect.width, rect.height - 24 - 32});
}

void ui::AppUi::addShortcut(std::shared_ptr<strategy::Strategy<>> strat,
                            int key,
                            int mod) {
  KeyboardShortcut ks(key, mod);
  ks.setStrategy(strat);
  shortcuts.push_back(ks);
}

void ui::AppUi::setupFileOperationButtons() {
  auto newDocButton = std::make_shared<IconButton>(ICON_FILE_ADD);
  auto saveDocButton = std::make_shared<IconButton>(ICON_FILE_SAVE_CLASSIC);
  auto exportDocButton = std::make_shared<IconButton>(ICON_FILE_EXPORT);

  {
    auto newDocStrat = std::make_shared<strategy::NewDocumentStrategy>(tabBar);

    newDocButton->setStrategy(newDocStrat);
    addShortcut(newDocStrat, KEY_N, keyboardShortcutMod());
  }

  {
    auto saveDocStrat =
        std::make_shared<strategy::SaveDocumentStrategy>(editor);

    saveDocButton->setStrategy(saveDocStrat);
    addShortcut(saveDocStrat, KEY_S, keyboardShortcutMod());
  }

  {
    auto exportStrat = std::make_shared<strategy::FunctorStrategy<>>(
        [this]() { editor->exportDocument("png"); });

    exportDocButton->setStrategy(exportStrat);
    addShortcut(exportStrat, KEY_E, keyboardShortcutMod());
  }

  toolbar->addWidget(std::move(newDocButton));
  toolbar->addWidget(std::move(saveDocButton));
  toolbar->addWidget(std::move(exportDocButton));
}

void ui::AppUi::setupUndoRedoButtons() {
  auto undoButton = std::make_shared<IconButton>(ICON_UNDO);
  auto redoButton = std::make_shared<IconButton>(ICON_REDO);

  {
    auto undoStrat = std::make_shared<strategy::UndoStrategy>(editor);

    undoButton->setStrategy(undoStrat);
    addShortcut(undoStrat, KEY_Z, keyboardShortcutMod());
  }

  {
    auto redoStrat = std::make_shared<strategy::RedoStrategy>(editor);

    redoButton->setStrategy(redoStrat);
    addShortcut(redoStrat, KEY_Y, keyboardShortcutMod());
  }

  toolbar->addWidget(nullptr);
  toolbar->addWidget(std::move(undoButton));
  toolbar->addWidget(std::move(redoButton));
}

void ui::AppUi::setupMoveButtons() {
  auto selectButton = std::make_shared<IconButton>(ICON_CURSOR_CLASSIC);

  {
    auto selectStrat = std::make_shared<strategy::SetSelectStrategy>(editor);

    selectButton->setStrategy(selectStrat);
    addShortcut(selectStrat, KEY_Q);
  }

  toolbar->addWidget(nullptr);
  toolbar->addWidget(std::move(selectButton));
}

void ui::AppUi::setupInsertRectButton() {
  auto insertRectButton = std::make_shared<IconButton>(ICON_PLAYER_STOP);

  {
    auto rect = std::make_shared<figure::RectFigure>();
    rect->setDimensions({40, 40});
    rect->setFill(PINK);
    rect->setStroke(BLACK);
    rect->setStrokeWeight(1);

    auto setRectStrat = std::make_shared<strategy::SetFigureInsertStrategy>(
        editor, rect, ICON_PLAYER_STOP);

    insertRectButton->setStrategy(setRectStrat);
    addShortcut(setRectStrat, KEY_R);
  }

  toolbar->addWidget(nullptr);
  toolbar->addWidget(std::move(insertRectButton));
}

void ui::AppUi::setupInsertCircleButton() {
  auto insertCircleButton = std::make_shared<IconButton>(ICON_PLAYER_RECORD);

  {
    auto circle = std::make_shared<figure::CircleFigure>();
    circle->setRadius(20);
    circle->setFill(PINK);
    circle->setStroke(BLACK);
    circle->setStrokeWeight(1);

    auto setCircleStrat = std::make_shared<strategy::SetFigureInsertStrategy>(
        editor, circle, ICON_PLAYER_RECORD);

    insertCircleButton->setStrategy(setCircleStrat);

    addShortcut(setCircleStrat, KEY_E);
  }

  toolbar->addWidget(std::move(insertCircleButton));
}

void ui::AppUi::setupInsertPolyButton() {
  auto insertPolyButton = std::make_shared<IconButton>(ICON_STAR);

  {
    auto poly = std::make_shared<figure::PolyFigure>(5);
    poly->initializeRegularPolygon(20);
    poly->setFill(PINK);
    poly->setStroke(BLACK);
    poly->setStrokeWeight(1);

    auto setPolyStrat = std::make_shared<strategy::SetFigureInsertStrategy>(
        editor, poly, ICON_STAR);

    insertPolyButton->setStrategy(setPolyStrat);

    addShortcut(setPolyStrat, KEY_T);
  }

  toolbar->addWidget(std::move(insertPolyButton));
}

void ui::AppUi::setupInsertLineButton() {
  auto insertLineButton = std::make_shared<IconButton>(ICON_CROSSLINE);

  {
    auto line = std::make_shared<figure::PolyFigure>(2);
    line->setOffset(0, {30, 30});
    line->setStroke(BLACK);
    line->setStrokeWeight(3);

    auto setLineStrat = std::make_shared<strategy::SetFigureInsertStrategy>(
        editor, line, ICON_CROSSLINE);

    insertLineButton->setStrategy(setLineStrat);
    addShortcut(setLineStrat, KEY_L);
  }

  toolbar->addWidget(std::move(insertLineButton));
}

void ui::AppUi::setupGroupButtons() {
  auto groupButton = std::make_shared<IconButton>(ICON_LINK);
  auto ungroupButton = std::make_shared<IconButton>(ICON_LINK_BROKE);

  {
    auto groupStrat = std::make_shared<strategy::FunctorStrategy<>>(
        [this]() { editor->groupFigures(); });

    groupButton->setStrategy(groupStrat);
    addShortcut(groupStrat, KEY_G, keyboardShortcutMod());
  }

  {
    auto ungroupStrat = std::make_shared<strategy::FunctorStrategy<>>(
        [this]() { editor->ungroupFigures(); });

    ungroupButton->setStrategy(ungroupStrat);
    addShortcut(ungroupStrat, KEY_U, keyboardShortcutMod());
  }

  toolbar->addWidget(nullptr);
  toolbar->addWidget(std::move(groupButton));
  toolbar->addWidget(std::move(ungroupButton));
}

void ui::AppUi::setupOrderChangeButtons() {
  auto moveHigherButton = std::make_shared<IconButton>(ICON_STEP_OUT);
  auto moveLowerButton = std::make_shared<IconButton>(ICON_STEP_INTO);

  {
    auto moveLowerStrat = std::make_shared<strategy::FunctorStrategy<>>(
        [this]() { editor->changeFigureOrder(-1); });

    moveLowerButton->setStrategy(moveLowerStrat);
    addShortcut(moveLowerStrat, KEY_PAGE_DOWN);
  }

  {
    auto moveHigherStrat = std::make_shared<strategy::FunctorStrategy<>>(
        [this]() { editor->changeFigureOrder(+1); });

    moveHigherButton->setStrategy(moveHigherStrat);
    addShortcut(moveHigherStrat, KEY_PAGE_UP);
  }

  toolbar->addWidget(std::move(moveLowerButton));
  toolbar->addWidget(std::move(moveHigherButton));
}

void ui::AppUi::setupFigureExistenceButtons() {
  auto removeFigureButton = std::make_shared<IconButton>(ICON_FILE_DELETE);
  auto dupFigureButton = std::make_shared<IconButton>(ICON_FILE_COPY);

  {
    auto removeStrat = std::make_shared<strategy::FunctorStrategy<>>(
        [this]() { editor->removeFigure(); });

    removeFigureButton->setStrategy(removeStrat);
    addShortcut(removeStrat, KEY_DELETE);
  }

  {
    auto dupStrat = std::make_shared<strategy::FunctorStrategy<>>(
        [this]() { editor->duplicateFigure(); });

    dupFigureButton->setStrategy(dupStrat);
    addShortcut(dupStrat, KEY_D, keyboardShortcutMod());
  }

  toolbar->addWidget(std::move(removeFigureButton));
  toolbar->addWidget(std::move(dupFigureButton));
}

void ui::AppUi::setupSettingsButtons() {
  auto gridButton = std::make_shared<IconButton>(ICON_GRID);
  auto settingsButton = std::make_shared<IconButton>(ICON_GEAR);

  {
    auto gridStrat = std::make_shared<strategy::FunctorStrategy<>>(
        [this]() { editor->toggleGrid(); });

    gridButton->setStrategy(gridStrat);
    addShortcut(gridStrat, KEY_I, keyboardShortcutMod());
  }

  {
    auto settingsStrat = std::make_shared<strategy::FunctorStrategy<>>(
        [this]() { editor->setMode(Editor::Mode::DocumentProperties); });

    settingsButton->setStrategy(settingsStrat);
    addShortcut(settingsStrat, KEY_PERIOD, keyboardShortcutMod());
  }

  toolbar->addWidget(nullptr);
  toolbar->addWidget(std::move(gridButton));
  toolbar->addWidget(nullptr);
  toolbar->addWidget(std::move(settingsButton));
}
