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
#include <gf/Unused.h>
#include <gf/VectorOps.h>

#include "GameConstants.h"
#include "Singletons.h"

namespace no {

  BuildMenu::BuildMenu(EconomicModel &model)
  : m_model(model)
  , m_oilPumpTexture(gResourceManager().getTexture("oil-pump.png"))
  , m_oilPumpWidget(m_oilPumpSprite)
  , m_uraniumMiningTexture(gResourceManager().getTexture("uranium-mining.png"))
  , m_uraniumMiningWidget(m_uraniumMiningSprite)
  , m_routeTexture(gResourceManager().getTexture("route.png"))
  , m_routeWidget(m_routeSprite)
  , m_infoTexture(gResourceManager().getTexture("info.png"))
  , m_infoWidget(m_infoSprite)
  {
    m_oilPumpTexture.setSmooth();
    m_uraniumMiningTexture.setSmooth();
    m_routeTexture.setSmooth();
    m_infoTexture.setSmooth();

    // Sprite for building
    // Widget for pump oil
    m_oilPumpSprite.setTexture(m_oilPumpTexture);
    m_oilPumpWidget.setCallback([this]() {
      m_model.state = State::ToolSelected;
      m_model.toolSelected = Tool::OilBuilder;
      m_model.resetDraftRoad();
    });
    m_widgets.addWidget(m_oilPumpWidget);

    // Widget for uranium
    m_uraniumMiningSprite.setTexture(m_uraniumMiningTexture);
    m_uraniumMiningWidget.setCallback([this]() {
      m_model.state = State::ToolSelected;
      m_model.toolSelected = Tool::UraniumBuilder;
      m_model.resetDraftRoad();
    });
    m_widgets.addWidget(m_uraniumMiningWidget);

    // Widget for route
    m_routeSprite.setTexture(m_routeTexture);
    m_routeWidget.setCallback([this]() {
      m_model.state = State::ToolSelected;
      m_model.toolSelected = Tool::RoadBuilder;
      m_model.resetDraftRoad();
    });
    m_widgets.addWidget(m_routeWidget);

    // Widget for info
    m_infoSprite.setTexture(m_infoTexture);
    m_infoWidget.setCallback([this]() {
      m_model.state = State::ToolSelected;
      m_model.toolSelected = Tool::Info;
      m_model.resetDraftRoad();
    });
    m_widgets.addWidget(m_infoWidget);
  }

  void BuildMenu::pressed(gf::MouseButton button) {
    m_widgets.pointTo(m_model.screenPosition);

    if (button == gf::MouseButton::Left) {
      m_widgets.triggerAction();

      switch (m_model.state) {
      case State::Idle:
        gf::Log::debug("State::Idle\n");
        break;
      case State::ToolSelected:
        // If the click is on the map we check the target
        if (!m_model.fieldOfView.contains(m_model.worldPosition)) {
          break;
        }

        // Manage the right tool
        switch (m_model.toolSelected) {
        case Tool::OilBuilder:
        {
          auto sourceId = m_model.searchSourceFormPosition(Resource::Oil);

          // If it's a correct position
          if (sourceId != InvalidId) {
            auto res = m_model.built.insert(sourceId);

            if (res.second) {
              gf::Log::debug("Spend money!\n");
              m_model.state = State::Idle;
            }
          }

          break;
        }

        case Tool::UraniumBuilder:
        {
          auto sourceId = m_model.searchSourceFormPosition(Resource::Uranium);

          // If it's a correct position
          if (sourceId != InvalidId) {
            auto res = m_model.built.insert(sourceId);

            if (res.second) {
              gf::Log::debug("Spend money!\n");
              m_model.state = State::Idle;
            }
          }

          break;
        }

        case Tool::RoadBuilder:
        {
          auto roadId = m_model.selectNextRoadPoint();

          // End of road
          if (roadId != InvalidId) {
            m_model.state = State::Idle;
          }
          break;
        }

        case Tool::Info:
        {
          auto locationId = m_model.searchLocationFormPosition();
          m_model.displayLocation = locationId;
          break;
        }

        default:
          // Never happend
          assert(false);
          break;
        }
        break;
      }
    }
    // if (button == gf::MouseButton::Left) {
    //   switch (m_state) {
    //   case State::Idle:
    //     m_widgets.triggerAction();
    //     break;
    //
    //   case State::BuildSelected:
    //     {
    //       BuildingQuery query;
    //       query.building = m_selectedBuilding;
    //       query.position = worldPosition;
    //       query.isValid = false;
    //       gMessageManager().sendMessage(&query);
    //
    //       if (query.isValid) {
    //         BalanceOperation operation;
    //         if (m_selectedBuilding == BuildingType::PetrolPump) {
    //           operation.value = -BuildCostOilPump;
    //         }
    //         else if (m_selectedBuilding == BuildingType::UraniumMining) {
    //           operation.value = -BuildCostUraniumMining;
    //         }
    //         else {
    //           assert(false);
    //         }
    //         gMessageManager().sendMessage(&operation);
    //
    //         m_state = State::Idle;
    //       }
    //       else { // To allow change building without select and build in one clic
    //         m_widgets.triggerAction();
    //       }
    //     }
    //     break;
    //
    //   case State::RouteMakerSource:
    //     {
    //       RouteStartQuery query;
    //       query.position = worldPosition;
    //       query.isValid = false;
    //       gMessageManager().sendMessage(&query);
    //
    //       if (query.isValid) {
    //         m_state = State::RouteMakerPipe;
    //       }
    //       else { // To allow change building without select and build in one clic
    //         m_widgets.triggerAction();
    //       }
    //     }
    //     break;
    //
    //   case State::RouteMakerPipe:
    //   {
    //     RoutePipeQuery query;
    //     query.position = worldPosition;
    //     query.isValid = false;
    //     query.isEnded = false;
    //     gMessageManager().sendMessage(&query);
    //
    //     if (query.isValid) {
    //       if (query.isEnded) {
    //         m_state = State::Idle;
    //       }
    //     }
    //     else { // To allow change building without select and build in one clic
    //       m_widgets.triggerAction();
    //     }
    //   }
    //   break;
    //
    //   case State::InfoTarget:
    //   {
    //     InfoQuery query;
    //     query.position = worldPosition;
    //     query.isValid = false;
    //     gMessageManager().sendMessage(&query);
    //
    //     if (!query.isValid) {
    //       m_widgets.triggerAction();
    //     }
    //   }
    //   break;
    //
    //   default:
    //     assert(false);
    //   }
    // }
  }

