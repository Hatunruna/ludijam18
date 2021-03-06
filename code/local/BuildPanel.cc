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
#include "BuildPanel.h"

#include <gf/Coordinates.h>
#include <gf/Curves.h>
#include <gf/Log.h>
#include <gf/RenderTarget.h>
#include <gf/Shapes.h>
#include <gf/VectorOps.h>

#include "GameConstants.h"
#include "Singletons.h"

namespace no {

  BuildMenu::BuildMenu()
  : m_state(State::Idle)
  , m_oilPumpTexture(gResourceManager().getTexture("oil-pump.png"))
  , m_oilPumpWidget(m_oilPumpSprite)
  , m_uraniumMiningTexture(gResourceManager().getTexture("uranium-mining.png"))
  , m_uraniumMiningWidget(m_uraniumMiningSprite)
  , m_routeTexture(gResourceManager().getTexture("route.png"))
  , m_routeWidget(m_routeSprite)
  , m_infoTexture(gResourceManager().getTexture("info.png"))
  , m_infoWidget(m_infoSprite)
  , m_selectedBuilding(BuildingType::PetrolPump)
  {
    m_oilPumpTexture.setSmooth();

    // Sprite for building
    gf::WidgetContainer widgets;

    // Widget for pump oil
    m_oilPumpSprite.setTexture(m_oilPumpTexture);
    m_oilPumpWidget.setCallback([this]() {
      m_state = State::BuildSelected;
      m_selectedBuilding = BuildingType::PetrolPump;
    });
    m_widgets.addWidget(m_oilPumpWidget);

    // Widget for uranium
    m_uraniumMiningSprite.setTexture(m_uraniumMiningTexture);
    m_uraniumMiningWidget.setCallback([this]() {
      m_state = State::BuildSelected;
      m_selectedBuilding = BuildingType::UraniumMining;

    });
    m_widgets.addWidget(m_uraniumMiningWidget);

    // Widget for route
    m_routeSprite.setTexture(m_routeTexture);
    m_routeWidget.setCallback([this]() {
      m_state = State::RouteMakerSource;
      m_selectedBuilding = BuildingType::Route;

    });
    m_widgets.addWidget(m_routeWidget);

    // Widget for info
    m_infoSprite.setTexture(m_infoTexture);
    m_infoWidget.setCallback([this]() {
      m_state = State::InfoTarget;
      m_selectedBuilding = BuildingType::InfoTarget;

    });
    m_widgets.addWidget(m_infoWidget);
  }

  void BuildMenu::pointTo(gf::Vector2f position) {
    m_mousePosition = position;
    m_widgets.pointTo(m_mousePosition);
  }

  void BuildMenu::pressed(gf::MouseButton button, gf::Vector2f worldPosition) {
    if (button == gf::MouseButton::Left) {
      switch (m_state) {
      case State::Idle:
        m_widgets.triggerAction();
        break;

      case State::BuildSelected:
        {
          BuildingQuery query;
          query.building = m_selectedBuilding;
          query.position = worldPosition;
          query.isValid = false;
          gMessageManager().sendMessage(&query);

          if (query.isValid) {
            BalanceOperation operation;
            if (m_selectedBuilding == BuildingType::PetrolPump) {
              operation.value = -BuildCostOilPump;
            }
            else if (m_selectedBuilding == BuildingType::UraniumMining) {
              operation.value = -BuildCostUraniumMining;
            }
            else {
              assert(false);
            }
            gMessageManager().sendMessage(&operation);

            m_state = State::Idle;
          }
          else { // To allow change building without select and build in one clic
            m_widgets.triggerAction();
          }
        }
        break;

      case State::RouteMakerSource:
        {
          RouteStartQuery query;
          query.position = worldPosition;
          query.isValid = false;
          gMessageManager().sendMessage(&query);

          if (query.isValid) {
            m_state = State::RouteMakerPipe;
          }
          else { // To allow change building without select and build in one clic
            m_widgets.triggerAction();
          }
        }
        break;

      case State::RouteMakerPipe:
      {
        RoutePipeQuery query;
        query.position = worldPosition;
        query.isValid = false;
        query.isEnded = false;
        gMessageManager().sendMessage(&query);

        if (query.isValid) {
          if (query.isEnded) {
            m_state = State::Idle;
          }
        }
        else { // To allow change building without select and build in one clic
          m_widgets.triggerAction();
        }
      }
      break;

      case State::InfoTarget:
      {
        InfoQuery query;
        query.position = worldPosition;
        query.isValid = false;
        gMessageManager().sendMessage(&query);

        if (!query.isValid) {
          m_widgets.triggerAction();
        }
      }
      break;

      default:
        assert(false);
      }
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

    // Info
    auto position = coordinates.getRelativePoint({ MenuPadding, MenuPadding });
    size = coordinates.getRelativeSize({ MenuRelativeSize.width - MenuPadding * 2, MenuRelativeSize.height });
    auto padding = coordinates.getRelativeSize({ MenuPadding, MenuPadding });
    m_infoSprite.setScale(size.width / WidgetSize);
    m_infoSprite.setPosition(position);

    // Pump oil
    position.y += size.width + padding.width;
    size = coordinates.getRelativeSize({ MenuRelativeSize.width - MenuPadding * 2, MenuRelativeSize.height });
    m_oilPumpSprite.setScale(size.width / WidgetSize);
    m_oilPumpSprite.setPosition(position);

    // Uranium mining
    position.y += size.width + padding.width;
    size = coordinates.getRelativeSize({ MenuRelativeSize.width - MenuPadding * 2, MenuRelativeSize.height });
    m_uraniumMiningSprite.setScale(size.width / WidgetSize);
    m_uraniumMiningSprite.setPosition(position);

    // Route
    position.y += size.width + padding.width;
    size = coordinates.getRelativeSize({ MenuRelativeSize.width - MenuPadding * 2, MenuRelativeSize.height });
    m_routeSprite.setScale(size.width / WidgetSize);
    m_routeSprite.setPosition(position);

    m_widgets.render(target, states);

    if (m_state == State::BuildSelected || m_state == State::RouteMakerSource || m_state == State::InfoTarget) {
      // Drawing the cursor
      gf::Sprite cursor;
      switch (m_selectedBuilding) {
      case BuildingType::PetrolPump:
        cursor.setTexture(m_oilPumpTexture);
        break;

      case BuildingType::UraniumMining:
        cursor.setTexture(m_uraniumMiningTexture);
        break;

      case BuildingType::Route:
        cursor.setTexture(m_routeTexture);
        break;

      case BuildingType::InfoTarget:
        cursor.setTexture(m_infoTexture);
        break;

      default:
        assert(false);
      }
      cursor.setColor(gf::Color::Opaque(0.5f));
      cursor.setPosition({m_mousePosition.x, m_mousePosition.y});
      cursor.setScale(size.width / WidgetSize);
      cursor.setAnchor(gf::Anchor::Center);

      target.draw(cursor);
    }
  }

}
