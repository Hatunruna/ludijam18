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

#include <gf/Circ.h>
#include <gf/Curves.h>
#include <gf/Log.h>
#include <gf/RenderTarget.h>
#include <gf/Shapes.h>
#include <gf/Sprite.h>

#include "GameConstants.h"
#include "Singletons.h"

namespace no {

  Globe::Globe()
  : m_nextIDPath(0)
  , m_oilPumpTexture(gResourceManager().getTexture("oil-pump.png"))
  , m_uraniumMiningTexture(gResourceManager().getTexture("uranium-mining.png"))
  {

    /*
     * consumers
     */

    auto consEurope = addConsumerLocation("Europe", { -44.7143f, -270.833f }, 1.0f, 1.0f, 1.0f, 1.0f);
    auto consRussia = addConsumerLocation("Russia", { 158.426f, -298.9f }, 1.0f, 1.0f, 1.0f, 1.0f);
    auto consUsaEastCoast = addConsumerLocation("USA, East Coast", { -545.688f, -200.521f }, 1.0f, 1.0f, 1.0f, 1.0f);
    auto consUsaWestCoast = addConsumerLocation("USA, West Coast", { -807.028f, -222.222f }, 1.0f, 1.0f, 1.0f, 1.0f);
    auto consBrazil = addConsumerLocation("Brazil", { -327.507f, 141.493f }, 1.0f, 1.0f, 1.0f, 1.0f);
    auto consSouthAfrica = addConsumerLocation("South Africa", { 75.3562f, 283.854f }, 1.0f, 1.0f, 1.0f, 1.0f);
    auto consIndia = addConsumerLocation("India", { 450.797f, -89.618f }, 1.0f, 1.0f, 1.0f, 1.0f);
    auto consJapan = addConsumerLocation("Japan", { 754.319f, -197.049f }, 1.0f, 1.0f, 1.0f, 1.0f);
    auto consChina = addConsumerLocation("China", { 649.008f, -133.681f }, 1.0f, 1.0f, 1.0f, 1.0f);
    auto consAustralia = addConsumerLocation("Australia", { 838.538f, 270.833f }, 1.0f, 1.0f, 1.0f, 1.0f);

    /*
     * oil sources
     */

    auto oilKuweit = addSourceLocation("Kuwait", LocationType::OilSource, { 227.913f, -144.097f }, 1.0f);
    auto oilSaudi = addSourceLocation("Saudi Arabia", LocationType::OilSource, { 256.565f, -105.903f }, 1.0f);
    auto oilIraq = addSourceLocation("Iraq", LocationType::OilSource, { 194.92f, -197.917f }, 1.0f);
    auto oilAlgeria = addSourceLocation("Algeria", LocationType::OilSource, { -56.0014f, -140.625f }, 1.0f);
    auto oilNigeria = addSourceLocation("Nigeria", LocationType::OilSource, { -25.613f, 36.4583f }, 1.0f);
    auto oilNothSea = addSourceLocation("North Sea", LocationType::OilSource, { -73.3661f, -371.528f }, 1.0f);
    auto oilAlaska = addSourceLocation("Alaska", LocationType::OilSource, { -788.18f, -410.799f }, 1.0f);
    auto oilCanada = addSourceLocation("Canada", LocationType::OilSource, { -698.752f, -323.993f }, 1.0f);
    auto oilMexico = addSourceLocation("Mexico", LocationType::OilSource, { -669.232f, -80.0694f }, 1.0f);
    auto oilTexas = addSourceLocation("Texas", LocationType::OilSource, { -682.255f, -157.326f }, 1.0f);
    auto oilVenezuela = addSourceLocation("Venezuela", LocationType::OilSource, { -505.134f, -8.02088f }, 1.0f);
    auto oilEcuador = addSourceLocation("Ecuador", LocationType::OilSource, { -599.772f, 72.7083f }, 1.0f);
    auto oilArgentina = addSourceLocation("Argentina", LocationType::OilSource, { -459.986f, 380.868f }, 1.0f);
    auto oilCaspianSea = addSourceLocation("Caspian Sea", LocationType::OilSource, { 243.288f, -262.361f }, 1.0f);
    auto oilUral = addSourceLocation("Ural", LocationType::OilSource, { 206.822f, -354.375f }, 1.0f);
    auto oilSiberia = addSourceLocation("Siberia", LocationType::OilSource, { 331.848f, -389.097f }, 1.0f);
    auto oilIndia = addSourceLocation("India", LocationType::OilSource, { 402.175f, -82.6735f }, 1.0f);
    auto oilChinaEast = addSourceLocation("China, East", LocationType::OilSource, { 663.515f, -251.944f }, 1.0f);
    auto oilChinaWest = addSourceLocation("China, West", LocationType::OilSource, { 447.324f, -232.847f }, 1.0f);
    auto oilIndonesia = addSourceLocation("Indonesia", LocationType::OilSource, { 601.87f, 84.8611f }, 1.0f);

    /*
     * uranium sources
     */

    auto urKazakhstan = addSourceLocation("Kazakhstan", LocationType::UraniumSource, { 352.071f, -250.868f }, 1.0f);
    auto urCanada = addSourceLocation("Canada", LocationType::UraniumSource, { -497.935f, -286.458f }, 1.0f);
    auto urAustralia = addSourceLocation("Australia", LocationType::UraniumSource, { 766.474f, 296.007f }, 1.0f);
    auto urNiger = addSourceLocation("Niger", LocationType::UraniumSource, { -20.1503f, -46.007f }, 1.0f);
    auto urRussia = addSourceLocation("Russia", LocationType::UraniumSource, { 117.032f, -358.507f }, 1.0f);
    auto urNamiba = addSourceLocation("Namibia", LocationType::UraniumSource, { 28.4711f, 214.41f }, 1.0f);

    /*
     * route points
     */

    auto locUsaCentral = addAnonymousLocation({ -688.948f, -215.938f });
    auto locCanada = addAnonymousLocation({ -446.455f, -253.264f });

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
    auto locAtlanticSouth = addAnonymousLocation({ -207.778f, 238.518f });
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

    auto locJavaSea = addAnonymousLocation({ 629.293f, 64.2361f });
    auto locChinaSea = addAnonymousLocation({ 698.498f, -68.5764f });
    auto locCoralSea = addAnonymousLocation({ 856.771f, 149.306f });
    auto locAustralia = addAnonymousLocation({ 836.802f, 220.486f });
    auto locBenin = addAnonymousLocation({ -61.7423f, 23.7615f });


    addRoute(locUsaCentral, oilTexas);
    addRoute(locUsaCentral, consUsaEastCoast);
    addRoute(locUsaCentral, consUsaWestCoast);
    addRoute(locCanada, urCanada);
    addRoute(locCanada, locAtlanticGibraltar);
    addRoute(urCanada, consUsaEastCoast);
    addRoute(oilCanada, locUsaCentral);

    addRoute(locRussiaWest, consRussia);
    addRoute(locRussiaWest, oilUral);
    addRoute(oilUral, oilSiberia);
    addRoute(locRussiaWest, urRussia);
    addRoute(locRussiaWest, locRussiaUral);
    addRoute(oilCaspianSea, locRussiaUral);
    addRoute(locRussiaWest, consEurope);
    addRoute(locRussiaUral, urKazakhstan);

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

    addRoute(locIndianIndonesia, locIndianMadagascar);
    addRoute(locJavaSea, locIndianIndonesia);
    addRoute(locJavaSea, locChinaSea);
    addRoute(locChinaSea, consChina);
    addRoute(locChinaSea, consJapan);
    addRoute(locChinaSea, locChinaEast);
    addRoute(locIndianIndonesia, locCoralSea);

    addRoute(locCoralSea, locAustralia);
    addRoute(locAustralia, consAustralia);
    addRoute(locAustralia, urAustralia);

    addRoute(locBenin, urNiger);
    addRoute(locBenin, locAtlanticEquator);

    // Messages handlers
    gMessageManager().registerHandler<BuildingQuery>(&Globe::onBuildingQuery, this);
    gMessageManager().registerHandler<RouteStartQuery>(&Globe::onRouteStartQuery, this);
    gMessageManager().registerHandler<RoutePipeQuery>(&Globe::onRoutePipeQuery, this);
    gMessageManager().registerHandler<InfoQuery>(&Globe::onInfoQuery, this);
  }

