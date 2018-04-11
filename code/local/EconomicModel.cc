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
#include "EconomicModel.h"

#include <gf/Circ.h>
#include <gf/Log.h>
#include <gf/Model.h>
#include <gf/Unused.h>

namespace no {

  EconomicModel::EconomicModel()
  : previousLocation(InvalidId)
  , displayLocation(InvalidId)
  , state(State::Idle)
  , toolSelected(Tool::None)
  {
    /*
     * consumers
     */

    auto consEurope = createConsumer({ -44.7143f, -270.833f }, "Europe", {{Resource::Oil, { 1.0f, 1.0f }}, {Resource::Uranium, { 1.0f, 1.0f }}});
    auto consRussia = createConsumer({ 158.426f, -298.9f }, "Russia", {{Resource::Oil, { 1.0f, 1.0f }}, {Resource::Uranium, { 1.0f, 1.0f }}});
    auto consUsaEastCoast = createConsumer({ -545.688f, -200.521f }, "USA, East Coast", {{Resource::Oil, { 1.0f, 1.0f }}, {Resource::Uranium, { 1.0f, 1.0f }}});
    auto consUsaWestCoast = createConsumer({ -807.028f, -222.222f }, "USA, West Coast", {{Resource::Oil, { 1.0f, 1.0f }}, {Resource::Uranium, { 1.0f, 1.0f }}});
    auto consBrazil = createConsumer({ -327.507f, 141.493f }, "Brazil", {{Resource::Oil, { 1.0f, 1.0f }}, {Resource::Uranium, { 1.0f, 1.0f }}});
    auto consSouthAfrica = createConsumer({ 75.3562f, 283.854f }, "South Africa", {{Resource::Oil, { 1.0f, 1.0f }}, {Resource::Uranium, { 1.0f, 1.0f }}});
    auto consIndia = createConsumer({ 450.797f, -89.618f }, "India", {{Resource::Oil, { 1.0f, 1.0f }}, {Resource::Uranium, { 1.0f, 1.0f }}});
    auto consJapan = createConsumer({ 754.319f, -197.049f }, "Japan", {{Resource::Oil, { 1.0f, 1.0f }}, {Resource::Uranium, { 1.0f, 1.0f }}});
    auto consChina = createConsumer({ 649.008f, -133.681f }, "China", {{Resource::Oil, { 1.0f, 1.0f }}, {Resource::Uranium, { 1.0f, 1.0f }}});
    auto consAustralia = createConsumer({ 838.538f, 270.833f }, "Australia", {{Resource::Oil, { 1.0f, 1.0f }}, {Resource::Uranium, { 1.0f, 1.0f }}});

    /*
     * oil sources
     */

    auto oilKuweit = createSource({ 227.913f, -144.097f }, "Kuwait", Resource::Oil, 1.0f, 1.0f);
    auto oilSaudi = createSource({ 256.565f, -105.903f }, "Saudi Arabia", Resource::Oil, 1.0f, 1.0f);
    auto oilIraq = createSource({ 194.92f, -197.917f }, "Iraq", Resource::Oil, 1.0f, 1.0f);
    auto oilAlgeria = createSource({ -56.0014f, -140.625f }, "Algeria", Resource::Oil, 1.0f, 1.0f);
    auto oilNigeria = createSource({ -25.613f, 36.4583f }, "Nigeria", Resource::Oil, 1.0f, 1.0f);
    auto oilNothSea = createSource({ -73.3661f, -371.528f }, "North Sea", Resource::Oil, 1.0f, 1.0f);
    auto oilAlaska = createSource({ -788.18f, -410.799f }, "Alaska", Resource::Oil, 1.0f, 1.0f);
    auto oilCanada = createSource({ -698.752f, -323.993f }, "Canada", Resource::Oil, 1.0f, 1.0f);
    auto oilMexico = createSource({ -669.232f, -80.0694f }, "Mexico", Resource::Oil, 1.0f, 1.0f);
    auto oilTexas = createSource({ -682.255f, -157.326f }, "Texas", Resource::Oil, 1.0f, 1.0f);
    auto oilVenezuela = createSource({ -505.134f, -8.02088f }, "Venezuela", Resource::Oil, 1.0f, 1.0f);
    auto oilEcuador = createSource({ -599.772f, 72.7083f }, "Ecuador", Resource::Oil, 1.0f, 1.0f);
    auto oilArgentina = createSource({ -459.986f, 380.868f }, "Argentina", Resource::Oil, 1.0f, 1.0f);
    auto oilCaspianSea = createSource({ 243.288f, -262.361f }, "Caspian Sea", Resource::Oil, 1.0f, 1.0f);
    auto oilUral = createSource({ 206.822f, -354.375f }, "Ural", Resource::Oil, 1.0f, 1.0f);
    auto oilSiberia = createSource({ 331.848f, -389.097f }, "Siberia", Resource::Oil, 1.0f, 1.0f);
    auto oilIndia = createSource({ 402.175f, -82.6735f }, "India", Resource::Oil, 1.0f, 1.0f);
    auto oilChinaEast = createSource({ 663.515f, -251.944f }, "China, East", Resource::Oil, 1.0f, 1.0f);
    auto oilChinaWest = createSource({ 447.324f, -232.847f }, "China, West", Resource::Oil, 1.0f, 1.0f);
    auto oilIndonesia = createSource({ 601.87f, 84.8611f }, "Indonesia", Resource::Oil, 1.0f, 1.0f);

    /*
     * uranium sources
     */

    auto urKazakhstan = createSource({ 352.071f, -250.868f }, "Kazakhstan", Resource::Uranium, 1.0f, 1.0f);
    auto urCanada = createSource({ -497.935f, -286.458f }, "Canada", Resource::Uranium, 1.0f, 1.0f);
    auto urAustralia = createSource({ 766.474f, 296.007f }, "Australia", Resource::Uranium, 1.0f, 1.0f);
    auto urNiger = createSource({ -20.1503f, -46.007f }, "Niger", Resource::Uranium, 1.0f, 1.0f);
    auto urRussia = createSource({ 117.032f, -358.507f }, "Russia", Resource::Uranium, 1.0f, 1.0f);
    auto urNamiba = createSource({ 28.4711f, 214.41f }, "Namibia", Resource::Uranium, 1.0f, 1.0f);

    /*
     * route points
     */

    auto locUsaCentral = createLocation({ -688.948f, -215.938f });
    auto locCanada = createLocation({ -446.455f, -253.264f });

    auto locAlgeria = createLocation({ -44.7142f, -194.444f });
    auto locMediterraneanSeaWest = createLocation({ -3.03857f, -216.146f });
    auto locMediterraneanSeaCenter = createLocation({ 40.3731f, -183.16f });
    auto locMediterraneanSeaEast = createLocation({ 115.91f, -177.083f });

    auto locRussiaCentral = createLocation({ 380.108f, -349.826f });
    auto locChinaCentral = createLocation({ 601.255f, -182.292f });
    auto locChinaEast = createLocation({ 674.933f, -192.882f });
    auto locRussiaWest = createLocation({ 148.903f, -326.389f });
    auto locRussiaUral = createLocation({ 226.176f, -310.764f });

    auto locAlaska = createLocation({ -844.616f, -355.903f });
    auto locPacificEast = createLocation({ -866.322f, -232.639f });
    auto locPacificCalifornia = createLocation({ -820.92f, -84.2014f });
    auto locPacificSouth = createLocation({ -693.542f, 324.861f });

    auto locPanamaSouth = createLocation({ -648.394f, 24.3054f });
    auto locPanamaNorth = createLocation({ -570.252f, -36.4585f });
    auto locCarribeanSea = createLocation({ -530.313f, -120.66f });
    auto locMexicoGulf = createLocation({ -636.841f, -113.021f });

    auto locAtlanticWest = createLocation({ -468.415f, -59.8958f });
    auto locAtlanticBrittany = createLocation({ -167.136f, -289.062f });
    auto locAtlanticGibraltar = createLocation({ -178.796f, -184.166f });
    auto locAtlanticAzores = createLocation({ -288.428f, -66.5509f });
    auto locAtlanticEquator = createLocation({ -181.028f, 110.243f });
    auto locAtlanticSouth = createLocation({ -207.778f, 238.518f });
    auto locAtlanticArgentina = createLocation({ -307.407f, 388.518f });
    auto locCapeHorn = createLocation({ -453.952f, 498.472f });

    auto locCapeGoodHope = createLocation({ 63.5184f, 384.722f });
    auto locIndianMadagascar = createLocation({ 314.737f, 243.056f });
    auto locIndianSomalia = createLocation({ 284.348f, -22.5694f });
    auto locIndianIndia = createLocation({ 387.669f, 10.4167f });
    auto locIndianIndonesia = createLocation({ 603.86f, 131.944f });

    auto locRedSea = createLocation({ 167.136f, -105.903f });
    auto locAdenGulf = createLocation({ 213.153f, -17.3611f });
    auto locPersicGulf = createLocation({ 265.247f, -119.792f });
    auto locOmanGulf = createLocation({ 328.628f, -98.0903f });

    auto locTurkey = createLocation({ 105.491f, -219.618f });

    auto locJavaSea = createLocation({ 629.293f, 64.2361f });
    auto locChinaSea = createLocation({ 698.498f, -68.5764f });
    auto locCoralSea = createLocation({ 856.771f, 149.306f });
    auto locAustralia = createLocation({ 836.802f, 220.486f });
    auto locBenin = createLocation({ -61.7423f, 23.7615f });

    createSegment(locUsaCentral, oilTexas, 1.0f, 1, 1.0f);
    createSegment(locUsaCentral, consUsaEastCoast, 1.0f, 1, 1.0f);
    createSegment(locUsaCentral, consUsaWestCoast, 1.0f, 1, 1.0f);
    createSegment(locCanada, urCanada, 1.0f, 1, 1.0f);
    createSegment(locCanada, locAtlanticGibraltar, 1.0f, 1, 1.0f);
    createSegment(urCanada, consUsaEastCoast, 1.0f, 1, 1.0f);
    createSegment(oilCanada, locUsaCentral, 1.0f, 1, 1.0f);

    createSegment(locRussiaWest, consRussia, 1.0f, 1, 1.0f);
    createSegment(locRussiaWest, oilUral, 1.0f, 1, 1.0f);
    createSegment(oilUral, oilSiberia, 1.0f, 1, 1.0f);
    createSegment(locRussiaWest, urRussia, 1.0f, 1, 1.0f);
    createSegment(locRussiaWest, locRussiaUral, 1.0f, 1, 1.0f);
    createSegment(oilCaspianSea, locRussiaUral, 1.0f, 1, 1.0f);
    createSegment(locRussiaWest, consEurope, 1.0f, 1, 1.0f);
    createSegment(locRussiaUral, urKazakhstan, 1.0f, 1, 1.0f);

    createSegment(locRussiaCentral, locRussiaUral, 1.0f, 1, 1.0f);
    createSegment(oilChinaWest, locRussiaCentral, 1.0f, 1, 1.0f);
    createSegment(oilChinaWest, locChinaCentral, 1.0f, 1, 1.0f);
    createSegment(oilChinaEast, locChinaCentral, 1.0f, 1, 1.0f);
    createSegment(locChinaCentral, consChina, 1.0f, 1, 1.0f);
    createSegment(oilChinaEast, locChinaEast, 1.0f, 1, 1.0f);
    createSegment(locChinaEast, consJapan, 1.0f, 1, 1.0f);

    createSegment(oilAlgeria, locAlgeria, 1.0f, 1, 1.0f);
    createSegment(locAlgeria, locMediterraneanSeaWest, 1.0f, 1, 1.0f);

    createSegment(locMediterraneanSeaWest, consEurope, 1.0f, 1, 1.0f);
    createSegment(locMediterraneanSeaCenter, locMediterraneanSeaEast, 1.0f, 1, 1.0f);
    createSegment(locMediterraneanSeaCenter, locMediterraneanSeaWest, 1.0f, 1, 1.0f);

    createSegment(oilAlaska, locAlaska, 1.0f, 1, 1.0f);
    createSegment(locAlaska, locPacificEast, 1.0f, 1, 1.0f);
    createSegment(locPacificEast, consUsaWestCoast, 1.0f, 1, 1.0f);
    createSegment(locPacificEast, locPacificCalifornia, 1.0f, 1, 1.0f);
    createSegment(locPacificCalifornia, locPanamaSouth, 1.0f, 1, 1.0f);
    createSegment(locPanamaSouth, locPanamaNorth, 1.0f, 1, 1.0f);
    createSegment(locPanamaNorth, locCarribeanSea, 1.0f, 1, 1.0f);
    createSegment(locCarribeanSea, consUsaEastCoast, 1.0f, 1, 1.0f);

    createSegment(oilVenezuela, locAtlanticWest, 1.0f, 1, 1.0f);
    createSegment(locCarribeanSea, locAtlanticWest, 1.0f, 1, 1.0f);
    createSegment(locPanamaNorth, locAtlanticWest, 1.0f, 1, 1.0f);

    createSegment(oilTexas, locMexicoGulf, 1.0f, 1, 1.0f);
    createSegment(oilMexico, locMexicoGulf, 1.0f, 1, 1.0f);
    createSegment(locMexicoGulf, locCarribeanSea, 1.0f, 1, 1.0f);
    createSegment(oilEcuador, locPanamaSouth, 1.0f, 1, 1.0f);

    createSegment(oilNothSea, locAtlanticBrittany, 1.0f, 1, 1.0f);
    createSegment(oilNothSea, consEurope, 1.0f, 1, 1.0f);
    createSegment(consEurope, locAtlanticBrittany, 1.0f, 1, 1.0f);
    createSegment(locAtlanticBrittany, locAtlanticGibraltar, 1.0f, 1, 1.0f);
    createSegment(locAtlanticGibraltar, locAlgeria, 1.0f, 1, 1.0f);
    createSegment(locAtlanticGibraltar, locAtlanticAzores, 1.0f, 1, 1.0f);
    createSegment(locAtlanticAzores, locAtlanticWest, 1.0f, 1, 1.0f);
    createSegment(locAtlanticAzores, locAtlanticEquator, 1.0f, 1, 1.0f);
    createSegment(locAtlanticEquator, oilNigeria, 1.0f, 1, 1.0f);
    createSegment(locAtlanticEquator, consBrazil, 1.0f, 1, 1.0f);
    createSegment(locAtlanticEquator, locAtlanticSouth, 1.0f, 1, 1.0f);
    createSegment(locAtlanticSouth, urNamiba, 1.0f, 1, 1.0f);
    createSegment(locAtlanticSouth, locAtlanticArgentina, 1.0f, 1, 1.0f);
    createSegment(locAtlanticArgentina, oilArgentina, 1.0f, 1, 1.0f);
    createSegment(locAtlanticArgentina, locCapeHorn, 1.0f, 1, 1.0f);
    createSegment(locAtlanticSouth, locCapeGoodHope, 1.0f, 1, 1.0f);

    createSegment(locCapeHorn, locPacificSouth, 1.0f, 1, 1.0f);
    createSegment(locPacificSouth, oilEcuador, 1.0f, 1, 1.0f);

    createSegment(locCapeGoodHope, consSouthAfrica, 1.0f, 1, 1.0f);
    createSegment(locCapeGoodHope, locIndianMadagascar, 1.0f, 1, 1.0f);
    createSegment(locIndianMadagascar, locIndianSomalia, 1.0f, 1, 1.0f);

    createSegment(locIndianSomalia, locAdenGulf, 1.0f, 1, 1.0f);
    createSegment(locAdenGulf, locRedSea, 1.0f, 1, 1.0f);
    createSegment(locRedSea, locMediterraneanSeaEast, 1.0f, 1, 1.0f);
    createSegment(locRedSea, oilSaudi, 1.0f, 1, 1.0f);

    createSegment(oilKuweit, oilIraq, 1.0f, 1, 1.0f);
    createSegment(oilIraq, locTurkey, 1.0f, 1, 1.0f);

    createSegment(locTurkey, consRussia, 1.0f, 1, 1.0f);
    createSegment(locTurkey, consEurope, 1.0f, 1, 1.0f);
    createSegment(locTurkey, locMediterraneanSeaCenter, 1.0f, 1, 1.0f);

    createSegment(oilKuweit, locPersicGulf, 1.0f, 1, 1.0f);
    createSegment(oilSaudi, locPersicGulf, 1.0f, 1, 1.0f);
    createSegment(locPersicGulf, locOmanGulf, 1.0f, 1, 1.0f);
    createSegment(locOmanGulf, locIndianSomalia, 1.0f, 1, 1.0f);

    createSegment(locOmanGulf, locIndianIndia, 1.0f, 1, 1.0f);
    createSegment(oilIndia, locIndianIndia, 1.0f, 1, 1.0f);
    createSegment(oilIndia, consIndia, 1.0f, 1, 1.0f);
    createSegment(locIndianIndia, locIndianIndonesia, 1.0f, 1, 1.0f);
    createSegment(locIndianIndonesia, oilIndonesia, 1.0f, 1, 1.0f);

    createSegment(locIndianIndonesia, locIndianMadagascar, 1.0f, 1, 1.0f);
    createSegment(locJavaSea, locIndianIndonesia, 1.0f, 1, 1.0f);
    createSegment(locJavaSea, locChinaSea, 1.0f, 1, 1.0f);
    createSegment(locChinaSea, consChina, 1.0f, 1, 1.0f);
    createSegment(locChinaSea, consJapan, 1.0f, 1, 1.0f);
    createSegment(locChinaSea, locChinaEast, 1.0f, 1, 1.0f);
    createSegment(locIndianIndonesia, locCoralSea, 1.0f, 1, 1.0f);

    createSegment(locCoralSea, locAustralia, 1.0f, 1, 1.0f);
    createSegment(locAustralia, consAustralia, 1.0f, 1, 1.0f);
    createSegment(locAustralia, urAustralia, 1.0f, 1, 1.0f);

    createSegment(locBenin, urNiger, 1.0f, 1, 1.0f);
    createSegment(locBenin, locAtlanticEquator, 1.0f, 1, 1.0f);

    // Reset the draft road
    resetDraftRoad();

  }

