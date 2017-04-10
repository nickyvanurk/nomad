#ifndef CREDITSTATE_H
#define CREDITSTATE_H

#include "State.h"

class StateManager;
class CreditState : public State {
public:
  CreditState(StateManager& stateManager);
  ~CreditState();

  void pause();
  void resume();

  void processEvents(sf::Event& event);
  void update(sf::Time deltaTime);
private:
  virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

  sf::Font _font;
  sf::Text _title;
  sf::Text _text;
};
#endif // CREDITSTATE_H

