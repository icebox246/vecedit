#include "Toolbar.h"

void ui::Toolbar::update() {
  for (auto& w : widgets) {
    if (w)
      w->update();
  }
}

void ui::Toolbar::setRect(const Rectangle& rect) {
  Widget::setRect(rect);

  auto padding = 2.f;
  Rectangle r = {rect.x + padding, rect.y + padding, rect.height - padding * 2,
                 rect.height - padding * 2};
  for (auto& w : widgets) {
    if (w) {
      w->setRect(r);
      r.x += r.height + padding;
    } else {
      r.x += r.height / 2;
    }
  }
}

void ui::Toolbar::addWidget(std::shared_ptr<Widget> tool) {
  widgets.emplace_back(std::move(tool));
}
