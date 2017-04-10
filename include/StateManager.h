#ifndef STATEMANAGER_H
#define STATEMANAGER_H

#include <vector>
#include <memory>

#include <SFML/Graphics.hpp>

class State;
class StateManager {
public:
  StateManager(const char* title, int width=1024, int height=768, int bpp=32, bool fullscreen=false);
  ~StateManager();

  void changeState(State* pState);
  void pushState(State* pState);
  void popState();

  void processEvents(sf::Event& event);
  void update(sf::Time deltaTime);
  void render();

  bool running();
  void quit();

  int getSize() const;

  sf::RenderWindow& getWindow() const;
private:
  std::vector<std::unique_ptr<State>> _states;

  bool _running;
  bool _fullscreen;
  sf::RenderWindow* _window;
};
#endif // STATEMANAGER_H
