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
#ifndef NO_INFO_PANEL_H
#define NO_INFO_PANEL_H

#include <gf/Entity.h>
#include <gf/Font.h>
#include <gf/UI.h>

#include "EconomicModel.h"

namespace no {

  class InfoPanel: public gf::Entity {
  public:
    InfoPanel(EconomicModel &model);

    void processEvent(const gf::Event& event);

    virtual void update(gf::Time time) override;
    virtual void render(gf::RenderTarget& target, const gf::RenderStates& states) override;

  private:
    std::pair<Demand, bool> getDemand(Consumer consumer, Resource resource);

  private:
    float m_balance;
    gf::Font &m_font;

    unsigned m_currentCharacterSize;
    gf::UI m_ui;

    EconomicModel &m_model;

  };

}

#endif // NO_INFO_PANEL_H
