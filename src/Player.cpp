#include "Player.h"

#include <iostream>

// Remember: Speed scales with size and not tile size, maybe change it later.

Player::Player(std::string type, sf::Vector2u size, sf::Vector2u position, sf::Color color)
    :Creature(type,size,position,color)
    ,_startPosition(position)
    ,_isJumping(false)
    ,_isGrounded(true)
    ,_isFalling(false)
    ,_impulse(400)
    ,_releaseEvents(false)
    ,_lives(3)
{
  if (_jumpBuffer.loadFromFile("Assets/Sounds/jump.wav"))
    _jumpSound.setBuffer(_jumpBuffer);

  if (_deathBuffer.loadFromFile("Assets/Sounds/death.wav"))
    _deathSound.setBuffer(_deathBuffer);

  _jumpSound.setVolume(90);
  _deathSound.setVolume(80);
}

void Player::processEvents(sf::Event& event)
{
  if (event.type == sf::Event::KeyPressed) {
    if (event.key.code == sf::Keyboard::A || event.key.code == sf::Keyboard::Left)
      _isMovingLeft = true;
    else if (event.key.code == sf::Keyboard::D || event.key.code == sf::Keyboard::Right)
      _isMovingRight = true;
    else if (event.key.code == sf::Keyboard::Space && !_isJumping && _isGrounded)
      _isJumping = true;
  }

  if (event.type == sf::Event::KeyReleased) {
    if (event.key.code == sf::Keyboard::A || event.key.code == sf::Keyboard::Left)
      _isMovingLeft = false;
    else if (event.key.code == sf::Keyboard::D || event.key.code == sf::Keyboard::Right)
      _isMovingRight = false;
  }
}

void Player::update(sf::Time deltaTime)
{
  if (_isJumping && _isGrounded && !_isFalling) {
    if (_velocity.y >= 0) {
      _velocity.y -= _impulse;
      _isGrounded = false;
      _isJumping = false;
      _jumpSound.play();
    }
  }

  Creature::update(deltaTime);
}

void Player::setFalling(bool isFalling)
{
  _isFalling = isFalling;

  if (!_isFalling)
    _isGrounded = true;
}

void Player::kill()
{
  int x = _startPosition.x+getSize().x/2;
  int y = _startPosition.y+getSize().y/2;
  setPosition(x,y);
  setVelocity(sf::Vector2f(0,0));
  --_lives;
  _deathSound.play();
}

float Player::getImpulse() const
{
  return _impulse;
}

void Player::releaseEvents()
{
  _isMovingLeft = false;
  _isMovingRight = false;
  _isJumping = false;
}

int Player::getLives() const
{
  return _lives;
}

void Player::setLives(int lives)
{
  _lives = lives;
}