  void Globe::update(gf::Time time) {
    float balance = 0.0f;

    // Compute maintenance charge
    for (auto &location: m_locations) {
      if (location.isBuild && (location.type == LocationType::OilSource || location.type == LocationType::UraniumSource)) {
        balance += -BuildingCharge * time.asSeconds();
      }
    }

    // For all active routes, we get the charge
    for (auto &entry: m_exportPaths) {
      ExportPath &exportPath = entry.second;
      balance += -exportPath.charge * time.asSeconds();
    }

    // Compute consumation for each consumers
    auto oilConsumption = computeConsumation(LocationType::OilSource);
    auto uraniumConsumption = computeConsumation(LocationType::UraniumSource);

    // Compute oil profit
    for (auto &entry: oilConsumption) {
      std::size_t key = entry.first;
      float realConsumption = entry.second;
      Location consumer = m_locations[key];

      // Discard the overflow
      if (realConsumption > consumer.consumerData.oilConsumption) {
        // gf::Log::debug("%s waste %f\n", consumer.name.c_str(), realConsumption-consumer.consumerData.oilConsumption);
        realConsumption = consumer.consumerData.oilConsumption;
      }

      // Compute the price
      balance += realConsumption * consumer.consumerData.oilPrice * time.asSeconds();

      // gf::Log::debug("%s profit %f\n", consumer.name.c_str(), realConsumption * consumer.consumerData.oilPrice * time.asSeconds());
    }

    // Compute uranium profit
    for (auto &entry: uraniumConsumption) {
      std::size_t key = entry.first;
      float realConsumption = entry.second;
      Location consumer = m_locations[key];

      // Discard the overflow
      if (realConsumption > consumer.consumerData.uraniumConsumption) {
        // gf::Log::debug("%s waste %f\n", consumer.name.c_str(), realConsumption-consumer.consumerData.oilConsumption);
        realConsumption = consumer.consumerData.uraniumConsumption;
      }

      // Compute the price
      balance += realConsumption * consumer.consumerData.uraniumPrice * time.asSeconds();

      // gf::Log::debug("%s profit %f\n", consumer.name.c_str(), realConsumption * consumer.consumerData.oilPrice * time.asSeconds());
    }

    BalanceOperation operation;
    operation.value = balance;
    gMessageManager().sendMessage(&operation);
  }

