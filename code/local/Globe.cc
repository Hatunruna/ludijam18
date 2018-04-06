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
#include "Globe.h"

#include <gf/RenderTarget.h>
#include <gf/Shapes.h>

namespace no {

  static constexpr gf::Vector2f Consumers[] = {
    { -44.7143, -270.833 }, // Europe
    { 137.001, -345.486 }, // Russia

    { -545.688, -200.521 }, // US, East Coast
    { -807.028, -222.222 }, // US, West Coast

    { -327.507, 141.493 }, // Brazil

    { 75.3562, 283.854 }, // South Africa

    { 450.797, -89.618 }, // India
    { 754.319, -197.049 }, // Japan-Korea
    { 649.008, -133.681 }, // China

    { 817.7, 301.215 }, // Australia
  };

  static constexpr gf::Vector2f OilSources[] = {
    { 227.913, -144.097 }, // Koweit
    { 256.565, -105.903 }, // Saudi Arabia
    { 194.92, -197.917 }, // Irak

    { -56.0014, -140.625 }, // Algeria
    { -25.613, 36.4583 }, // Nigeria

    { -57.7379, -371.528 }, // North Sea

    { -788.18, -410.799 }, // Alaska
    { -698.752, -323.993 }, // Canada
    { -669.232, -80.0694 }, // Mexico
    { -682.255, -157.326 }, // Texas

    { -505.134, -8.02088 }, // Venezuela
    { -599.772, 72.7083 }, // Ecuador
    { -459.986, 380.868 }, // Argentina

    { 243.288, -262.361 }, // Caspian Sea
    { 206.822, -354.375 }, // Oural
    { 331.848, -389.097 }, // Siberia

    { 402.175, -82.6735 }, // India
    { 663.515, -251.944 }, // China-East
    { 447.324, -232.847 }, // China-West

    { 601.87, 84.8611 }, // Indonesia
  };



  static constexpr gf::Vector2f UraniumSources[] = {
    { 352.071, -250.868 }, // Kazakhstan
    { -497.935, -286.458 }, // Canada
    { 775.157, 292.535 }, // Australia
    { -20.1503, -46.007 }, // Niger
    { 117.9, -350.694 }, // Russia
    { 28.4711, 214.41 }, // Namibia
  };

  Globe::Globe()
  {

  }

  void Globe::update(gf::Time time) {

  }

  void Globe::render(gf::RenderTarget& target, const gf::RenderStates& states) {
    for (auto& pos : Consumers) {
      gf::CircleShape shape(40.0f);
      shape.setColor(gf::Color::Transparent);
      shape.setOutlineColor(gf::Color::Azure * gf::Color::Opaque(0.7f));
      shape.setOutlineThickness(10.0f);
      shape.setPosition(pos);
      shape.setAnchor(gf::Anchor::Center);
      target.draw(shape);
    }

    for (auto& pos : OilSources) {
      gf::CircleShape shape(15.0f);
      shape.setColor(gf::Color::Transparent);
      shape.setOutlineColor(gf::Color::Black * gf::Color::Opaque(0.3f));
      shape.setOutlineThickness(5.0f);
      shape.setPosition(pos);
      shape.setAnchor(gf::Anchor::Center);
      target.draw(shape);
    }

    for (auto& pos : UraniumSources) {
      gf::CircleShape shape(15.0f);
      shape.setColor(gf::Color::Transparent);
      shape.setOutlineColor(gf::Color::Chartreuse * gf::Color::Opaque(0.3f));
      shape.setOutlineThickness(5.0f);
      shape.setPosition(pos);
      shape.setAnchor(gf::Anchor::Center);
      target.draw(shape);
    }
  }

}
