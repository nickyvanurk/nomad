#include "PauseState.h"

#include "StateManager.h"
#include "GameState.h"
#include "MenuState.h"

PauseState::PauseState(StateManager& stateManager)
    :State(stateManager)
{
  _font.loadFromFile("Assets/Fonts/pixelmix.ttf");
  _title.setFont(_font);
  _instruction.setFont(_font);
  _title.setString("Paused");
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

PauseState::~PauseState()
{

}

void PauseState::pause()
{

}

void PauseState::resume()
{

}

void PauseState::processEvents(sf::Event& event)
{
  if (event.type == sf::Event::KeyPressed) {
    getStateManager().popState();
  }
}

void PauseState::update(sf::Time deltaTime)
{

}

void PauseState::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
  target.clear(sf::Color(217,91,67));
  target.draw(_title);
  target.draw(_instruction);
}
