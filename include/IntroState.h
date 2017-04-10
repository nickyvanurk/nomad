#ifndef INTROSTATE_H
#define INTROSTATE_H

#include "State.h"

class StateManager;
class IntroState : public State {
public:
  IntroState(StateManager& stateManager);
  ~IntroState();

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
#endif // INTROSTATE_H
