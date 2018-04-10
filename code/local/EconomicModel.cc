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

#include <gf/Model.h>

namespace no {

  EconomicModel::EconomicModel()
  : state(State::Idle)
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
    //
    // /*
    //  * route points
    //  */
    //
    // auto locUsaCentral = addAnonymousLocation({ -688.948f, -215.938f });
    // auto locCanada = addAnonymousLocation({ -446.455f, -253.264f });
    //
    // auto locAlgeria = addAnonymousLocation({ -44.7142f, -194.444f });
    // auto locMediterraneanSeaWest = addAnonymousLocation({ -3.03857f, -216.146f });
    // auto locMediterraneanSeaCenter = addAnonymousLocation({ 40.3731f, -183.16f });
    // auto locMediterraneanSeaEast = addAnonymousLocation({ 115.91f, -177.083f });
    //
    // auto locRussiaCentral = addAnonymousLocation({ 380.108f, -349.826f });
    // auto locChinaCentral = addAnonymousLocation({ 601.255f, -182.292f });
    // auto locChinaEast = addAnonymousLocation({ 674.933f, -192.882f });
    // auto locRussiaWest = addAnonymousLocation({ 148.903f, -326.389f });
    // auto locRussiaUral = addAnonymousLocation({ 226.176f, -310.764f });
    //
    // auto locAlaska = addAnonymousLocation({ -844.616f, -355.903f });
    // auto locPacificEast = addAnonymousLocation({ -866.322f, -232.639f });
    // auto locPacificCalifornia = addAnonymousLocation({ -820.92f, -84.2014f });
    // auto locPacificSouth = addAnonymousLocation({ -693.542f, 324.861f });
    //
    // auto locPanamaSouth = addAnonymousLocation({ -648.394f, 24.3054f });
    // auto locPanamaNorth = addAnonymousLocation({ -570.252f, -36.4585f });
    // auto locCarribeanSea = addAnonymousLocation({ -530.313f, -120.66f });
    // auto locMexicoGulf = addAnonymousLocation({ -636.841f, -113.021f });
    //
    // auto locAtlanticWest = addAnonymousLocation({ -468.415f, -59.8958f });
    // auto locAtlanticBrittany = addAnonymousLocation({ -167.136f, -289.062f });
    // auto locAtlanticGibraltar = addAnonymousLocation({ -178.796f, -184.166f });
    // auto locAtlanticAzores = addAnonymousLocation({ -288.428f, -66.5509f });
    // auto locAtlanticEquator = addAnonymousLocation({ -181.028f, 110.243f });
    // auto locAtlanticSouth = addAnonymousLocation({ -207.778f, 238.518f });
    // auto locAtlanticArgentina = addAnonymousLocation({ -307.407f, 388.518f });
    // auto locCapeHorn = addAnonymousLocation({ -453.952f, 498.472f });
    //
    // auto locCapeGoodHope = addAnonymousLocation({ 63.5184f, 384.722f });
    // auto locIndianMadagascar = addAnonymousLocation({ 314.737f, 243.056f });
    // auto locIndianSomalia = addAnonymousLocation({ 284.348f, -22.5694f });
    // auto locIndianIndia = addAnonymousLocation({ 387.669f, 10.4167f });
    // auto locIndianIndonesia = addAnonymousLocation({ 603.86f, 131.944f });
    //
    // auto locRedSea = addAnonymousLocation({ 167.136f, -105.903f });
    // auto locAdenGulf = addAnonymousLocation({ 213.153f, -17.3611f });
    // auto locPersicGulf = addAnonymousLocation({ 265.247f, -119.792f });
    // auto locOmanGulf = addAnonymousLocation({ 328.628f, -98.0903f });
    //
    // auto locTurkey = addAnonymousLocation({ 105.491f, -219.618f });
    //
    // auto locJavaSea = addAnonymousLocation({ 629.293f, 64.2361f });
    // auto locChinaSea = addAnonymousLocation({ 698.498f, -68.5764f });
    // auto locCoralSea = addAnonymousLocation({ 856.771f, 149.306f });
    // auto locAustralia = addAnonymousLocation({ 836.802f, 220.486f });
    // auto locBenin = addAnonymousLocation({ -61.7423f, 23.7615f });

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

  SourceId EconomicModel::createSource(const gf::Vector2f position, const std::string &name, Resource resource, float production, float charge) {
    Source src;
    src.id = sources.size();
    src.loc = createLocation(position);
    src.name = name;
    src.resource = resource;
    src.production = production;
    src.charge = charge;

    sources.push_back(src);

    return src.id;
  }

  ConsumerId EconomicModel::createConsumer(const gf::Vector2f position, const std::string &name, std::map<Resource, Demand> demands) {
    Consumer consumer;
    consumer.id = consumers.size();
    consumer.loc = createLocation(position);
    consumer.name = name;
    consumer.demands = demands;

    consumers.push_back(consumer);

    return consumer.id;
  }

  void EconomicModel::update(gf::Time time) {
  }

}
