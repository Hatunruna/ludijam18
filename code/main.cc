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
#include <iostream>

#include <gf/Action.h>
#include <gf/Clock.h>
#include <gf/Color.h>
#include <gf/Cursor.h>
#include <gf/EntityContainer.h>
#include <gf/Event.h>
#include <gf/ModelContainer.h>
#include <gf/RenderWindow.h>
#include <gf/ViewContainer.h>
#include <gf/Views.h>
#include <gf/Window.h>

#include "local/BuildPanel.h"
#include "local/Globe.h"
#include "local/InfoPanel.h"
#include "local/Singletons.h"
#include "local/WorldMap.h"

#include "config.h"

int main() {
  static constexpr gf::Vector2u ScreenSize(1024, 576);
  static constexpr gf::Vector2f ViewSize(500.0f, 500.0f); // dummy values
  static constexpr gf::Vector2f ViewCenter(0.0f, 0.0f); // dummy values

  // initialization

  gf::Window window("NO Inc.", ScreenSize);
  window.setVerticalSyncEnabled(true);
  window.setFramerateLimit(60);

  gf::Cursor cursor;
  cursor.loadFromSystem(gf::Cursor::Cross);
  window.setMouseCursor(cursor);

  gf::RenderWindow renderer(window);

  // singletons

  gf::SingletonStorage<gf::ResourceManager> storageForResourceManager(no::gResourceManager);
  no::gResourceManager().addSearchDir(NOINC_DATA_DIR);

  gf::SingletonStorage<gf::MessageManager> storageForMessageManager(no::gMessageManager);
  gf::SingletonStorage<gf::Random> storageForRandom(no::gRandom);

  // views

  gf::ViewContainer views;

  gf::ExtendView mainView(ViewCenter, ViewSize);
  mainView.setViewport({0.075f, 0.0f, 0.725f, 1.0f});
  views.addView(mainView);

  gf::ScreenView hudView;
  views.addView(hudView);

  views.setInitialScreenSize(ScreenSize);

  no::WorldView adaptor(renderer, mainView);

  // actions

  gf::ActionContainer actions;

  gf::Action closeWindowAction("Close window");
  closeWindowAction.addCloseControl();
  closeWindowAction.addKeycodeKeyControl(gf::Keycode::Escape);
  actions.addAction(closeWindowAction);

  gf::Action fullscreenAction("Fullscreen");
  fullscreenAction.addKeycodeKeyControl(gf::Keycode::F);
  actions.addAction(fullscreenAction);

  gf::Action leftAction("Left");
  leftAction.addScancodeKeyControl(gf::Scancode::A);
  leftAction.addScancodeKeyControl(gf::Scancode::Left);
  leftAction.setContinuous();
  actions.addAction(leftAction);

  gf::Action rightAction("Right");
  rightAction.addScancodeKeyControl(gf::Scancode::D);
  rightAction.addScancodeKeyControl(gf::Scancode::Right);
  rightAction.setContinuous();
  actions.addAction(rightAction);

  gf::Action upAction("Up");
  upAction.addScancodeKeyControl(gf::Scancode::W);
  upAction.addScancodeKeyControl(gf::Scancode::Up);
  upAction.setContinuous();
  actions.addAction(upAction);

  gf::Action downAction("Down");
  downAction.addScancodeKeyControl(gf::Scancode::S);
  downAction.addScancodeKeyControl(gf::Scancode::Down);
  downAction.setContinuous();
  actions.addAction(downAction);

  // Models
  gf::ModelContainer models;

  no::EconomicModel gameModel;
  models.addModel(gameModel);

  // entities

  gf::EntityContainer mainEntities;

  no::WorldMap map;
  mainEntities.addEntity(map);

  no::Globe globe(gameModel);
  mainEntities.addEntity(globe);

  gf::EntityContainer hudEntities;
  // add entities to hudEntities

  no::BuildMenu buildMenu(gameModel);
  hudEntities.addEntity(buildMenu);

  no::InfoPanel infoPanel(gameModel);
  hudEntities.addEntity(infoPanel);

  // game loop

  renderer.clear(gf::Color::fromRgba32(0x19, 0x74, 0xD2));

  gf::Clock clock;

  while (window.isOpen()) {
    // 1. input

    gf::Event event;

    while (window.pollEvent(event)) {
      actions.processEvent(event);
      views.processEvent(event);
      adaptor.processEvent(event);
      infoPanel.processEvent(event);

      switch (event.type) {
        case gf::EventType::MouseMoved:
        {
          auto worldPosition = renderer.mapPixelToCoords(event.mouseCursor.coords, mainView);
          auto screenPosition = renderer.mapPixelToCoords(event.mouseCursor.coords, hudView);

          // Update postions for the model
          gameModel.worldPosition = worldPosition;
          gameModel.screenPosition = screenPosition;
          gameModel.fieldOfView = mainView.getBounds();
        }
          break;

        case gf::EventType::MouseButtonPressed:
        {
          auto screenPosition = renderer.mapPixelToCoords(event.mouseButton.coords, hudView);
          auto worldPosition = renderer.mapPixelToCoords(event.mouseButton.coords, mainView);

          // Update postions for the model
          gameModel.worldPosition = worldPosition;
          gameModel.screenPosition = screenPosition;
          gameModel.fieldOfView = mainView.getBounds();

          if (event.mouseButton.button == gf::MouseButton::Middle) {
            gf::Vector2f pos = worldPosition;
            std::cout << "{ " << pos.x << "f, " << pos.y << "f },\n";
          }

          // Trigger build menu
          buildMenu.pressed(event.mouseButton.button);
          break;
        }

        default:
          break;
      }
    }

    if (closeWindowAction.isActive()) {
      window.close();
    }

    if (fullscreenAction.isActive()) {
      window.toggleFullscreen();
    }

    if (rightAction.isActive()) {
      // do something
    } else if (leftAction.isActive()) {
      // do something
    } else if (upAction.isActive()) {
      // do something
    } else if (downAction.isActive()) {
      // do something
    } else {
      // do something
    }


    // 2. update

    gf::Time time = clock.restart();
    gameModel.update(time);
    mainEntities.update(time);
    hudEntities.update(time);


    // 3. draw

    renderer.clear();

    renderer.setView(mainView);
    mainEntities.render(renderer);

    renderer.setView(hudView);
    hudEntities.render(renderer);

    renderer.display();

    actions.reset();
  }

  return 0;
}
