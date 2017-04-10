#include "CreditState.h"

#include "StateManager.h"
#include "MenuState.h"

CreditState::CreditState(StateManager& stateManager)
    :State(stateManager)
{
  _font.loadFromFile("Assets/Fonts/pixelmix.ttf");
  _title.setFont(_font);
  _text.setFont(_font);

  _title.setString("Nomad");
  _text.setString("A game programmed in about two weeks to serve as a school project.\nProgrammed in C++ and SFML. Made by Nicky van Urk.\n\nMonday January 25th, 2016.");

  _title.setCharacterSize(24);
  _text.setCharacterSize(12);
  _title.setColor(sf::Color(236,208,120));
  _text.setColor(sf::Color(236,208,120));

  int windowWidth  = getStateManager().getWindow().getSize().x;
  int windowHeight = getStateManager().getWindow().getSize().y;

  int spacing = 20;

  _title.setPosition(windowWidth/2 - _title.getGlobalBounds().width/2,
      windowHeight/2 - _title.getGlobalBounds().height/2 - spacing);

  _text.setPosition(windowWidth/2 - _text.getGlobalBounds().width/2,
      windowHeight/2 - _title.getGlobalBounds().height/2 + spacing);
}

CreditState::~CreditState()
{

}

void CreditState::pause()
{

}

void CreditState::resume()
{

}

void CreditState::processEvents(sf::Event& event)
{
  if (event.type == sf::Event::KeyPressed) {
    getStateManager().popState();
  }
}

void CreditState::update(sf::Time deltaTime)
{

}

void CreditState::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
  target.clear(sf::Color(217,91,67));
  target.draw(_title);
  target.draw(_text);
}
