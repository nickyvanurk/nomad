#include "TileMap.h"

#include <SFML/Graphics/Color.hpp>

void TileMap::load(const sf::Color* colors, sf::Vector2u tileSize,
                   std::vector<int>& tiles, unsigned int width, unsigned int height)
{
  // resize the vertex array to fit the level size
  _vertices.setPrimitiveType(sf::Quads);
  _vertices.resize(width * height * 4);

  // populate the vertex array, with one quad per tile
  for (unsigned int i = 0; i < width; ++i) {
    for (unsigned int j = 0; j < height; ++j) {
      // get the current tile number
      int tileNumber = tiles[i + j * width];

      // Skip the tile number: 0
      if (!tileNumber)
        continue;

      // get a pointer to the current tile's quad
      sf::Vertex* quad = &_vertices[(i + j * width) * 4];

      quad[0].position = sf::Vector2f(i * tileSize.x, j * tileSize.y);
      quad[1].position = sf::Vector2f((i + 1) * tileSize.x, j * tileSize.y);
      quad[2].position = sf::Vector2f((i + 1) * tileSize.x, (j + 1) * tileSize.y);
      quad[3].position = sf::Vector2f(i * tileSize.x, (j + 1) * tileSize.y);

      quad[0].color = colors[tileNumber];
      quad[1].color = colors[tileNumber];
      quad[2].color = colors[tileNumber];
      quad[3].color = colors[tileNumber];
    }
  }
}

void TileMap::clear()
{
  _vertices.clear();
}

void TileMap::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
  states.transform *= getTransform();
  target.draw(_vertices,states);
}
