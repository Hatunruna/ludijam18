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

#include <gf/Curves.h>
#include <gf/RenderTarget.h>
#include <gf/Shapes.h>

namespace no {

#if 0
  static constexpr Location Locations[] = {
    /*
     * consumers
     */

    { LocationType::Consumer, { -44.7143f, -270.833f } }, // Europe
    { LocationType::Consumer, { 156.971f, -306.424f } }, // Russia

    { LocationType::Consumer, { -545.688f, -200.521f } }, // US, East Coast
    { LocationType::Consumer, { -807.028f, -222.222f } }, // US, West Coast

    { LocationType::Consumer, { -327.507f, 141.493f } }, // Brazil

    { LocationType::Consumer, { 75.3562f, 283.854f } }, // South Africa

    { LocationType::Consumer, { 450.797f, -89.618f } }, // India
    { LocationType::Consumer, { 754.319f, -197.049f } }, // Japan-Korea
    { LocationType::Consumer, { 649.008f, -133.681f } }, // China

    { LocationType::Consumer, { 838.538f, 270.833f } }, // Australia

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
    { LocationType::UraniumSource, { 766.474f, 296.007f } }, // Australia
    { LocationType::UraniumSource, { -20.1503f, -46.007f } }, // Niger
    { LocationType::UraniumSource, { 117.032f, -358.507f } }, // Russia
    { LocationType::UraniumSource, { 28.4711f, 214.41f } }, // Namibia

  };
#endif

