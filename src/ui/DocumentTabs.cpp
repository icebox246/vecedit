#include "DocumentTabs.h"

#include <raygui.h>
#include <algorithm>

#include "../Document.h"

void ui::DocumentTabs::update() {
  const auto tabNames = Document::getDocumentNames();

  std::vector<const char*> cstrings;
  cstrings.reserve(tabNames.size());
  std::ranges::transform(tabNames, std::back_inserter(cstrings),
                         [](const auto& s) { return s.data(); });

  auto it = std::ranges::find(tabNames, openedFileName);
  if (it == tabNames.end())
    it = tabNames.begin();

  int active = std::distance(tabNames.begin(), it);
  int oldActive = active;
  if (auto idxToClose =
          GuiTabBar(rect, cstrings.data(), cstrings.size(), &active);
      idxToClose != -1) {
    // TODO close a tab
  }
  if (tabNames.size() && active != oldActive) {
    setOpenedFile(std::string(tabNames[active]));
  }
}

void ui::DocumentTabs::setOpenedFile(std::string newName) {
  openedFileName = std::move(newName);

  if (openCommand)
    openCommand->execute(openedFileName);
}

void ui::DocumentTabs::setOpenCommand(
    std::shared_ptr<command::Command<std::string_view>> command) {
  openCommand = std::move(command);
}
