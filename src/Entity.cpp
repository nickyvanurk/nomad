#include "Entity.h"

Entity::Entity(std::string type, sf::Vector2u size, sf::Vector2u position,
               sf::Color color)
    :_rectangle(sf::Vector2f(size.x,size.y))
    ,_size(size)
    ,_position(position)
    ,_type(type)
{
  setPosition(sf::Vector2f(_position.x+size.x/2,_position.y+size.y/2));
  setOrigin(size.x/2,size.y/2);
  setColor(color);
}

sf::Vector2u Entity::getSize() const
{
  return _size;
}

std::string Entity::getType() const
{
  return _type;
}

void Entity::setColor(sf::Color color)
{
  _rectangle.setFillColor(color);
}

void Entity::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
  states.transform *= getTransform();
  target.draw(_rectangle,states);
}
