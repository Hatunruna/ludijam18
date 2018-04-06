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
#ifndef NO_WORLD_MAP_H
#define NO_WORLD_MAP_H

#include <gf/Entity.h>
#include <gf/Event.h>
#include <gf/Texture.h>
#include <gf/View.h>

namespace no {

  class WorldMap : public gf::Entity {
  public:
    WorldMap();

    virtual void update(gf::Time time) override;

    virtual void render(gf::RenderTarget& target, const gf::RenderStates& states) override;

  private:
    gf::Texture& m_texture;
  };

  class WorldView : public gf::Entity {
  public:
    WorldView(const gf::RenderTarget& target, gf::View& view);

    void processEvent(const gf::Event& event);

  private:
    const gf::RenderTarget& m_target;
    gf::View& m_view;
    gf::Vector2i m_mousePosition;

    enum class State {
      Stationary,
      Moving,
    };

    State m_state;
  };

}

#endif // NO_WORLD_MAP_H
