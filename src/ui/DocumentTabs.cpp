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
                         [](const auto& s) { return s.filename().string(); });
  std::ranges::transform(strings, std::back_inserter(cstrings),
                         [](const auto& s) { return s.c_str(); });

  auto it = tabNames.end();
  if (openedDocument) {
    it = std::ranges::find(tabNames, openedDocument->getFilePath());
  }

  int active = std::distance(tabNames.begin(), it);
  int oldActive = active;
  if (auto idxToClose =
          GuiTabBar(rect, cstrings.data(), cstrings.size(), &active);
      idxToClose != -1) {
    auto docToClose = Document::getDocument(tabNames[idxToClose]);
    if (openedDocument == docToClose) {
      openedDocument = nullptr;
      openStrategy->execute(nullptr);
    }
    docToClose->close();
  } else if (tabNames.size() && active != oldActive) {
    setOpenedFile(tabNames[active]);
  }
}

void ui::DocumentTabs::setOpenedFile(std::filesystem::path newName) {
  openedDocument = Document::getDocument(newName);

  if (openStrategy)
    openStrategy->execute(openedDocument);
}

void ui::DocumentTabs::setOpenStrategy(
    std::shared_ptr<strategy::Strategy<std::shared_ptr<Document>>> strategy) {
  openStrategy = std::move(strategy);
}
