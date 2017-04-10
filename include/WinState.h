#ifndef WINSTATE_H
#define WINSTATE_H

#include "State.h"

#include <SFML/Audio.hpp>

class StateManager;
class WinState : public State {
public:
  WinState(StateManager& stateManager);
  ~WinState();

  void pause();
  void resume();

  void processEvents(sf::Event& event);
  void update(sf::Time deltaTime);
private:
  virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

  sf::SoundBuffer _winBuffer;
  sf::Sound _winSound;

  sf::Font _font;
  sf::Text _title;
  sf::Text _instruction;
};
#endif // WINSTATE_H

