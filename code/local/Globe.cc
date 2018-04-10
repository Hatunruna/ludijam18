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
#include <gf/Unused.h>

#include "GameConstants.h"
#include "Singletons.h"

namespace no {

  Globe::Globe(EconomicModel &model)
  : m_model(model)
  {

  }

  void Globe::update(gf::Time time) {
    gf::unused(time);
  }

  void Globe::render(gf::RenderTarget& target, const gf::RenderStates& states) {
    for (const auto &segment: m_model.segments) {
      auto pos0 = m_model.locations[segment.endPoints[0]].position;
      auto pos1 = m_model.locations[segment.endPoints[1]].position;

      gf::Line line(pos0, pos1);
      line.setColor(gf::Color::Gray() * gf::Color::Opaque(0.7f));
      line.setWidth(3.0f);
      line.setOutlineThickness(0.5f);
      line.setOutlineColor(gf::Color::Gray(0.3f) * gf::Color::Opaque(0.7f));
      target.draw(line);
    }
    //
    // // Draw active route
    // for (auto &entry: m_exportPaths) {
    //   drawPath(target, entry.second);
    // }
    //
    // // Draw the temporary path
    // if (m_tempRoute.waypoints.size() > 0) {
    //   drawPath(target, m_tempRoute);
    // }
    //
    // Draw locations
    for (const auto &location: m_model.locations) {
      gf::CircleShape shape;
      shape.setPosition(location.position);
      shape.setRadius(3.0f);
      shape.setColor(gf::Color::Gray());
      shape.setOutlineThickness(0.0f);
      shape.setAnchor(gf::Anchor::Center);
      target.draw(shape, states);
    }

    // Draw consumers
    for (const auto &consumer: m_model.consumers) {
      gf::CircleShape shape;
      shape.setRadius(40.0f);
      shape.setColor(gf::Color::Transparent);
      shape.setOutlineColor(gf::Color::Azure * gf::Color::Opaque(0.7f));
      shape.setOutlineThickness(10.0f);
      shape.setPosition(m_model.locations[consumer.loc].position);
      shape.setAnchor(gf::Anchor::Center);
      target.draw(shape, states);
    }

    // Draw source
    for (const auto &source: m_model.sources) {
      gf::CircleShape shape;
      shape.setRadius(15.0f);
      shape.setColor(gf::Color::Transparent);
      switch (source.resource) {
      case Resource::Oil:
        shape.setOutlineColor(gf::Color::Black * gf::Color::Opaque(0.3f));
        break;
      case Resource::Uranium:
        shape.setOutlineColor(gf::Color::Chartreuse * gf::Color::Opaque(0.3f));
        break;
      }
      shape.setOutlineThickness(5.0f);
      shape.setPosition(m_model.locations[source.loc].position);
      shape.setAnchor(gf::Anchor::Center);
      target.draw(shape);
    }

    // for (auto& loc : m_locations) {
    //   if (loc.isBuild) {
    //     gf::Sprite sprite;
    //
    //     switch (loc.type) {
    //       case LocationType::OilSource:
    //         sprite.setTexture(m_oilPumpTexture);
    //         break;
    //
    //       case LocationType::UraniumSource:
    //         sprite.setTexture(m_uraniumMiningTexture);
    //         break;
    //
    //       default:
    //         assert(false);
    //     }
    //
    //     sprite.setScale(50.0f / 256.0f); // WorldSize / SpriteSize
    //     sprite.setPosition(loc.position);
    //     sprite.setAnchor(gf::Anchor::Center);
    //     target.draw(sprite);
    //   }
    //   else {
    //     gf::CircleShape shape;
    //
    //     switch (loc.type) {
    //       case LocationType::Consumer:
    //         shape.setRadius(40.0f);
    //         shape.setColor(gf::Color::Transparent);
    //         shape.setOutlineColor(gf::Color::Azure * gf::Color::Opaque(0.7f));
    //         shape.setOutlineThickness(10.0f);
    //         break;
    //
    //       case LocationType::OilSource:
    //         shape.setRadius(ResourcesRadius);
    //         shape.setColor(gf::Color::Transparent);
    //         shape.setOutlineColor(gf::Color::Black * gf::Color::Opaque(0.3f));
    //         shape.setOutlineThickness(5.0f);
    //         break;
    //
    //       case LocationType::UraniumSource:
    //         shape.setRadius(ResourcesRadius);
    //         shape.setColor(gf::Color::Transparent);
    //         shape.setOutlineColor(gf::Color::Chartreuse * gf::Color::Opaque(0.3f));
    //         shape.setOutlineThickness(5.0f);
    //         break;
    //
    //       case LocationType::None:
    //         break;
    //     }
    //
    //     shape.setPosition(loc.position);
    //     shape.setAnchor(gf::Anchor::Center);
    //     target.draw(shape);
    //
    //     shape.setRadius(3.0f);
    //     shape.setColor(gf::Color::Gray());
    //     shape.setOutlineThickness(0.0f);
    //     shape.setAnchor(gf::Anchor::Center);
    //     target.draw(shape);
    //   }
    // }
  }

}