  Globe::Globe()
  {

    /*
     * consumers
     */

    auto consEurope = addLocation("Europe", LocationType::Consumer, { -44.7143f, -270.833f });
    auto consRussia = addLocation("Russia", LocationType::Consumer, { 158.426f, -298.9f });
    auto consUsaEastCoast = addLocation("USA, East Coast", LocationType::Consumer, { -545.688f, -200.521f });
    auto consUsaWestCoast = addLocation("USA, West Coast", LocationType::Consumer, { -807.028f, -222.222f });
    auto consBrazil = addLocation("Brazil", LocationType::Consumer, { -327.507f, 141.493f });
    auto consSouthAfrica = addLocation("South Africa", LocationType::Consumer, { 75.3562f, 283.854f });
    auto consIndia = addLocation("India", LocationType::Consumer, { 450.797f, -89.618f });
    auto consJapan = addLocation("Japan", LocationType::Consumer, { 754.319f, -197.049f });
    auto consChina = addLocation("China", LocationType::Consumer, { 649.008f, -133.681f });
    auto consAustralia = addLocation("Australia", LocationType::Consumer, { 838.538f, 270.833f });

    /*
     * oil sources
     */

    auto oilKuweit = addLocation("Kuwait", LocationType::OilSource, { 227.913f, -144.097f });
    auto oilSaudi = addLocation("Saudi Arabia", LocationType::OilSource, { 256.565f, -105.903f });
    auto oilIraq = addLocation("Iraq", LocationType::OilSource, { 194.92f, -197.917f });
    auto oilAlgeria = addLocation("Algeria", LocationType::OilSource, { -56.0014f, -140.625f });
    auto oilNigeria = addLocation("Nigeria", LocationType::OilSource, { -25.613f, 36.4583f });
    auto oilNothSea = addLocation("North Sea", LocationType::OilSource, { -73.3661f, -371.528f });
    auto oilAlaska = addLocation("Alaska", LocationType::OilSource, { -788.18f, -410.799f });
    auto oilCanada = addLocation("Canada", LocationType::OilSource, { -698.752f, -323.993f });
    auto oilMexico = addLocation("Mexico", LocationType::OilSource, { -669.232f, -80.0694f });
    auto oilTexas = addLocation("Texas", LocationType::OilSource, { -682.255f, -157.326f });
    auto oilVenezuela = addLocation("Venezuela", LocationType::OilSource, { -505.134f, -8.02088f });
    auto oilEcuador = addLocation("Ecuador", LocationType::OilSource, { -599.772f, 72.7083f });
    auto oilArgentina = addLocation("Argentina", LocationType::OilSource, { -459.986f, 380.868f });
    auto oilCaspianSea = addLocation("Caspian Sea", LocationType::OilSource, { 243.288f, -262.361f });
    auto oilUral = addLocation("Ural", LocationType::OilSource, { 206.822f, -354.375f });
    auto oilSiberia = addLocation("Siberia", LocationType::OilSource, { 331.848f, -389.097f });
    auto oilIndia = addLocation("India", LocationType::OilSource, { 402.175f, -82.6735f });
    auto oilChinaEast = addLocation("China, East", LocationType::OilSource, { 663.515f, -251.944f });
    auto oilChinaWest = addLocation("China, West", LocationType::OilSource, { 447.324f, -232.847f });
    auto oilIndonesia = addLocation("Indonesia", LocationType::OilSource, { 601.87f, 84.8611f });

    /*
     * uranium sources
     */

    auto urKazakhstan = addLocation("Kazakhstan", LocationType::UraniumSource, { 352.071f, -250.868f });
    auto urCanada = addLocation("Canada", LocationType::UraniumSource, { -497.935f, -286.458f });
    auto urAustralia = addLocation("Australia", LocationType::UraniumSource, { 766.474f, 296.007f });
    auto urNiger = addLocation("Niger", LocationType::UraniumSource, { -20.1503f, -46.007f });
    auto urRussia = addLocation("Russia", LocationType::UraniumSource, { 117.032f, -358.507f });
    auto urNamiba = addLocation("Namibia", LocationType::UraniumSource, { 28.4711f, 214.41f });

    /*
     * pipelines
     */

    auto locUsaCentral = addAnonymousLocation({ -653.964f, -202.917f });
    auto locAlgeria = addAnonymousLocation({ -44.7142f, -194.444f });
    auto locMediterraneanSeaWest = addAnonymousLocation({ -3.03857f, -216.146f });
    auto locMediterraneanSeaCenter = addAnonymousLocation({ 40.3731f, -183.16f });
    auto locMediterraneanSeaEast = addAnonymousLocation({ 115.91f, -177.083f });

    auto locRussiaCentral = addAnonymousLocation({ 380.108f, -349.826f });
    auto locChinaCentral = addAnonymousLocation({ 601.255f, -182.292f });
    auto locChinaEast = addAnonymousLocation({ 674.933f, -192.882f });
    auto locRussiaWest = addAnonymousLocation({ 148.903f, -326.389f });
    auto locRussiaUral = addAnonymousLocation({ 226.176f, -310.764f });

    auto locAlaska = addAnonymousLocation({ -844.616f, -355.903f });
    auto locPacificEast = addAnonymousLocation({ -866.322f, -232.639f });
    auto locPacificCalifornia = addAnonymousLocation({ -820.92f, -84.2014f });
    auto locPacificSouth = addAnonymousLocation({ -693.542f, 324.861f });

    auto locPanamaSouth = addAnonymousLocation({ -648.394f, 24.3054f });
    auto locPanamaNorth = addAnonymousLocation({ -570.252f, -36.4585f });
    auto locCarribeanSea = addAnonymousLocation({ -530.313f, -120.66f });
    auto locMexicoGulf = addAnonymousLocation({ -636.841f, -113.021f });

    auto locAtlanticWest = addAnonymousLocation({ -468.415f, -59.8958f });
    auto locAtlanticBrittany = addAnonymousLocation({ -167.136f, -289.062f });
    auto locAtlanticGibraltar = addAnonymousLocation({ -178.796f, -184.166f });
    auto locAtlanticAzores = addAnonymousLocation({ -288.428f, -66.5509f });
    auto locAtlanticEquator = addAnonymousLocation({ -181.028f, 110.243f });
    auto locAtlanticSouth = addAnonymousLocation({ -162.795f, 298.611f });
    auto locAtlanticArgentina = addAnonymousLocation({ -307.407f, 388.518f });
    auto locCapeHorn = addAnonymousLocation({ -453.952f, 498.472f });

    auto locCapeGoodHope = addAnonymousLocation({ 63.5184f, 384.722f });
    auto locIndianMadagascar = addAnonymousLocation({ 314.737f, 243.056f });
    auto locIndianSomalia = addAnonymousLocation({ 284.348f, -22.5694f });
    auto locIndianIndia = addAnonymousLocation({ 387.669f, 10.4167f });
    auto locIndianIndonesia = addAnonymousLocation({ 603.86f, 131.944f });

    auto locRedSea = addAnonymousLocation({ 167.136f, -105.903f });
    auto locAdenGulf = addAnonymousLocation({ 213.153f, -17.3611f });
    auto locPersicGulf = addAnonymousLocation({ 265.247f, -119.792f });
    auto locOmanGulf = addAnonymousLocation({ 328.628f, -98.0903f });

    auto locTurkey = addAnonymousLocation({ 105.491f, -219.618f });




    addRoute(locUsaCentral, oilTexas);
    addRoute(locUsaCentral, consUsaEastCoast);
    addRoute(locUsaCentral, consUsaWestCoast);



    addRoute(locRussiaWest, consRussia);
    addRoute(locRussiaWest, oilUral);
    addRoute(oilUral, oilSiberia);
    addRoute(locRussiaWest, urRussia);
    addRoute(locRussiaWest, locRussiaUral);
    addRoute(oilCaspianSea, locRussiaUral);
    addRoute(locRussiaWest, consEurope);

    addRoute(locRussiaCentral, locRussiaUral);
    addRoute(oilChinaWest, locRussiaCentral);
    addRoute(oilChinaWest, locChinaCentral);
    addRoute(oilChinaEast, locChinaCentral);
    addRoute(locChinaCentral, consChina);
    addRoute(oilChinaEast, locChinaEast);
    addRoute(locChinaEast, consJapan);

    addRoute(oilAlgeria, locAlgeria);
    addRoute(locAlgeria, locMediterraneanSeaWest);

    addRoute(locMediterraneanSeaWest, consEurope);
    addRoute(locMediterraneanSeaCenter, locMediterraneanSeaEast);
    addRoute(locMediterraneanSeaCenter, locMediterraneanSeaWest);

    addRoute(oilAlaska, locAlaska);
    addRoute(locAlaska, locPacificEast);
    addRoute(locPacificEast, consUsaWestCoast);
    addRoute(locPacificEast, locPacificCalifornia);
    addRoute(locPacificCalifornia, locPanamaSouth);
    addRoute(locPanamaSouth, locPanamaNorth);
    addRoute(locPanamaNorth, locCarribeanSea);
    addRoute(locCarribeanSea, consUsaEastCoast);

    addRoute(oilVenezuela, locAtlanticWest);
    addRoute(locCarribeanSea, locAtlanticWest);
    addRoute(locPanamaNorth, locAtlanticWest);

    addRoute(oilTexas, locMexicoGulf);
    addRoute(oilMexico, locMexicoGulf);
    addRoute(locMexicoGulf, locCarribeanSea);
    addRoute(oilEcuador, locPanamaSouth);

    addRoute(oilCanada, consUsaWestCoast);
    addRoute(oilCanada, consUsaEastCoast);

    addRoute(oilNothSea, locAtlanticBrittany);
    addRoute(oilNothSea, consEurope);
    addRoute(consEurope, locAtlanticBrittany);
    addRoute(locAtlanticBrittany, locAtlanticGibraltar);
    addRoute(locAtlanticGibraltar, locAlgeria);
    addRoute(locAtlanticGibraltar, locAtlanticAzores);
    addRoute(locAtlanticAzores, locAtlanticWest);
    addRoute(locAtlanticAzores, locAtlanticEquator);
    addRoute(locAtlanticEquator, oilNigeria);
    addRoute(locAtlanticEquator, consBrazil);
    addRoute(locAtlanticEquator, locAtlanticSouth);
    addRoute(locAtlanticSouth, urNamiba);
    addRoute(locAtlanticSouth, locAtlanticArgentina);
    addRoute(locAtlanticArgentina, oilArgentina);
    addRoute(locAtlanticArgentina, locCapeHorn);
    addRoute(locAtlanticSouth, locCapeGoodHope);

    addRoute(locCapeHorn, locPacificSouth);
    addRoute(locPacificSouth, oilEcuador);

    addRoute(locCapeGoodHope, consSouthAfrica);
    addRoute(locCapeGoodHope, locIndianMadagascar);
    addRoute(locIndianMadagascar, locIndianSomalia);

    addRoute(locIndianSomalia, locAdenGulf);
    addRoute(locAdenGulf, locRedSea);
    addRoute(locRedSea, locMediterraneanSeaEast);
    addRoute(locRedSea, oilSaudi);

    addRoute(oilKuweit, oilIraq);
    addRoute(oilIraq, locTurkey);

    addRoute(locTurkey, consRussia);
    addRoute(locTurkey, consEurope);
    addRoute(locTurkey, locMediterraneanSeaCenter);

    addRoute(oilKuweit, locPersicGulf);
    addRoute(oilSaudi, locPersicGulf);
    addRoute(locPersicGulf, locOmanGulf);
    addRoute(locOmanGulf, locIndianSomalia);

    addRoute(locOmanGulf, locIndianIndia);
    addRoute(oilIndia, locIndianIndia);
    addRoute(oilIndia, consIndia);
    addRoute(locIndianIndia, locIndianIndonesia);
    addRoute(locIndianIndonesia, oilIndonesia);

  }

