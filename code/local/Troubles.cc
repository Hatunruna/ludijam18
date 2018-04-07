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

 #include "Troubles.h"

 #include "Messages.h"
 #include "Singletons.h"

 namespace no {
   TroubleContainer::TroubleContainer() {
     gMessageManager().registerHandler<NewSourceTrouble>(&TroubleContainer::onNewSourceTrouble, this);
   }

   void TroubleContainer::update(gf::Time time) {
     for (auto &sourceTrouble: m_sourceTroubles) {
       sourceTrouble.m_effectTime += time;
     }
   }

   void TroubleContainer::render(gf::RenderTarget& target, const gf::RenderStates& states) {
     //
   }

   gf::MessageStatus TroubleContainer::onNewSourceTrouble(gf::Id id, gf::Message *msg) {
     assert(id == NewSourceTrouble::type);
     NewSourceTrouble *newTrouble = static_cast<NewSourceTrouble*>(msg);

     m_sourceTroubles.push_back(newTrouble->trouble);

     return gf::MessageStatus::Keep;
   }

   gf::MessageStatus TroubleContainer::onNewRouteTrouble(gf::Id id, gf::Message *msg) {
     assert(id == NewRouteTrouble::type);
     NewRouteTrouble *newTrouble = static_cast<NewRouteTrouble*>(msg);

     m_routeTroubles.push_back(newTrouble->trouble);

     return gf::MessageStatus::Keep;
   }

 }