  /*
   * Static data handlers
   */
  LocationId EconomicModel::createLocation(const gf::Vector2f position) {
    Location loc;
    loc.id = locations.size();
    loc.position = position;

    locations.push_back(loc);

    return loc.id;
  }

  LocationId EconomicModel::createSource(const gf::Vector2f position, const std::string &name, Resource resource, float production, float charge) {
    Source src;
    src.id = sources.size();
    src.loc = createLocation(position);
    src.name = name;
    src.resource = resource;
    src.production = production;
    src.charge = charge;

    sources.push_back(src);

    return src.loc;
  }

  LocationId EconomicModel::createConsumer(const gf::Vector2f position, const std::string &name, std::map<Resource, Demand> demands) {
    Consumer consumer;
    consumer.id = consumers.size();
    consumer.loc = createLocation(position);
    consumer.name = name;
    consumer.demands = demands;

    consumers.push_back(consumer);

    return consumer.loc;
  }

  void EconomicModel::createSegment(const LocationId id0, const LocationId id1, float charge, Tick delay, float length) {
    Segment segment;
    segment.id = segments.size();
    segment.endPoints[0] = id0;
    segment.endPoints[1] = id1;
    segment.charge = charge;
    segment.delay = delay;
    segment.length = length;

    segments.push_back(segment);
  }

