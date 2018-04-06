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

  enum class LocationType {
    Consumer,
    OilSource,
    UraniumSource,
  };

  struct Location {
    LocationType type;
    gf::Vector2f position;
  };

  static constexpr Location Locations[] = {
    /*
     * consumers
     */

    { LocationType::Consumer, { -44.7143f, -270.833f } }, // Europe
    { LocationType::Consumer, { 137.001f, -345.486f } }, // Russia

    { LocationType::Consumer, { -545.688f, -200.521f } }, // US, East Coast
    { LocationType::Consumer, { -807.028f, -222.222f } }, // US, West Coast

    { LocationType::Consumer, { -327.507f, 141.493f } }, // Brazil

    { LocationType::Consumer, { 75.3562f, 283.854f } }, // South Africa

    { LocationType::Consumer, { 450.797f, -89.618f } }, // India
    { LocationType::Consumer, { 754.319f, -197.049f } }, // Japan-Korea
    { LocationType::Consumer, { 649.008f, -133.681f } }, // China

    { LocationType::Consumer, { 817.7f, 301.215f } }, // Australia

    /*
     * oil sources
     */

    { LocationType::OilSource, { 227.913f, -144.097f } }, // Koweit
    { LocationType::OilSource, { 256.565f, -105.903f } }, // Saudi Arabia
    { LocationType::OilSource, { 194.92f, -197.917f } }, // Irak

    { LocationType::OilSource, { -56.0014f, -140.625f } }, // Algeria
    { LocationType::OilSource, { -25.613f, 36.4583f } }, // Nigeria

    { LocationType::OilSource, { -57.7379f, -371.528f } }, // North Sea

    { LocationType::OilSource, { -788.18f, -410.799f } }, // Alaska
    { LocationType::OilSource, { -698.752f, -323.993f } }, // Canada
    { LocationType::OilSource, { -669.232f, -80.0694f } }, // Mexico
    { LocationType::OilSource, { -682.255f, -157.326f } }, // Texas

    { LocationType::OilSource, { -505.134f, -8.02088f } }, // Venezuela
    { LocationType::OilSource, { -599.772f, 72.7083f } }, // Ecuador
    { LocationType::OilSource, { -459.986f, 380.868f } }, // Argentina

    { LocationType::OilSource, { 243.288f, -262.361f } }, // Caspian Sea
    { LocationType::OilSource, { 206.822f, -354.375f } }, // Oural
    { LocationType::OilSource, { 331.848f, -389.097f } }, // Siberia

    { LocationType::OilSource, { 402.175f, -82.6735f } }, // India
    { LocationType::OilSource, { 663.515f, -251.944f } }, // China-East
    { LocationType::OilSource, { 447.324f, -232.847f } }, // China-West

    { LocationType::OilSource, { 601.87f, 84.8611f } }, // Indonesia

    /*
     * uranium sources
     */

    { LocationType::UraniumSource, { 352.071f, -250.868f } }, // Kazakhstan
    { LocationType::UraniumSource, { -497.935f, -286.458f } }, // Canada
    { LocationType::UraniumSource, { 775.157f, 292.535f } }, // Australia
    { LocationType::UraniumSource, { -20.1503f, -46.007f } }, // Niger
    { LocationType::UraniumSource, { 117.9f, -350.694f } }, // Russia
    { LocationType::UraniumSource, { 28.4711f, 214.41f } }, // Namibia

  };

  Globe::Globe()
  {

  }

  void Globe::update(gf::Time time) {

  }

  void Globe::render(gf::RenderTarget& target, const gf::RenderStates& states) {
    for (auto& loc : Locations) {
      gf::CircleShape shape;
      shape.setColor(gf::Color::Transparent);

      switch (loc.type) {
        case LocationType::Consumer:
          shape.setRadius(40.0f);
          shape.setOutlineColor(gf::Color::Azure * gf::Color::Opaque(0.7f));
          shape.setOutlineThickness(10.0f);
          break;

        case LocationType::OilSource:
          shape.setRadius(15.0f);
          shape.setOutlineColor(gf::Color::Black * gf::Color::Opaque(0.3f));
          shape.setOutlineThickness(5.0f);
          break;

        case LocationType::UraniumSource:
          shape.setRadius(15.0f);
          shape.setOutlineColor(gf::Color::Chartreuse * gf::Color::Opaque(0.3f));
          shape.setOutlineThickness(5.0f);
          break;
      }

      shape.setPosition(loc.position);
      shape.setAnchor(gf::Anchor::Center);
      target.draw(shape);
    }

  }

}
