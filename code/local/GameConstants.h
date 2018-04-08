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

#ifndef NO_GAME_CONSTANTS
#define NO_GAME_CONSTANTS

namespace no {

  // Build cost
  static constexpr float BuildCostOilPump = 100.0f;
  static constexpr float BuildCostUraniumMining = 200.0f;

  // Consumption
  static constexpr float BaseOilConsumption = 100.0f;

  // Price
  static constexpr float BasePriceOil = 0.50f;

  // Production
  static constexpr float BaseOilProduction = 50.0f;

  /// FOR DEBUG
  static constexpr float BuildingCharge = 1.0f; // 1/sec
  static constexpr float RouteCharge = 0.20f; // 1/sec
}

#endif
