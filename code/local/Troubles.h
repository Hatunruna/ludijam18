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

#ifndef NO_TROUBLES_H
#define NO_TROUBLES_H

#include <string>

#include <gf/Entity.h>
#include <gf/Event.h>
#include <gf//Message.h>

namespace no {

  struct SourceTrouble {
    gf::Time m_effectTime;
    long m_cancelCost;
    gf::Vector2f m_position;
    std::string m_description;
    std::size_t m_sourceID;
  };

  struct RouteTrouble {
    gf::Time m_effectTime;
    long m_cancelCost;
    gf::Vector2f m_position;
    std::string m_description;
    std::size_t m_routeID[2];
  };

  class TroubleContainer: public gf::Entity {
  public:
    TroubleContainer();

    virtual void update(gf::Time time) override;
    virtual void render(gf::RenderTarget& target, const gf::RenderStates& states) override;

    gf::MessageStatus onNewSourceTrouble(gf::Id id, gf::Message *msg);
    gf::MessageStatus onNewRouteTrouble(gf::Id id, gf::Message *msg);

  private:
    std::vector<SourceTrouble> m_sourceTroubles;
    std::vector<RouteTrouble> m_routeTroubles;
  };

}

#endif // NO_TROUBLES_H
