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
#ifndef NO_ECONOMIC_MODEL_H
#define NO_ECONOMIC_MODEL_H

#include <map>
#include <queue>
#include <set>
#include <string>
#include <vector>

#include <gf/Model.h>
#include <gf/Rect.h>
#include <gf/Vector.h>

namespace no {

  using Tick = int;

  using LocationId = std::ptrdiff_t;
  constexpr std::ptrdiff_t InvalidId = -1;

  struct Location {
    LocationId id;
    gf::Vector2f position;
  };

  using SourceId = std::ptrdiff_t;

  enum class Resource {
    Oil,
    Uranium,
  };

  struct Source {
    SourceId id;
    LocationId loc;
    std::string name;
    Resource resource;
    float production;
    float charge;
  };

  using ConsumerId = std::ptrdiff_t;

  struct Demand {
    float consumption = 0.0f;
    float price = 0.0f;
  };

  struct Consumer {
    ConsumerId id;
    LocationId loc;
    std::string name;
    std::map<Resource, Demand> demands;
  };

  using SegmentId = std::ptrdiff_t;

  struct Segment {
    SegmentId id;
    LocationId endPoints[2];
    float charge;
    Tick delay;
    float length;
  };

  using RoadId = std::ptrdiff_t;

  struct Package {
    Tick remaining;
    float quantity;
  };

  enum class RoadState {
    Active,
    Stopped,
  };

  struct Road {
    RoadId id;
    std::vector<SegmentId> waypoints;
    float length = 0.0f;
    Tick delay = 0;

    float quantity = 0.0f;
    float charge = 0.0f;
    RoadState state;

    std::queue<Package> packages;
  };

  struct Effect {
    RoadId road;
    float quantity;
    float charge;
    RoadState state;
  };

  template<typename Id>
  struct Trouble {
    Id where;
    Tick duration;
    float cost;
    Effect on;
    Effect off;
  };

  enum class State {
    Idle,
    ToolSelected,
  };

  enum class Tool {
    None,
    Info,
    OilBuilder,
    UraniumBuilder,
    RoadBuilder,
  };

  struct EconomicModel: public gf::Model {
    EconomicModel();

    // Static data handler
    LocationId createLocation(const gf::Vector2f position);
    LocationId createSource(const gf::Vector2f position, const std::string &name, Resource resource, float production, float charge);
    LocationId createConsumer(const gf::Vector2f position, const std::string &name, std::map<Resource, Demand> demands);
    void createSegment(const LocationId id0, const LocationId id1, float charge, Tick delay, float length);

    // Dynamic handlers
    SourceId searchSourceFormPosition() const;
    SourceId searchSourceFormPosition(Resource resource) const;
    void resetState();
    RoadId selectNextRoadPoint();
    std::vector<gf::Vector2f> searchNeighborLocation(const LocationId locationId);
    LocationId searchLocationFormPosition() const;
    SegmentId isValidSegment(LocationId locId0, LocationId locId1) const;
    SourceId isSource(LocationId locId) const;
    ConsumerId isConsumer(LocationId locId) const;

    virtual void update(gf::Time time) override;

    // static
    std::vector<Location> locations;
    std::vector<Source> sources;
    std::vector<Consumer> consumers;
    std::vector<Segment> segments;

    // dynamic
    std::set<SourceId> built;
    std::map<RoadId, Road> roads;

    std::vector<Trouble<LocationId>> sourceTrouble;
    std::vector<Trouble<SegmentId>> segmentTrouble;

    // Draft road
    Road draftRoad;
    LocationId previousLocation;

    // Display location
    LocationId displayLocation;

    // state
    State state;
    Tool toolSelected;
    gf::Vector2f worldPosition;
    gf::Vector2f screenPosition;
    gf::RectF fieldOfView;
  };

}

#endif // NO_ECONOMIC_MODEL_H
