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
#include <gf/Unused.h>

#include <gf/Log.h>

#include "Messages.h"
#include "Singletons.h"

namespace no {

  InfoPanel::InfoPanel(EconomicModel &model)
  : m_balance(5000.0f)
  , m_font(gResourceManager().getFont("liberation-sans.ttf"))
  , m_currentCharacterSize(14)
  , m_ui(m_font, m_currentCharacterSize)
  , m_model(model)
  {

  }

  void InfoPanel::processEvent(const gf::Event& event) {
    m_ui.processEvent(event);
  }

  void InfoPanel::update(gf::Time time) {
    gf::unused(time);
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
      if (m_model.displayLocation != InvalidId) {
        // If it's a source
        SourceId sourceId = m_model.isSource(m_model.displayLocation);
        ConsumerId consumerId = m_model.isConsumer(m_model.displayLocation);
        if (sourceId != InvalidId) {
          Source source = m_model.sources[sourceId];

          m_ui.layoutRow(gf::UILayout::Dynamic, height, { 0.5f, 0.5f });
          m_ui.label("Name:");
          m_ui.label(source.name);
          m_ui.label("Production:");
          m_ui.label(gf::niceNum(source.production, 0.1f));
          m_ui.label("Charge:");
          m_ui.label(gf::niceNum(source.charge, 0.1f));
        }
        else if (consumerId != InvalidId) {
          Consumer consumer = m_model.consumers[consumerId];

          m_ui.layoutRow(gf::UILayout::Dynamic, height, { 0.3f, 0.7f });
          m_ui.label("Name:");
          m_ui.label(consumer.name);

          m_ui.separator(height / 2);

          auto oilDemand = getDemand(consumer, Resource::Oil);
          if (oilDemand.second) {
            m_ui.layoutRowDynamic(height, 1);
            m_ui.label("Oil", gf::UIAlignment::Center);
            m_ui.layoutRow(gf::UILayout::Dynamic, height, { 0.6f, 0.4f });
            m_ui.label("Consumption:");
            m_ui.label(gf::niceNum(oilDemand.first.consumption, 0.1f));
            m_ui.label("Price:");
            m_ui.label(gf::niceNum(oilDemand.first.price, 0.2f));
          }

          auto uraniumDemand = getDemand(consumer, Resource::Oil);
          if (oilDemand.second) {
            m_ui.layoutRowDynamic(height, 1);
            m_ui.label("Uranium", gf::UIAlignment::Center);
            m_ui.layoutRow(gf::UILayout::Dynamic, height, { 0.6f, 0.4f });
            m_ui.label("Consumption:");
            m_ui.label(gf::niceNum(uraniumDemand.first.consumption, 0.1f));
            m_ui.label("Price:");
            m_ui.label(gf::niceNum(uraniumDemand.first.price, 0.2f));
          }
        }
      }
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

  std::pair<Demand, bool> InfoPanel::getDemand(Consumer consumer, Resource resource) {
    auto search = consumer.demands.find(resource);
    if (search != consumer.demands.end()) {
      return { search->second, true };
    }

    return { { 0.0f, 0.0f }, false };
  }

}
