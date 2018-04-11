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
#ifndef NO_GLOBE_H
#define NO_GLOBE_H

#include <map>

#include <gf/Entity.h>
#include <gf/Texture.h>

#include "EconomicModel.h"

namespace no {

  class Globe : public gf::Entity {
  public:
    Globe(EconomicModel &model);

    virtual void update(gf::Time time) override;
    virtual void render(gf::RenderTarget& target, const gf::RenderStates& states) override;

  private:
    void drawRoad(gf::RenderTarget& target, const gf::RenderStates& states, const Road &road) const;

  private:
    EconomicModel &m_model;
    gf::Texture& m_oilPumpTexture;
    gf::Texture& m_uraniumMiningTexture;
  };

}

#endif // NO_GLOBE_H