  static constexpr float ResourcesRadius = 15.0f;

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

    // Draw active route
    for (auto &entry: m_exportPaths) {
      drawPath(target, entry.second);
    }

    // Draw the temporary path
    if (m_tempRoute.waypoints.size() > 0) {
      drawPath(target, m_tempRoute);
    }

    for (auto& loc : m_locations) {
      if (loc.isBuild) {
        gf::Sprite sprite;

        switch (loc.type) {
          case LocationType::OilSource:
            sprite.setTexture(m_oilPumpTexture);
            break;

          case LocationType::UraniumSource:
            sprite.setTexture(m_uraniumMiningTexture);
            break;

          default:
            assert(false);
        }

        sprite.setScale(50.0f / 256.0f); // WorldSize / SpriteSize
        sprite.setPosition(loc.position);
        sprite.setAnchor(gf::Anchor::Center);
        target.draw(sprite);
      }
      else {
        gf::CircleShape shape;

        switch (loc.type) {
          case LocationType::Consumer:
            shape.setRadius(40.0f);
            shape.setColor(gf::Color::Transparent);
            shape.setOutlineColor(gf::Color::Azure * gf::Color::Opaque(0.7f));
            shape.setOutlineThickness(10.0f);
            break;

          case LocationType::OilSource:
            shape.setRadius(ResourcesRadius);
            shape.setColor(gf::Color::Transparent);
            shape.setOutlineColor(gf::Color::Black * gf::Color::Opaque(0.3f));
            shape.setOutlineThickness(5.0f);
            break;

          case LocationType::UraniumSource:
            shape.setRadius(ResourcesRadius);
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
  }

  gf::MessageStatus Globe::onBuildingQuery(gf::Id id, gf::Message *msg) {
    assert(id == BuildingQuery::type);
    BuildingQuery *query = static_cast<BuildingQuery*>(msg);

    m_tempRoute.clear();

    // Check if the build is valid
    for (auto &location: m_locations) {
      // Dirty cast
      int locationType = static_cast<int>(location.type);
      int buildingType = static_cast<int>(query->building);

      // Create circle to check position
      gf::CircF circle(location.position, ResourcesRadius);
      if (locationType == buildingType && !location.isBuild && circle.contains(query->position)) {
        location.isBuild = true;
        query->isValid = true;

        break;
      }
    }

    return gf::MessageStatus::Keep;
  }

  gf::MessageStatus Globe::onRouteStartQuery(gf::Id id, gf::Message *msg) {
    assert(id == RouteStartQuery::type);
    RouteStartQuery *query = static_cast<RouteStartQuery*>(msg);

    // Check if the build is valid
    for (std::size_t i = 0; i < m_locations.size(); ++i) {
      auto &location = m_locations[i];
      // Create circle to check position
      gf::CircF circle(location.position, ResourcesRadius);
      if ((location.type == LocationType::OilSource || location.type == LocationType::UraniumSource) && location.isBuild && circle.contains(query->position)) {
        query->isValid = true;
        m_tempRoute.clear();
        m_tempRoute.waypoints.push_back(i);

        break;
      }
    }

    return gf::MessageStatus::Keep;
  }

  gf::MessageStatus Globe::onRoutePipeQuery(gf::Id id, gf::Message *msg) {
    assert(id == RoutePipeQuery::type);
    RoutePipeQuery *query = static_cast<RoutePipeQuery*>(msg);

    static constexpr float WaypointHitbox = 10.0f;

    // Check if the build is valid
    for (std::size_t i = 0; i < m_locations.size(); ++i) {
      auto &location = m_locations[i];

      // Create circle to check position
      gf::CircF circle(location.position, WaypointHitbox);
      std::size_t previousLocation = m_tempRoute.waypoints.back();
      if (circle.contains(query->position) && previousLocation == i) {
        query->isValid = true;
        query->isEnded = false;
        m_tempRoute.waypoints.pop_back();

        break;
      }
      else if (circle.contains(query->position) && isValidRoute(previousLocation, i)) {
        query->isValid = true;
        query->isEnded = location.type == LocationType::Consumer;

        // Update the charge
        Route route = findRoute(m_tempRoute.waypoints.back(), i);
        m_tempRoute.charge += route.charge;

        m_tempRoute.waypoints.push_back(i);

        if (query->isEnded) {
          m_exportPaths.emplace(std::pair<std::size_t, ExportPath>(m_nextIDPath, m_tempRoute));
          ++m_nextIDPath;

          m_tempRoute.clear();
        }

        break;
      }
    }

    return gf::MessageStatus::Keep;
  }

  gf::MessageStatus Globe::onInfoQuery(gf::Id id, gf::Message *msg) {
    assert(id == InfoQuery::type);
    InfoQuery *query = static_cast<InfoQuery*>(msg);

    m_tempRoute.clear();

    static constexpr float ResourcesHitbox = ResourcesRadius;

    // Check if the build is valid
    for (std::size_t i = 0; i < m_locations.size(); ++i) {
      auto &location = m_locations[i];

      // Create circle to check position
      gf::CircF circle(location.position, ResourcesHitbox);

      if (circle.contains(query->position)) {
        query->isValid = true;

        switch (location.type) {
          case LocationType::OilSource:
          case LocationType::UraniumSource:
            {
              DisplaySource message;
              message.name = location.name;
              message.resourceProduction = location.sourceData.resourceProduction;

              gMessageManager().sendMessage(&message);
            }

            return gf::MessageStatus::Keep;

          case LocationType::Consumer:
            {
              DisplayConsumer message;
              message.name = location.name;
              message.oilConsumption = location.consumerData.oilConsumption;
              message.oilPrice = location.consumerData.oilPrice;

              gMessageManager().sendMessage(&message);
            }

            return gf::MessageStatus::Keep;

          default:
            break;
        }

        break;
      }
    }

    query->isValid = false;

    DisplayNone message;
    gMessageManager().sendMessage(&message);

    return gf::MessageStatus::Keep;
  }

  std::size_t Globe::addLocation(std::string name, LocationType type, gf::Vector2f pos) {
    std::size_t id = m_locations.size();
    Location loc;
    loc.name = std::move(name);
    loc.type = type;
    loc.position = pos;
    loc.isBuild = false;

    m_locations.push_back(std::move(loc));
    return id;
  }

  std::size_t Globe::addConsumerLocation(std::string name, gf::Vector2f pos, float oilConsumptionFactor, float oilPriceFactor, float uraniumConsumptionFactor, float uraniumPriceFactor) {
    std::size_t id = m_locations.size();
    Location loc;
    loc.name = std::move(name);
    loc.type = LocationType::Consumer;
    loc.position = pos;
    loc.isBuild = false;
    loc.consumerData.oilConsumption = BaseOilConsumption * oilConsumptionFactor;
    loc.consumerData.oilPrice = BasePriceOil * oilPriceFactor;
    loc.consumerData.uraniumConsumption = BaseUraniumConsumption * uraniumConsumptionFactor;
    loc.consumerData.uraniumPrice = BasePriceUranium * uraniumPriceFactor;

    m_locations.push_back(std::move(loc));
    return id;
  }
  std::size_t Globe::addSourceLocation(std::string name, LocationType type, gf::Vector2f pos, float ResourceProductionFactor) {
    std::size_t id = m_locations.size();
    Location loc;
    loc.name = std::move(name);
    loc.type = type;
    loc.position = pos;
    loc.isBuild = false;

    if (type == LocationType::OilSource) {
      loc.sourceData.resourceProduction = BaseOilProduction * ResourceProductionFactor;
    }
    else if (type == LocationType::UraniumSource) {
      loc.sourceData.resourceProduction = BaseUraniumProduction * ResourceProductionFactor;
    }
    else {
      assert(false);
    }

    m_locations.push_back(std::move(loc));
    return id;
  }

  std::size_t Globe::addAnonymousLocation(gf::Vector2f pos) {
    return addLocation("", LocationType::None, pos);
  }

  void Globe::addRoute(std::size_t endPoint0, std::size_t endPoint1) {
    m_routes.push_back({ endPoint0, endPoint1, RouteCharge });
  }

  bool Globe::isValidRoute(std::size_t endPoint0, std::size_t endPoint1) {
    for (std::size_t i = 0; i < m_routes.size(); ++i) {
      auto &route = m_routes[i];

      if ((route.endPoint0 == endPoint0 && route.endPoint1 == endPoint1) || (route.endPoint0 == endPoint1 && route.endPoint1 == endPoint0)) {
        return true;
      }
    }

    return false;
  }

  void Globe::drawPath(gf::RenderTarget& target, ExportPath &path) {
    for (std::size_t i = 0; i < path.waypoints.size() - 1; ++i) {
      auto end0Pos = m_locations[path.waypoints[i]].position;
      auto end1Pos = m_locations[path.waypoints[i + 1]].position;
      gf::Line line(end0Pos, end1Pos);
      line.setColor(gf::Color::White);
      line.setWidth(3.0f);
      line.setOutlineThickness(0.5f);
      line.setOutlineColor(gf::Color::Black);
      target.draw(line);
    }
  }

  Globe::Route Globe::findRoute(std::size_t endPoint0, std::size_t endPoint1) {
    for (std::size_t i = 0; i < m_routes.size(); ++i) {
      auto &route = m_routes[i];

      if ((route.endPoint0 == endPoint0 && route.endPoint1 == endPoint1) || (route.endPoint0 == endPoint1 && route.endPoint1 == endPoint0)) {
        return route;
      }
    }

    assert(false);
    return { 0, 0, 0.0f };
  }

  std::vector<Globe::ExportPath> Globe::findExportFormSource(std::size_t id) {
    std::vector<ExportPath> paths;

    for (auto &entry: m_exportPaths) {
      ExportPath &exportPath = entry.second;
      if (exportPath.waypoints.front() == id) {
        paths.push_back(exportPath);
      }
    }

    return paths;
  }

  std::vector<Globe::ExportPath> Globe::findExportFormConsumer(std::size_t id) {
    std::vector<ExportPath> paths;

    for (auto &entry: m_exportPaths) {
      ExportPath &exportPath = entry.second;
      if (exportPath.waypoints.back() == id) {
        paths.push_back(exportPath);
      }
    }

    return paths;
  }

  std::map<std::size_t, float> Globe::computeConsumation(Globe::LocationType type) {
    assert(type == LocationType::OilSource || type == LocationType::UraniumSource);

    std::map<std::size_t, float> consumption;
    for (std::size_t i = 0; i < m_locations.size(); ++i) {
      Location &source = m_locations[i];
      // If it's a oil source
      if (source.type == type && source.isBuild) {
        // For each path form the source we get the export
        // to add the quantity to consumer and keep this in memory
        auto exportPaths = findExportFormSource(i);
        for (auto &exportPath: exportPaths) {
          // Get the id of consumers
          std::size_t consumerID = exportPath.waypoints.back();

          // If he is in memory
          auto search = consumption.find(consumerID);
          if(search != consumption.end()) {
            // TODO: delete next and uncomment the second next
            search->second += source.sourceData.resourceProduction;
            // search->second += exportPath.quantity;
          }
          // Else we create the entry
          else {
            // TODO: delete next and uncomment the second next
            consumption.emplace(std::pair<std::size_t, float>(consumerID, source.sourceData.resourceProduction));
            // oilConsumption.emplace(std::pair<std::size_t, float>(consumerID, exportPath.quantity));
          }
        }
      }
    }

    return consumption;
  }

}
