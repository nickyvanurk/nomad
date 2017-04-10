#include "Creature.h"

#include <iostream>

Creature::Creature(std::string type, sf::Vector2u size, sf::Vector2u position,
                   sf::Color color)
    :Entity(type,size,position,color)
    ,_isMovingLeft(false)
    ,_isMovingRight(false)
    ,_velocity(0,0)
    ,_maxSpeed(size.x*15,size.y*60)
    ,_acceleration(_maxSpeed.x*2)
    ,_resistance(_maxSpeed.x*6)
    ,_gravity(size.x*(9.8*6))
{
}

void Creature::update(sf::Time deltaTime)
{
  float seconds = deltaTime.asSeconds();

  bool wasLeft  = _velocity.x < 0;
  bool wasRight = _velocity.x > 0;

  sf::Vector2f velocity = sf::Vector2f(0,_gravity);

  if (_isMovingLeft)
    velocity.x -= _acceleration;
  else if (wasLeft)
    velocity.x += _resistance;

  if (_isMovingRight)
    velocity.x += _acceleration;
  else if (wasRight)
    velocity.x -= _resistance;

  move(_velocity * seconds);

  _velocity.x = std::max(-_maxSpeed.x,std::min(_maxSpeed.x,_velocity.x+(velocity.x*seconds)));
  _velocity.y = std::max(-_maxSpeed.y,std::min(_maxSpeed.y,_velocity.y+(velocity.y*seconds)));

  // Prevent friction from making us jiggle side to side
  if ((wasLeft && (_velocity.x > 0)) || (wasRight && (_velocity.x < 0))) {
    _velocity.x = 0;
  }
}

sf::Vector2f Creature::getVelocity() const
{
  return _velocity;
}

void Creature::setVelocity(sf::Vector2f velocity)
{
  _velocity = velocity;
}

sf::Vector2f Creature::getMaxSpeed() const
{
  return _maxSpeed;
}

void Creature::setMaxSpeed(sf::Vector2f maxSpeed)
{
  _maxSpeed = maxSpeed;
}
