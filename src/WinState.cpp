#include "WinState.h"

#include "StateManager.h"
#include "MenuState.h"

#include <iostream>

WinState::WinState(StateManager& stateManager)
    :State(stateManager)
{
  if (!_winBuffer.loadFromFile("Assets/Sounds/win.ogg"))\
    std::cout << "Failed to load: win.ogg" << std::endl;

  _winSound.setBuffer(_winBuffer);
  _winSound.play();

  _font.loadFromFile("Assets/Fonts/pixelmix.ttf");
  _title.setFont(_font);
  _instruction.setFont(_font);
  _title.setString("You Won!");
  _instruction.setString("Press any key to continue");
  _title.setCharacterSize(24);
  _instruction.setCharacterSize(12);
  _title.setColor(sf::Color(236,208,120));
  _instruction.setColor(sf::Color(236,208,120));

  int windowWidth  = getStateManager().getWindow().getSize().x;
  int windowHeight = getStateManager().getWindow().getSize().y;

  int spacing = 20;

  _title.setPosition(windowWidth/2 - _title.getGlobalBounds().width/2,
      windowHeight/2 - _title.getGlobalBounds().height/2 - spacing);

  _instruction.setPosition(windowWidth/2 - _instruction.getGlobalBounds().width/2,
      windowHeight/2 - _title.getGlobalBounds().height/2 + spacing);
}

WinState::~WinState()
{

}

void WinState::pause()
{

}

void WinState::resume()
{

}

void WinState::processEvents(sf::Event& event)
{
  if (event.type == sf::Event::KeyPressed)
    getStateManager().changeState(new MenuState(getStateManager()));
}

void WinState::update(sf::Time deltaTime)
{

}

void WinState::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
  target.clear(sf::Color(217,91,67));
  target.draw(_title);
  target.draw(_instruction);
}
