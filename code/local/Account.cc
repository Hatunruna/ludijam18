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
#include "Account.h"

#include <gf/Coordinates.h>
#include <gf/RenderTarget.h>
#include <gf/Text.h>

#include "Messages.h"
#include "Singletons.h"

namespace no {

  Account::Account()
  : m_balance(5000)
  , m_font(gResourceManager().getFont("liberation-sans.ttf")) {

  }

  void Account::update(gf::Time time) {

  }

  void Account::render(gf::RenderTarget& target, const gf::RenderStates& states) {
    gf::Coordinates coordinates(target);

    auto fontSize = coordinates.getRelativeCharacterSize(0.05f);
    gf::Text text("$ " + std::to_string(m_balance), m_font, fontSize);
    text.setColor(gf::Color::White);
    text.setOutlineColor(gf::Color::Black);
    text.setOutlineThickness(fontSize * 0.02f);
    text.setPosition(coordinates.getRelativePoint({ 0.99f, 0.01f }));
    text.setAnchor(gf::Anchor::TopRight);

    target.draw(text, states);
  }

}
