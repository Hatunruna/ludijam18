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
#ifndef NO_MESSAGES_H
#define NO_MESSAGES_H

#include <gf/Message.h>

#include "Troubles.h"

using namespace gf::literals;

namespace no {
  // TODO: Rename this...
  enum class BuildingType: int {
    Route,
    InfoTarget,
    PetrolPump = 10,
    UraniumMining = 11,
  };

  struct BuildingQuery : public gf::Message {
    static constexpr gf::Id type = "BuildingQuery"_id;

    BuildingType building;
    gf::Vector2f position;
    bool isValid;
  };

  struct RouteStartQuery : public gf::Message {
    static constexpr gf::Id type = "RouteStartQuery"_id;

    gf::Vector2f position;
    bool isValid;
  };

  struct RoutePipeQuery : public gf::Message {
    static constexpr gf::Id type = "RoutePipeQuery"_id;

    gf::Vector2f position;
    bool isValid;
    bool isEnded;
  };

  struct InfoQuery : public gf::Message {
    static constexpr gf::Id type = "InfoQuery"_id;

    gf::Vector2f position;
    bool isValid;
  };

  struct NewSourceTrouble : public gf::Message {
    static constexpr gf::Id type = "NewSourceTrouble"_id;

    SourceTrouble trouble;
  };

  struct NewRouteTrouble : public gf::Message {
    static constexpr gf::Id type = "NewRouteTrouble"_id;

    RouteTrouble trouble;
  };

  struct BalanceOperation : public gf::Message {
    static constexpr gf::Id type = "BalanceOperation"_id;

    float value;
  };

}

#endif // NO_MESSAGES_H
