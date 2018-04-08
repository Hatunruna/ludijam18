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
#include "InfoPanel.h"

#include <gf/Coordinates.h>
#include <gf/RenderTarget.h>
#include <gf/StringUtils.h>
#include <gf/Text.h>
#include <gf/StringUtils.h>

#include <gf/Log.h>

#include "Messages.h"
#include "Singletons.h"

namespace no {

  InfoPanel::InfoPanel()
  : m_balance(5000.0f)
  , m_font(gResourceManager().getFont("liberation-sans.ttf"))
  , m_currentCharacterSize(14)
  , m_ui(m_font, m_currentCharacterSize)
  {
    // Messages handlers
    gMessageManager().registerHandler<BalanceOperation>(&InfoPanel::onBalanceOperation, this);
  }

  void InfoPanel::processEvent(const gf::Event& event) {
    m_ui.processEvent(event);
  }

  void InfoPanel::update(gf::Time time) {

  }

  void InfoPanel::render(gf::RenderTarget& target, const gf::RenderStates& states) {
    gf::Coordinates coordinates(target);

    float height = 1.2f * m_currentCharacterSize;

    gf::Vector2f dashboardPosition = coordinates.getRelativePoint({ 0.8f, 0.0f });
    gf::Vector2f dashboardSize = coordinates.getRelativeSize({ 0.2f, 0.5f });

    std::string money = "$ " + gf::niceNum(m_balance, 0.01f);

    if (m_ui.begin("NO Inc. Dashboard", gf::RectF(dashboardPosition, dashboardSize), gf::UIWindow::Title | gf::UIWindow::Border)) {
      m_ui.layoutRow(gf::UILayout::Dynamic, height, { 0.3f, 0.7f });
      m_ui.label("Money:");
      m_ui.label(money);
    }

    m_ui.end();

    gf::Vector2f infoPosition = coordinates.getRelativePoint({ 0.8f, 0.5f });
    gf::Vector2f infoSize = coordinates.getRelativeSize({ 0.2f, 0.5f });

    if (m_ui.begin("NO Inc. Info", gf::RectF(infoPosition, infoSize), gf::UIWindow::Title | gf::UIWindow::Border)) {

    }

    m_ui.end();

    target.draw(m_ui, states);

    // WARNING: hack!

    unsigned characterSize = coordinates.getRelativeCharacterSize(0.025f);

    if (characterSize != m_currentCharacterSize) {
      gf::Log::debug("New UI with size: %u\n", characterSize);
      m_currentCharacterSize = characterSize;
      m_ui = gf::UI(m_font, m_currentCharacterSize);
    }

  }

  gf::MessageStatus InfoPanel::onBalanceOperation(gf::Id id, gf::Message *msg) {
    assert(id == BalanceOperation::type);
    BalanceOperation *operation = static_cast<BalanceOperation*>(msg);

    m_balance += operation->value;

    return gf::MessageStatus::Keep;
  }

}
