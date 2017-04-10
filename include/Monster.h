#ifndef MONSTER_H
#define MONSTER_H

#include "Creature.h"

#include <SFML/Graphics.hpp>

class Monster : public Creature {
public:
  Monster(bool left, bool right, int maxDx,std::string type, sf::Vector2u size,
          sf::Vector2u position, sf::Color color);

  void update(sf::Time deltaTime);

  bool isGoingLeft() const;
  bool isGoingRight() const;

  void goLeft();
  void goRight();
};
#endif // MONSTER_H

