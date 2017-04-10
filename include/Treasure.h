#ifndef TREASURE_H
#define TREASURE_H

#include "Entity.h"

#include <SFML/Graphics.hpp>

class Treasure : public Entity {
public:
  Treasure(std::string type, sf::Vector2u size, sf::Vector2u position, sf::Color color);

  void update(sf::Time deltaTime);
private:
  sf::Color _color;
  sf::Color _maxColor;
  sf::Color _minColor;
  float _tweenPercentage;
  int _tweenSpeed;
  bool _switch;
};
#endif // TREASURE_H
