#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "State.h"

#include "Level.h"
#include "Player.h"

#include <SFML/Audio.hpp>

class StateManager;
class GameState : public State {
public:
  GameState(StateManager& stateManager);
  ~GameState();

  void pause();
  void resume();

  void processEvents(sf::Event& event);
  void update(sf::Time deltaTime);

  bool isPaused() const;
private:
  virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

  Level _level;
  Player* _player;

  bool _paused;

  sf::SoundBuffer _winBuffer;
  sf::SoundBuffer _loseBuffer;

  sf::Sound _winSound;
  sf::Sound _loseSound;
};
#endif // GAMESTATE_H
