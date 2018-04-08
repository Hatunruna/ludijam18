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

#include <gf/Entity.h>
#include <gf/Event.h>
#include <gf/Texture.h>
#include <gf/View.h>

#include "Messages.h"

namespace no {

  using ExportPath = std::vector<std::size_t>;

  class Globe : public gf::Entity {
  public:
    Globe();

    virtual void update(gf::Time time) override;
    virtual void render(gf::RenderTarget& target, const gf::RenderStates& states) override;

    gf::MessageStatus onBuildingQuery(gf::Id id, gf::Message *msg);
    gf::MessageStatus onRouteStartQuery(gf::Id id, gf::Message *msg);
    gf::MessageStatus onRoutePipeQuery(gf::Id id, gf::Message *msg);
    gf::MessageStatus onInfoQuery(gf::Id id, gf::Message *msg);

  private:
    enum class LocationType: int {
      None,
      Consumer,
      OilSource = 10,
      UraniumSource = 11,
    };

    struct Location {
      std::string name;
      LocationType type;
      gf::Vector2f position;
      bool isBuild;

      union {
        // Consumers
        struct {
          float oilConsumption;
          float oilPrice;
        } consumerData;

        // Sources
        struct {
          float resourceProduction;
        } sourceData;
      };
    };

    struct Route {
      std::size_t endPoint0;
      std::size_t endPoint1;
      float charge;
    };

  private:
    std::size_t addLocation(std::string name, LocationType type, gf::Vector2f pos);
    std::size_t addConsumerLocation(std::string name, gf::Vector2f pos, float oilConsumptionFactor, float oilPriceFactor);
    std::size_t addSourceLocation(std::string name, LocationType type, gf::Vector2f pos, float ResourceProductionFactor);
    std::size_t addAnonymousLocation(gf::Vector2f pos);
    void addRoute(std::size_t endPoint0, std::size_t endPoint1);
    bool isValidRoute(std::size_t endPoint0, std::size_t endPoint1);
    void drawPath(gf::RenderTarget& target, ExportPath &path);
    Route findRoute(std::size_t endPoint0, std::size_t endPoint1);
    // std::vector<Location> findConsumersFormSource(std::size_t id);
    // std::vector<Location> findConsumersFormSource(std::size_t id);

  private:
    std::vector<Location> m_locations;
    std::vector<Route> m_routes;

    // Definitive route
    std::vector<ExportPath> m_exportPaths;

    // Temporary route
    ExportPath m_tempRoute;

    // Texture for resources
    gf::Texture& m_oilPumpTexture;
    gf::Texture& m_uraniumMiningTexture;
  };

}

#endif // NO_GLOBE_H
