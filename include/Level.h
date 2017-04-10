#ifndef LEVEL_H
#define LEVEL_H

#include <string>
#include <vector>
#include <memory>

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "TileMap.h"
#include "Player.h"
#include "Treasure.h"
#include "Monster.h"

class Level : public sf::Drawable {
public:
  Level();
  ~Level();

  void update(sf::Time deltaTime);

  bool finished();
  bool nextLevel();

  Player* getPlayer() const;

  bool isRestart() const;
  void setRestart(bool restart);
private:
  std::string getCurrentLevel(std::string filePath) const;
  bool loadFromFile(std::string filePath);

  void clear();
  void saveProgress();
  void restart();

  virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

  sf::Vector2u _levelSize;
  sf::Vector2u _tileSize;
  std::vector<int> _tiles;

  TileMap _tileMap;

  sf::Color _colors[8]; // Determine the colors of the tiles and objects

  Player* _pPlayer;
  std::vector<Treasure*> _treasures;
  std::vector<Monster*> _monsters;

  unsigned int _currentLevel;

  int _monstersScore;
  int _treasuresScore;

  int _maxMonsterScore;
  int _maxTreasureScore;

  std::vector<sf::RectangleShape> _mScore;
  std::vector<sf::RectangleShape> _tScore;
  std::vector<sf::RectangleShape> _playerLives;

  sf::SoundBuffer _jumpBuffer;
  sf::SoundBuffer _monsterBuffer;
  sf::SoundBuffer _treasureBuffer;

  sf::Sound _monsterSound;
  sf::Sound _treasureSound;

  bool _restart;
};
#endif // LEVEL_H
