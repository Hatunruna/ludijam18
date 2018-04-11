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
#include <gf/Unused.h>
#include <gf/VectorOps.h>

#include "Singletons.h"

namespace no {

  static constexpr float Padding = 20.0f;
  static constexpr gf::Vector2f WorldMapSize = gf::Vector2f(2000, 1075);

  WorldMap::WorldMap()
  : m_texture(gResourceManager().getTexture("world-map.png"))
  {
    m_texture.setSmooth();
  }

  void WorldMap::update(gf::Time time) {
    gf::unused(time);
  }

  void WorldMap::render(gf::RenderTarget& target, const gf::RenderStates& states) {
    gf::Sprite sprite(m_texture);
    sprite.setColor(gf::Color::fromRgba32(0x82, 0x66, 0x44));
    sprite.setAnchor(gf::Anchor::Center);
    target.draw(sprite, states);
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
          gf::Vector2f centerBound = WorldMapSize / 2 - m_view.getSize() / 2 + Padding;

          gf::Vector2f oldPosition = m_target.mapPixelToCoords(m_mousePosition, m_view);
          gf::Vector2f newPosition = m_target.mapPixelToCoords(event.mouseCursor.coords, m_view);

          currentCenter += (oldPosition - newPosition);
          m_view.setCenter(gf::clamp(currentCenter, -centerBound, centerBound));
        }

        m_mousePosition = event.mouseCursor.coords;
        break;

      case gf::EventType::MouseButtonPressed:
        if (event.mouseButton.button == gf::MouseButton::Right && isCursorOnView(event.mouseButton.coords, m_target.getSize(), m_view.getViewport())) {
          m_state = State::Moving;
        }
        break;

      case gf::EventType::MouseButtonReleased:
        if (event.mouseButton.button == gf::MouseButton::Right) {
          m_state = State::Stationary;
        }
        break;

      default:
        break;
    }
  }


}
