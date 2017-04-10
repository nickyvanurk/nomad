#include "StateManager.h"
#include "State.h"

#include <iostream>

StateManager::StateManager(const char* title, int width, int height, int bpp, bool fullscreen)
    :_running(true)
    ,_fullscreen(fullscreen)
    ,_window(nullptr)
{
  int style = sf::Style::Default;

  if (_fullscreen)
    style = sf::Style::Fullscreen;

  _window = new sf::RenderWindow(sf::VideoMode(width,height,bpp),title,style);

  getWindow().setKeyRepeatEnabled(false);

  std::cout << "StateManager initialized" << std::endl;
}

StateManager::~StateManager()
{
  while (!_states.empty())
    _states.pop_back();

  getWindow().close();

  std::cout << "StateManager destructed" << std::endl;
}

void StateManager::changeState(State* pState)
{
  if (!_states.empty())
    _states.pop_back();

  if (pState != nullptr)
    _states.push_back(std::move(std::unique_ptr<State>(pState)));
}

void StateManager::pushState(State* pState)
{
  if (!_states.empty())
    _states.back()->pause();

  if (pState != nullptr)
    _states.push_back(std::move(std::unique_ptr<State>(pState)));
}

void StateManager::popState()
{
  if (!_states.empty())
    _states.pop_back();

  if (!_states.empty())
    _states.back()->resume();
}

void StateManager::processEvents(sf::Event& event)
{
  while (getWindow().pollEvent(event)) {
    if (event.type == sf::Event::Closed)
      _running = false;

    _states.back()->processEvents(event);
  }
}

void StateManager::update(sf::Time deltaTime)
{
  _states.back()->update(deltaTime);
}

void StateManager::render()
{
  sf::RenderWindow& window = getWindow();

  window.clear();
  window.draw(*_states.back());
  window.display();
}

bool StateManager::running()
{
  return _running;
}

void StateManager::quit()
{
  _running = false;
}

int StateManager::getSize() const
{
  return _states.size();
}

sf::RenderWindow& StateManager::getWindow() const
{
  if (_window != nullptr)
    return *_window;
}
