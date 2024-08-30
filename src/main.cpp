/*
    This project does not own any of the images or sounds used in it. All images
    and sounds were used for educational purposes as the project will not be
    distributed.
*/

#include <SDL.h>
#include <chrono>
#include <iostream>
#include <vector>

#include "Character.hpp"
#include "Enemy.hpp"
#include "GameWindow.hpp"
#include "LoseScreen.hpp"
#include "Map.hpp"
#include "Platform.hpp"
#include "Sprite.hpp"
#include "StartScreen.hpp"
#include "Text.hpp"

// Function to calculate the time between frames
float calculateDeltaTime(float &previousTick) {
  using namespace std::chrono;
  static auto startTime = high_resolution_clock::now();
  auto currentTime = high_resolution_clock::now();
  float currentTick =
      duration_cast<milliseconds>(currentTime - startTime).count();
  float deltaTime =
      (currentTick - previousTick) / 1000.0f; // Convert to seconds
  previousTick = currentTick;
  return deltaTime;
}

// Function to handle events
void handleEvents(GameWindow &game) {
  SDL_Event e;
  while (SDL_PollEvent(&e) != 0) {
    if (e.type == SDL_QUIT) {
      game.closeGameWindow();
    }
  }
}

int main(int argc, const char **argv) {
  GameWindow game("Dungeon Escape");
  Map map;
  map.init(game.getRenderer());

  float previousTick = 0.0f;
  float deltaTime = 0.0f;

  // Game loop
  while (game.isOpen()) {
    // Calculate time between frames
    deltaTime = calculateDeltaTime(previousTick);

    // Handle events
    handleEvents(game);

    // Show start screen if needed
    if (!map.shouldShowStartScreen(game.getRenderer(), deltaTime)) {
      // Load the map (only happens once due to checks within the method)
      map.load(game.getRenderer());
    }

    // Show the game map if not showing lose or win screen
    if (!map.shouldShowLoseScreen(game.getRenderer()) &&
        !map.shouldShowWinScreen(game.getRenderer())) {
      map.show(game.getRenderer(), deltaTime);
    }
  }

  return 0;
}
