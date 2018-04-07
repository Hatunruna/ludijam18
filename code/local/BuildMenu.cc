/*
 * NO Inc.
 * Copyright (C) 2018 Hatunruna team
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include "BuildMenu.h"

#include <gf/Coordinates.h>
#include <gf/Log.h>
#include <gf/RenderTarget.h>
#include <gf/Shapes.h>
#include <gf/VectorOps.h>

#include "Messages.h"
#include "Singletons.h"

namespace no {

  BuildMenu::BuildMenu()
  : m_state(State::Idle)
  , m_oilPumpTexture(gResourceManager().getTexture("oil-pump.png"))
  , m_oilPumpWidget(m_oilPumpSprite)
  , m_selectedTexture(nullptr)
  {
    m_oilPumpTexture.setSmooth();

    // Sprite for building
    gf::WidgetContainer widgets;

    m_oilPumpSprite.setTexture(m_oilPumpTexture);

    m_oilPumpWidget.setCallback([this]() {
      if (m_state == State::Idle) {
        m_state = State::BuildSelected;
        m_selectedTexture = &m_oilPumpTexture;
      }
    });
    m_widgets.addWidget(m_oilPumpWidget);
  }

  void BuildMenu::pointTo(gf::Vector2f position) {
    m_mousePosition = position;
    m_widgets.pointTo(m_mousePosition);
  }

  void BuildMenu::pressed(gf::MouseButton button) {
    if (button == gf::MouseButton::Left) {
      m_widgets.triggerAction();
    }
  }

  gf::WidgetContainer& BuildMenu::getWidgetContainer() {
    return m_widgets;
  }

  void BuildMenu::update(gf::Time time) {
    // gf::Log::debug("(%f;%f)\n", m_mousePosition.x, m_mousePosition.y);
  }

  void BuildMenu::render(gf::RenderTarget& target, const gf::RenderStates& states) {
    gf::Coordinates coordinates(target);

    // Drawing the menu
    static constexpr float WidgetSize = 256.0f;
    static constexpr float MenuPadding = 0.01f;
    static constexpr gf::Vector2f MenuRelativeSize = { 0.075f, 1.0f };

    auto size = coordinates.getRelativeSize(MenuRelativeSize);
    gf::RectangleShape rect;
    rect.setSize(size);
    rect.setColor(gf::Color::White);

    target.draw(rect, states);

    auto position = coordinates.getRelativePoint({ MenuPadding, MenuPadding });
    size = coordinates.getRelativeSize({ MenuRelativeSize.width - MenuPadding * 2, MenuRelativeSize.height });
    m_oilPumpSprite.setScale(size.width / WidgetSize);
    m_oilPumpSprite.setPosition(position);

    m_widgets.render(target, states);

    if (m_state == State::BuildSelected) {
      assert(m_selectedTexture != nullptr);

      // Drawing the cursor
      gf::Sprite cursor;
      cursor.setTexture(*m_selectedTexture);
      auto padding = coordinates.getRelativeSize({ MenuPadding, MenuPadding });
      cursor.setPosition({m_mousePosition.x + padding.x, m_mousePosition.y - padding.y});
      cursor.setScale(size.width / WidgetSize);
      cursor.setAnchor(gf::Anchor::BottomLeft);

      target.draw(cursor);
    }
  }

}
