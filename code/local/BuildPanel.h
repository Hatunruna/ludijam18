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
#ifndef NO_BUILD_PANEL_H
#define NO_BUILD_PANEL_H

#include <gf/Entity.h>
#include <gf/Event.h>
#include <gf/Sprite.h>
#include <gf/Texture.h>
#include <gf/WidgetContainer.h>
#include <gf/Widgets.h>

#include "Messages.h"

namespace no {

  class BuildMenu : public gf::Entity {
  public:
    BuildMenu();

    void pointTo(gf::Vector2f position);
    void pressed(gf::MouseButton button, gf::Vector2f worldPosition);

    gf::WidgetContainer& getWidgetContainer();
    virtual void update(gf::Time time) override;
    virtual void render(gf::RenderTarget& target, const gf::RenderStates& states) override;

  private:
    enum class State {
      Idle,
      BuildSelected,
      RouteMakerSource,
      RouteMakerPipe,
      InfoTarget,
    };

  private:
    // State system
    State m_state;

    // Texture and widgets
    // Oil pump
    gf::Texture& m_oilPumpTexture;
    gf::Sprite m_oilPumpSprite;
    gf::SpriteWidget m_oilPumpWidget;

    // Uranium Mining
    gf::Texture& m_uraniumMiningTexture;
    gf::Sprite m_uraniumMiningSprite;
    gf::SpriteWidget m_uraniumMiningWidget;

    // Route
    gf::Texture& m_routeTexture;
    gf::Sprite m_routeSprite;
    gf::SpriteWidget m_routeWidget;

    // Info
    gf::Texture& m_infoTexture;
    gf::Sprite m_infoSprite;
    gf::SpriteWidget m_infoWidget;

    gf::WidgetContainer m_widgets;

    // Cursor
    gf::Vector2f m_mousePosition;
    BuildingType m_selectedBuilding;
  };

}

#endif // NO_BUILD_PANEL_H