  void Globe::update(gf::Time time) {

  }

  void Globe::render(gf::RenderTarget& target, const gf::RenderStates& states) {
    for (auto& route : m_routes) {
      auto pos0 = m_locations[route.endPoint0].position;
      auto pos1 = m_locations[route.endPoint1].position;

      gf::Line line(pos0, pos1);
      line.setColor(gf::Color::Gray() * gf::Color::Opaque(0.7f));
      line.setWidth(3.0f);
      line.setOutlineThickness(0.5f);
      line.setOutlineColor(gf::Color::Gray(0.3f) * gf::Color::Opaque(0.7f));
      target.draw(line);
    }

    for (auto& loc : m_locations) {
      gf::CircleShape shape;

      switch (loc.type) {
        case LocationType::Consumer:
          shape.setRadius(40.0f);
          shape.setColor(gf::Color::Transparent);
          shape.setOutlineColor(gf::Color::Azure * gf::Color::Opaque(0.7f));
          shape.setOutlineThickness(10.0f);
          break;

        case LocationType::OilSource:
          shape.setRadius(15.0f);
          shape.setColor(gf::Color::Transparent);
          shape.setOutlineColor(gf::Color::Black * gf::Color::Opaque(0.3f));
          shape.setOutlineThickness(5.0f);
          break;

        case LocationType::UraniumSource:
          shape.setRadius(15.0f);
          shape.setColor(gf::Color::Transparent);
          shape.setOutlineColor(gf::Color::Chartreuse * gf::Color::Opaque(0.3f));
          shape.setOutlineThickness(5.0f);
          break;

        case LocationType::None:
          break;
      }

      shape.setPosition(loc.position);
      shape.setAnchor(gf::Anchor::Center);
      target.draw(shape);

      shape.setRadius(3.0f);
      shape.setColor(gf::Color::Gray());
      shape.setOutlineThickness(0.0f);
      shape.setAnchor(gf::Anchor::Center);
      target.draw(shape);
    }

  }

  std::size_t Globe::addLocation(std::string name, LocationType type, gf::Vector2f pos) {
    std::size_t id = m_locations.size();
    m_locations.push_back({ std::move(name), type, pos });
    return id;
  }

  std::size_t Globe::addAnonymousLocation(gf::Vector2f pos) {
    return addLocation("", LocationType::None, pos);
  }

  void Globe::addRoute(std::size_t endPoint0, std::size_t endPoint1) {
    m_routes.push_back({ endPoint0, endPoint1 });
  }

}
