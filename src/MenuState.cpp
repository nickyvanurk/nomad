#include "MenuState.h"

#include "StateManager.h"
#include "GameState.h"
#include "CreditState.h"

MenuState::MenuState(StateManager& stateManager)
    :State(stateManager)
    ,_triangle(5,3)
    ,_activeBtn(1)
{
  _font.loadFromFile("Assets/Fonts/pixelmix.ttf");

  int windowWidth  = getStateManager().getWindow().getSize().x;
  int windowHeight = getStateManager().getWindow().getSize().y;

  int spacing = 20;

  _title.setFont(_font);
  _title.setString("Nomad");
  _title.setCharacterSize(24);
  _title.setColor(sf::Color(236,208,120));
  _title.setPosition(windowWidth/2 - _title.getGlobalBounds().width/2,
      windowHeight/2 - _title.getGlobalBounds().height/2 - spacing);

  _play.setFont(_font);
  _play.setString("Play");
  _play.setCharacterSize(12);
  _play.setColor(sf::Color(236,208,120));
  _play.setPosition(windowWidth/2 - _play.getGlobalBounds().width/2,
      windowHeight/2 - _play.getGlobalBounds().height/2 + spacing);

  _credits.setFont(_font);
  _credits.setString("Credits");
  _credits.setCharacterSize(12);
  _credits.setColor(sf::Color(236,208,120));
  _credits.setPosition(windowWidth/2 - _credits.getGlobalBounds().width/2,
      windowHeight/2 - _credits.getGlobalBounds().height/2 + spacing*2);

  _exit.setFont(_font);
  _exit.setString("Exit");
  _exit.setCharacterSize(12);
  _exit.setColor(sf::Color(236,208,120));
  _exit.setPosition(windowWidth/2 - _exit.getGlobalBounds().width/2,
      windowHeight/2 - _exit.getGlobalBounds().height/2 + spacing*3);

  _triangle.setRotation(90);
  _triangle.setPosition(windowWidth/2 - _exit.getGlobalBounds().width/2 - 30,
      windowHeight/2 - _exit.getGlobalBounds().height/2 + spacing*_activeBtn);
}

MenuState::~MenuState()
{

}

void MenuState::pause()
{

}

void MenuState::resume()
{

}

void MenuState::processEvents(sf::Event& event)
{
  if (event.type == sf::Event::KeyPressed) {
    if (event.key.code == sf::Keyboard::Escape)
      getStateManager().quit();
    else if (event.key.code == sf::Keyboard::Return ||
             event.key.code == sf::Keyboard::Space) {
      if (_activeBtn == 1) {
        if (getStateManager().getSize() <= 1)
          getStateManager().changeState(new GameState(getStateManager()));
        else
          getStateManager().popState();
      } if (_activeBtn == 2)
        getStateManager().pushState(new CreditState(getStateManager()));
      if (_activeBtn == 3)
        getStateManager().quit();
    } else if ((event.key.code == sf::Keyboard::S ||
              event.key.code == sf::Keyboard::Down) && (_activeBtn >= 1 && _activeBtn < 3)) {
      ++_activeBtn;
      _triangle.setPosition(_triangle.getPosition().x,
        _triangle.getPosition().y + 20);
    } else if ((event.key.code == sf::Keyboard::W ||
             event.key.code == sf::Keyboard::Up) && (_activeBtn > 1 && _activeBtn <= 3)) {
      --_activeBtn;
      _triangle.setPosition(_triangle.getPosition().x,
        _triangle.getPosition().y - 20);
    }
  }
}

void MenuState::update(sf::Time deltaTime)
{
  if (getStateManager().getSize() > 1) {
    _play.setString("Resume");
    int windowWidth  = getStateManager().getWindow().getSize().x;
    _play.setPosition(windowWidth/2 - _play.getGlobalBounds().width/2,
                      _play.getPosition().y);
  }
}

void MenuState::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
  target.clear(sf::Color(217,91,67));
  target.draw(_title);
  target.draw(_play);
  target.draw(_credits);
  target.draw(_exit);

  target.draw(_triangle);
}