  void EconomicModel::update(gf::Time time) {
    gf::unused(time);
  }

  /*
   * Dynamic handlers
   */
  static constexpr float HitboxResource = 20.0f;
  SourceId EconomicModel::searchSourceFormPosition() const {
    for (const Source &source: sources) {
      auto &position = locations[source.loc].position;
      gf::CircF circ(position, HitboxResource);

      if (circ.contains(worldPosition)) {
        return source.id;
      }
    }

    return InvalidId;
  }

  SourceId EconomicModel::searchSourceFormPosition(Resource resource) const {
    for (const Source &source: sources) {
      auto &position = locations[source.loc].position;
      gf::CircF circ(position, HitboxResource);

      if (source.resource == resource && circ.contains(worldPosition)) {
        return source.id;
      }
    }

    return InvalidId;
  }

  void EconomicModel::resetDraftRoad() {
    draftRoad.id = InvalidId;
    draftRoad.waypoints.clear();
    draftRoad.length = 0.0f;
    draftRoad.delay = 0;
    draftRoad.quantity = 0.0f;
    draftRoad.charge = 0.0f;
    draftRoad.state = RoadState::Active;
    draftRoad.packages = std::move(std::queue<Package>());

    previousLocation = InvalidId;
  }

  RoadId EconomicModel::selectNextRoadPoint() {
    // If it's the first point
    if (draftRoad.waypoints.size() == 0 && previousLocation == InvalidId) {
      auto sourceId = searchSourceFormPosition();

      // it must be a built source
      if (sourceId != InvalidId && built.count(sourceId) == 1) {
        auto source = sources[sourceId];
        previousLocation = source.loc;
      }

      return InvalidId;
    }

    // If it's the next waypoint we get the current location
    LocationId locId = searchLocationFormPosition();

    // And we check if it's a valid segment
    SegmentId segId = isValidSegment(previousLocation, locId);
    if (segId != InvalidId) {
      previousLocation = locId;

      Segment seg = segments[segId];
      draftRoad.charge += seg.charge;
      draftRoad.delay += seg.delay;
      draftRoad.length += seg.length;
      draftRoad.waypoints.push_back(seg.id);
    }

    // If the location is a consumers, we create the road
    for (auto consumer: consumers) {
      if (consumer.loc == locId) {
        RoadId id = roads.size();
        draftRoad.id = id;
        roads.insert({ draftRoad.id, draftRoad });
        resetDraftRoad();

        return id;
      }
    }

    return InvalidId;
  }

