#include "DocumentTabs.h"

#include <raygui.h>
#include <algorithm>

#include "../Document.h"

void ui::DocumentTabs::update() {
  const auto tabNames = Document::getDocumentNames();

  std::vector<std::string> strings;
  std::vector<const char*> cstrings;
  cstrings.reserve(tabNames.size());
  std::ranges::transform(tabNames, std::back_inserter(strings),
                         [](const auto& s) { return s.filename(); });
  std::ranges::transform(strings, std::back_inserter(cstrings),
                         [](const auto& s) { return s.c_str(); });

  auto it = std::ranges::find(tabNames, openedFilePath);
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
  openedFilePath = std::move(newName);

  if (openStrategy)
    openStrategy->execute(openedFilePath);
}

void ui::DocumentTabs::setOpenStrategy(
    std::shared_ptr<strategy::Strategy<std::filesystem::path>> strategy) {
  openStrategy = std::move(strategy);
}
