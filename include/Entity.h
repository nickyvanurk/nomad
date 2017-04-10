#ifndef ENTITY_H
#define ENTITY_H

#include <SFML/Graphics.hpp>

#include <string>
#include <iostream>

class Entity : public sf::Drawable, public sf::Transformable {
public:
  Entity(std::string type, sf::Vector2u size, sf::Vector2u position,
         sf::Color color);

  sf::Vector2u getSize() const;
  std::string getType() const;

  void setColor(sf::Color color);

  virtual void update(sf::Time deltaTime) = 0;
private:
  virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

  sf::RectangleShape _rectangle;

  std::string _type;
  sf::Vector2u _size;
  sf::Vector2u _position;
};
#endif // ENTITY_H
