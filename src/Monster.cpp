#include "Monster.h"

Monster::Monster(bool left, bool right, int maxDx, std::string type,
                 sf::Vector2u size, sf::Vector2u position, sf::Color color)
    :Creature(type,size,position,color)
{
  if (left) _isMovingLeft = true;
  else if (right) _isMovingRight = true;

  if (maxDx) {
    sf::Vector2f maxSpeed = getMaxSpeed();
    maxSpeed.x = size.x*maxDx;
    setMaxSpeed(maxSpeed);
  }
}

void Monster::update(sf::Time deltaTime)
{
  Creature::update(deltaTime);
}

bool Monster::isGoingLeft() const
{
  return _isMovingLeft ? true : false;
}

bool Monster::isGoingRight() const
{
  return _isMovingRight ? true : false;
}

void Monster::goLeft()
{
  if (_isMovingRight) _isMovingRight = false;
  if (!_isMovingLeft) _isMovingLeft  = true;
}

void Monster::goRight()
{
  if (_isMovingLeft)   _isMovingLeft  = false;
  if (!_isMovingRight) _isMovingRight = true;
}
