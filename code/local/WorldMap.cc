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
#include "WorldMap.h"

#include <gf/RenderTarget.h>
#include <gf/Sprite.h>
#include <gf/VectorOps.h>

#include "Singletons.h"

namespace no {

  static constexpr float ViewSize = 500.0f;
  static constexpr gf::Vector2f WorldMapSize = gf::Vector2f(1920.0f, 982.0f);

  WorldMap::WorldMap()
  : m_texture(gResourceManager().getTexture("world-map.png"))
  {
    m_texture.setSmooth();
  }

  void WorldMap::update(gf::Time time) {

  }

  void WorldMap::render(gf::RenderTarget& target, const gf::RenderStates& states) {
    gf::Sprite sprite(m_texture);
    sprite.setAnchor(gf::Anchor::Center);
    target.draw(sprite);
  }

  /*
   * WorldView
   */

  WorldView::WorldView(const gf::RenderTarget& target, gf::View& view)
  : m_target(target)
  , m_view(view)
  , m_mousePosition({ 0, 0 })
  , m_state(State::Stationary)
  {

  }

  namespace {

    bool isCursorOnView(gf::Vector2i cursor, gf::Vector2u screenSize, const gf::RectF& viewport) {
      gf::RectF visible(viewport.getPosition() * screenSize, viewport.getSize() * screenSize);
      return visible.contains(cursor);
    }

  }

  void WorldView::processEvent(const gf::Event& event) {
    switch (event.type) {
      case gf::EventType::MouseMoved:
        if (m_state == State::Moving) {
          gf::Vector2f currentCenter = m_view.getCenter();
          gf::Vector2f centerBound = WorldMapSize / 2 - m_view.getSize() / 2;

          gf::Vector2f oldPosition = m_target.mapPixelToCoords(m_mousePosition, m_view);
          gf::Vector2f newPosition = m_target.mapPixelToCoords(event.mouseCursor.coords, m_view);

          currentCenter += (oldPosition - newPosition);
          m_view.setCenter(gf::clamp(currentCenter, -centerBound, centerBound));
        }

        m_mousePosition = event.mouseCursor.coords;
        break;

      case gf::EventType::MouseButtonPressed:
        if (isCursorOnView(event.mouseButton.coords, m_target.getSize(), m_view.getViewport())) {
          m_state = State::Moving;
        }
        break;

      case gf::EventType::MouseButtonReleased:
        m_state = State::Stationary;
        break;

      default:
        break;
    }
  }


}