  std::vector<gf::Vector2f> EconomicModel::searchNeighborLocation(const LocationId locationId) {
    std::vector<gf::Vector2f> neighbors;
    for (Segment seg: segments) {
      if (seg.endPoints[0] == locationId) {
        neighbors.push_back(locations[seg.endPoints[1]].position);
      }
      else if (seg.endPoints[1] == locationId) {
        neighbors.push_back(locations[seg.endPoints[0]].position);
      }
    }

    return neighbors;
  }

  static constexpr float HitboxLocation = 15.0f;
  LocationId EconomicModel::searchLocationFormPosition() const {
    for (const Location &location: locations) {
      auto &position = location.position;
      gf::CircF circ(position, HitboxLocation);

      if (circ.contains(worldPosition)) {
        return location.id;
      }
    }

    return InvalidId;
  }


  SegmentId EconomicModel::isValidSegment(LocationId locId0, LocationId locId1) const {
    for (auto seg: segments) {
      if ((seg.endPoints[0] == locId0 && seg.endPoints[1] == locId1) || (seg.endPoints[0] == locId1 && seg.endPoints[1] == locId0)) {
        return seg.id;
      }
    }

    return InvalidId;
  }

  SourceId EconomicModel::isSource(LocationId locId) const {
    for (auto &source: sources) {
      if (source.loc == locId) {
        return source.id;
      }
    }

    return InvalidId;
  }

  ConsumerId EconomicModel::isConsumer(LocationId locId) const {
    for (auto &consumer: consumers) {
      if (consumer.loc == locId) {
        return consumer.id;
      }
    }

    return InvalidId;
  }

}
