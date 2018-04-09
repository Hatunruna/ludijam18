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
#include <gf/Vector.h>

namespace no {

  using Tick = int;

  using LocationId = std::size_t;

  struct Location {
    LocationId id;
    gf::Vector2f position;
  };

  using SourceId = std::size_t;

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

  using ConsumerId = std::size_t;

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

  using SegmentId = std::size_t;

  struct Segment {
    SegmentId id;
    LocationId endPoints[2];
    float charge;
    Tick delay;
    float length;
  };

  using RoadId = std::size_t;

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
  };

  struct EconomicModel: public gf::Model {
    EconomicModel();

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

    // state
    State state;
  };

}

#endif // NO_ECONOMIC_MODEL_H
