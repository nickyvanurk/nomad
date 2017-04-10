#ifndef PAUSESTATE_H
#define PAUSESTATE_H

#include "State.h"

class StateManager;
class PauseState : public State {
public:
  PauseState(StateManager& stateManager);
  ~PauseState();

  void pause();
  void resume();

  void processEvents(sf::Event& event);
  void update(sf::Time deltaTime);
private:
  virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

  sf::Font _font;
  sf::Text _title;
  sf::Text _instruction;
};
#endif // PAUSESTATE_H
