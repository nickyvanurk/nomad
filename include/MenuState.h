#ifndef MENUSTATE_H
#define MENUSTATE_H

#include "State.h"

class StateManager;
class MenuState : public State {
public:
  MenuState(StateManager& stateManager);
  ~MenuState();

  void pause();
  void resume();

  void processEvents(sf::Event& event);
  void update(sf::Time deltaTime);
private:
  virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

  sf::Font _font;
  sf::Text _title;
  sf::Text _play;
  sf::Text _credits;
  sf::Text _exit;

  int _activeBtn;

  sf::CircleShape _triangle;
};
#endif // MENUSTATE_H
