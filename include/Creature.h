#ifndef CREATURE_H
#define CREATURE_H

#include "Entity.h"

#include <SFML/Graphics.hpp>

class Creature : public Entity {
public:
  Creature(std::string type, sf::Vector2u size, sf::Vector2u position,
           sf::Color color);

  void update(sf::Time deltaTime);

  sf::Vector2f getVelocity() const;
  void setVelocity(sf::Vector2f velocity);

  sf::Vector2f getMaxSpeed() const;
  void setMaxSpeed(sf::Vector2f maxSpeed);
protected:
  bool _isMovingLeft;
  bool _isMovingRight;

  sf::Vector2f _velocity;
private:
  sf::Vector2f _maxSpeed;

  float _acceleration;
  float _resistance;
  float _gravity;
};
#endif // CREATURE_H
