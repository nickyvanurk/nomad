#ifndef TILEMAP_H
#define TILEMAP_H

#include <SFML/Graphics.hpp>

class TileMap : public sf::Drawable, public sf::Transformable {
public:
  void load(const sf::Color* colors, sf::Vector2u tileSize,
            std::vector<int>& tiles, unsigned int width, unsigned int height);

  void clear();
private:
  virtual void draw(sf::RenderTarget& target,sf::RenderStates states) const;

  sf::VertexArray _vertices;
};
#endif // TILEMAP_H
