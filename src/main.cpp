#include "StateManager.h"
#include "IntroState.h"

int main()
{
  StateManager stateManager("Nomad");
  stateManager.pushState(new IntroState(stateManager));

  sf::Clock clock;
  sf::Time timeSinceLastUpdate = sf::Time::Zero;
  sf::Time timePerFrame = sf::seconds(1.f/60.f);

  while (stateManager.running()) {
    sf::Event event;
    stateManager.processEvents(event);

    timeSinceLastUpdate += clock.restart();
    while (timeSinceLastUpdate > timePerFrame) {
      timeSinceLastUpdate -= timePerFrame;
      stateManager.update(timePerFrame);
      stateManager.render();
    }
  }
}