  void BuildMenu::update(gf::Time time) {
    gf::unused(time);
    // gf::Log::debug("(%f;%f)\n", m_mousePosition.x, m_mousePosition.y);
  }

  void BuildMenu::render(gf::RenderTarget& target, const gf::RenderStates& states) {
    gf::Coordinates coordinates(target);

    // Drawing the menu
    static constexpr float WidgetSize = 256.0f;
    static constexpr float MenuPadding = 0.01f;
    static constexpr gf::Vector2f MenuRelativeSize = { 0.075f, 1.0f };

    auto menySize = coordinates.getRelativeSize(MenuRelativeSize);
    gf::RectangleShape rect;
    rect.setSize(menySize);
    rect.setColor(gf::Color::White);

    target.draw(rect, states);

    // Info
    auto position = coordinates.getRelativePoint({ MenuPadding, MenuPadding });
    auto size = coordinates.getRelativeSize({ MenuRelativeSize.width - MenuPadding * 2, MenuRelativeSize.height });
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

    // If a tool is selected and is in the right area
    auto limit = m_model.fieldOfView.getTopRight().x;
    if (m_model.state == State::ToolSelected && m_model.worldPosition.x < limit) {
      gf::Sprite cursor;
      switch (m_model.toolSelected) {
      case Tool::OilBuilder:
        cursor.setTexture(m_oilPumpTexture);
        break;

      case Tool::UraniumBuilder:
        cursor.setTexture(m_uraniumMiningTexture);
        break;

      case Tool::RoadBuilder:
        cursor.setTexture(m_routeTexture);
        break;

      case Tool::Info:
        cursor.setTexture(m_infoTexture);
        break;

      default:
        assert(false);
      }
      cursor.setColor(gf::Color::Opaque(0.5f));
      cursor.setPosition(m_model.screenPosition);
      cursor.setScale(size.width / WidgetSize);
      cursor.setAnchor(gf::Anchor::Center);

      target.draw(cursor, states);
    }

    // if (m_state == State::BuildSelected || m_state == State::RouteMakerSource || m_state == State::InfoTarget) {
    //   // Drawing the cursor
    //   gf::Sprite cursor;
    //   switch (m_selectedBuilding) {
    //   case BuildingType::PetrolPump:
    //     cursor.setTexture(m_oilPumpTexture);
    //     break;
    //
    //   case BuildingType::UraniumMining:
    //     cursor.setTexture(m_uraniumMiningTexture);
    //     break;
    //
    //   case BuildingType::Route:
    //     cursor.setTexture(m_routeTexture);
    //     break;
    //
    //   case BuildingType::InfoTarget:
    //     cursor.setTexture(m_infoTexture);
    //     break;
    //
    //   default:
    //     assert(false);
    //   }
    //   cursor.setColor(gf::Color::Opaque(0.5f));
    //   cursor.setPosition({m_mousePosition.x, m_mousePosition.y});
    //   cursor.setScale(size.width / WidgetSize);
    //   cursor.setAnchor(gf::Anchor::Center);
    //
    //   target.draw(cursor);
    // }
  }

}
