#include "GameState.h"

#include "StateManager.h"
#include "MenuState.h"
#include "PauseState.h"
#include "WinState.h"

#include <iostream>

GameState::GameState(StateManager& stateManager)
    :State(stateManager)
    ,_player(_level.getPlayer())
    ,_paused(false)
{
  if (!_winBuffer.loadFromFile("Assets/Sounds/win.ogg"))
    std::cout << "Failed to load: win.ogg" << std::endl;

  if (!_loseBuffer.loadFromFile("Assets/Sounds/lose.ogg"))
    std::cout << "Failed to load: lose.ogg" << std::endl;

  _winSound.setBuffer(_winBuffer);
  _loseSound.setBuffer(_loseBuffer);

  std::cout << "GameState initialized" << std::endl;
}

GameState::~GameState()
{
  std::cout << "GameState destructed" << std::endl;
}

void GameState::pause()
{
  _paused = true;

  std::cout << "GameState paused" << std::endl;
}

void GameState::resume()
{
  _paused = false;
  _player->releaseEvents();
  std::cout << "GameState resumed" << std::endl;
}

void GameState::processEvents(sf::Event& event)
{
  if (event.type == sf::Event::KeyPressed) {
    if (event.key.code == sf::Keyboard::Escape)
      getStateManager().pushState(new MenuState(getStateManager()));
    else if (event.key.code == sf::Keyboard::P)
      getStateManager().pushState(new PauseState(getStateManager()));
  }

  _player->processEvents(event);
}

void GameState::update(sf::Time deltaTime)
{
  _level.update(deltaTime);

  if (_level.finished()) {
    if (!_level.nextLevel())
      getStateManager().changeState(new WinState(getStateManager()));

    _player = _level.getPlayer();
    _winSound.play();
  }

  if (_level.isRestart()) {
    _player = _level.getPlayer();
    _level.setRestart(false);
    _loseSound.play();
  }
}

void GameState::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
  target.draw(_level,states);
}

bool GameState::isPaused() const
{
  return _paused;
}

