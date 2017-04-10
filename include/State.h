#ifndef STATE_H
#define STATE_H

#include <SFML/Graphics.hpp>

class StateManager;
class State : public sf::Drawable {
public:
  State(StateManager& stateManager);
  ~State() = default;

  virtual void pause() = 0;
  virtual void resume() = 0;

  virtual void processEvents(sf::Event& event) = 0;
  virtual void update(sf::Time deltaTime) = 0;

protected:
  StateManager& getStateManager() const;
private:
  virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const = 0;

  StateManager& _stateManager;
};
#endif // STATE_H
