#include "Level.h"

#include <sstream> // int to string
#include <fstream> // load file from hard drive
#include <cstdlib> // atoi: string to int
#include <iostream>

#include "pugixml.hpp"

#include "Player.h"
#include "Monster.h"
#include "Treasure.h"

Level::Level()
    :_levelSize(0,0)
    ,_tileSize(0,0)
    ,_colors{sf::Color(0,0,0),      sf::Color(236,208,120),
             sf::Color(217,91,67),  sf::Color(192,41,66),
             sf::Color(84,36,55),   sf::Color(51,51,51),
             sf::Color(83,119,122), sf::Color(255,238,0)}
    ,_pPlayer(nullptr)
    ,_monstersScore(0)
    ,_treasuresScore(0)
    ,_restart(false)
{
  // Load the XML level data
  std::string currentLevel = getCurrentLevel("Assets/Levels/current_level.txt");
  _currentLevel = std::atoi(currentLevel.c_str());
  loadFromFile("Assets/Levels/level"+currentLevel+".tmx");

  _tileMap.load(_colors,_tileSize,_tiles,_levelSize.x,_levelSize.y);

  _maxMonsterScore  = _monsters.size();
  _maxTreasureScore = _treasures.size();

  for (int i=0; i<_pPlayer->getLives(); ++i) {
    sf::RectangleShape life;
    life.setSize(sf::Vector2f(6,6));
    life.setFillColor(sf::Color::Red);
    life.setPosition(16+(8*(i+1)), 24);
    _playerLives.push_back(life);
  }

  if (_monsterBuffer.loadFromFile("Assets/Sounds/monster.wav"))
    _monsterSound.setBuffer(_monsterBuffer);

  if (_treasureBuffer.loadFromFile("Assets/Sounds/treasure.wav"))
    _treasureSound.setBuffer(_treasureBuffer);

  _monsterSound.setVolume(50);
  _treasureSound.setVolume(70);
}

Level::~Level()
{
  clear();
  std::cout << "Level cleared" << std::endl;
}

void Level::clear()
{
  _levelSize = _tileSize = sf::Vector2u(0,0);

  delete _pPlayer;
  _pPlayer = nullptr;

  for (auto* monster : _monsters)
    delete monster;
  _monsters.clear();

  for (auto* treasure : _treasures)
    delete treasure;
  _treasures.clear();

  _tiles.clear();
  _tileMap.clear();

  _monstersScore = _treasuresScore = 0;

  _mScore.clear();
  _tScore.clear();
  _playerLives.clear();
}

std::string Level::getCurrentLevel(std::string filePath) const
{
  std::ifstream file(filePath);
  std::stringstream data;

  data << file.rdbuf();

  return data.str();
}

bool Level::loadFromFile(std::string filePath)
{
  pugi::xml_document doc;

  if (!doc.load_file((filePath).c_str()))
    return false;

  // Map data
  pugi::xml_node mapNode = doc.child("map");

  _levelSize = sf::Vector2u(mapNode.attribute("width").as_int(),
                            mapNode.attribute("height").as_int());

  _tileSize = sf::Vector2u(mapNode.attribute("tilewidth").as_int(),
                           mapNode.attribute("tileheight").as_int());

  // Loop through each layer element
  for (pugi::xml_node layer : mapNode.children("layer")) {
    // Loop through all the data tiles
    pugi::xml_node data = layer.child("data");
    for (pugi::xml_node tile : data) {
      // Store the tile number for later use
      _tiles.push_back(tile.attribute("gid").as_int());
    }
  }

  // Loop through each object group
  for (pugi::xml_node group : mapNode.children("objectgroup")) {
    for (pugi::xml_node object : group) {
      std::string objectType = object.attribute("type").value();

      sf::Vector2u objectSize = sf::Vector2u(object.attribute("width").as_int(),
                                             object.attribute("height").as_int());

      sf::Vector2u objectPosition = sf::Vector2u(object.attribute("x").as_int(),
                                                 object.attribute("y").as_int());

      bool left  = false;
      bool right = false;
      int  maxdx = 0; // The maximal horizontal speed

      // Loop  through the object properties
      for (pugi::xml_node property : object.child("properties")) {
        std::string propertyName = property.attribute("name").value();

        if (propertyName == "left")
          left = property.attribute("value").as_bool();
        else if (propertyName == "right")
          right = property.attribute("value").as_bool();
        else if (propertyName == "maxdx")
          maxdx = property.attribute("value").as_int();
      }

      // Create and story object
      if (objectType == "player")
        _pPlayer = new Player(objectType,objectSize,objectPosition,_colors[1]);
      else if (objectType == "treasure")
        _treasures.push_back(new Treasure(objectType,objectSize,objectPosition,_colors[7]));
      else // Treasure
        _monsters.push_back(new Monster(left,right,maxdx,objectType,objectSize,objectPosition,_colors[6]));
    }
  }

  return true;
}

void Level::restart()
{
  clear();

  // Load the XML level data
  std::string currentLevel = getCurrentLevel("Assets/Levels/current_level.txt");
  _currentLevel = std::atoi(currentLevel.c_str());
  loadFromFile("Assets/Levels/level"+currentLevel+".tmx");

  _tileMap.load(_colors,_tileSize,_tiles,_levelSize.x,_levelSize.y);

  _maxMonsterScore  = _monsters.size();
  _maxTreasureScore = _treasures.size();

  for (int i=0; i<_pPlayer->getLives(); ++i) {
    sf::RectangleShape life;
    life.setSize(sf::Vector2f(6,6));
    life.setFillColor(sf::Color::Red);
    life.setPosition(16+(8*(i+1)), 24);
    _playerLives.push_back(life);
  }

  _restart = true;
}

bool Level::isRestart() const
{
  return _restart;
}

void Level::setRestart(bool restart)
{
  _restart = restart;
}

void Level::update(sf::Time deltaTime)
{
  _pPlayer->update(deltaTime);

  // Collision detection: Player - Tiles
  Player& player = *_pPlayer;

  sf::Vector2f position = player.getPosition();
  sf::Vector2u size     = player.getSize();
  sf::Vector2f velocity = player.getVelocity();

  // Player tile position
  int tx = (position.x-size.x/2)/_tileSize.x;
  int ty = (position.y-size.y/2)/_tileSize.y;

  // True of player overlaps right or below
  int nx = static_cast<int>(position.x-size.x/2)%_tileSize.x;
  int ny = static_cast<int>(position.y-size.y/2)%_tileSize.y;

  // Number of current tile position in level data vector
  int cell = _tiles[tx + ty * _levelSize.x];

  int cellRight = _tiles[(tx+1)+ ty   *_levelSize.x];
  int cellDown  = _tiles[ tx   +(ty+1)*_levelSize.x];
  int cellDiag  = _tiles[(tx+1)+(ty+1)*_levelSize.x];

  // Check for collision on the y axis
  if (velocity.y > 0) {
    if ((cellDown && !cell) || (cellDiag && !cellRight && nx)) {
      position.y = ty*_tileSize.y+size.y/2;
      velocity.y = 0;
      ny = 0;

      player.setFalling(false);
    }
  } else if (velocity.y < 0) {
    if ((cell && !cellDown) || (cellRight && !cellDiag && nx)) {
      position.y = (ty+1)*_tileSize.y+size.y/2;
      velocity.y = 0;
      cell = cellDown;
      cellRight = cellDiag;
      ny = 0;
    }
  }

  // Check for collision on the x axis
  if (velocity.x > 0) {
    if ((cellRight && !cell) || (cellDiag && !cellDown && ny)) {
      position.x = tx*_tileSize.x+size.x/2;
      velocity.x = 0;
    }
  } else if (velocity.x < 0) {
    if ((cell && !cellRight) || (cellDown && !cellDiag && ny)) {
      position.x = (tx+1)*_tileSize.x+size.x/2;
      velocity.x = 0;
    }
  }

  player.setPosition(position);
  player.setVelocity(velocity);
  player.setFalling(!(cellDown || (nx && cellDiag)));

  for (auto* monsterPtr : _monsters) {
    Monster& monster = *monsterPtr;
    monster.update(deltaTime);

    sf::Vector2f position = monster.getPosition();
    sf::Vector2u size     = monster.getSize();
    sf::Vector2f velocity = monster.getVelocity();

    // Player tile position
    int tx = (position.x-size.x/2)/_tileSize.x;
    int ty = (position.y-size.y/2)/_tileSize.y;

    // True of player overlaps right or below
    int nx = static_cast<int>(position.x-size.x/2)%_tileSize.x;
    int ny = static_cast<int>(position.y-size.y/2)%_tileSize.y;

    // Number of current tile position in level data vector
    int cell = _tiles[tx + ty * _levelSize.x];

    int cellRight = _tiles[(tx+1)+ ty   *_levelSize.x];
    int cellDown  = _tiles[ tx   +(ty+1)*_levelSize.x];
    int cellDiag  = _tiles[(tx+1)+(ty+1)*_levelSize.x];

    // Check for collision on the y axis
    if (velocity.y > 0) {
      if ((cellDown && !cell) || (cellDiag && !cellRight && nx)) {
        position.y = ty*_tileSize.y+size.y/2;
        velocity.y = 0;
        ny = 0;
      }
    } else if (velocity.y < 0) {
      if ((cell && !cellDown) || (cellRight && !cellDiag && nx)) {
        position.y = (ty+1)*_tileSize.y+size.y/2;
        velocity.y = 0;
        cell = cellDown;
        cellRight = cellDiag;
        ny = 0;
      }
    }

    // Check for collision on the x axis
    if (velocity.x > 0) {
      if ((cellRight && !cell) || (cellDiag && !cellDown && ny)) {
        position.x = tx*_tileSize.x+size.x/2;
        velocity.x = 0;
      }
    } else if (velocity.x < 0) {
      if ((cell && !cellRight) || (cellDown && !cellDiag && ny)) {
        position.x = (tx+1)*_tileSize.x+size.x/2;
        velocity.x = 0;
      }
    }

    monster.setPosition(position);
    monster.setVelocity(velocity);

    if (monster.isGoingLeft() && (cell || !cellDown)) {
      monster.goRight();
    } else if (monster.isGoingRight() && (cellRight || !cellDiag)) {
      monster.goLeft();
    }
  }

  // Player treasure collision
  for (auto e = _treasures.begin(); e != _treasures.end();) {
    Treasure& treasure = **e;
    treasure.update(deltaTime);

    sf::Vector2f tPos  = treasure.getPosition();
    sf::Vector2u tSize = treasure.getSize();

    sf::Vector2f playerPos  = player.getPosition();
    sf::Vector2u playerSize = player.getSize();

    if ((std::abs(playerPos.x - tPos.x) < (playerSize.x/2 + tSize.x/2)) &&
        (std::abs(playerPos.y - tPos.y) < (playerSize.y/2 + tSize.y/2))) {
      // Colliding with a treasure...
      e = _treasures.erase(e);
      ++_treasuresScore;
      _treasureSound.play();
    } else {
      ++e;
    }
  }

  // Player monster collision
  for (auto e = _monsters.begin(); e != _monsters.end();) {
    Monster& monster = **e;

    sf::Vector2f mPos  = monster.getPosition();
    sf::Vector2u mSize = monster.getSize();

    sf::Vector2f playerPos  = player.getPosition();
    sf::Vector2u playerSize = player.getSize();

    if ((std::abs(playerPos.x - mPos.x) < (playerSize.x/2 + mSize.x/2)) &&
        (std::abs(playerPos.y - mPos.y) < (playerSize.y/2 + mSize.y/2))) {
      // Colliding with a monster...
      sf::Vector2f playerVel = player.getVelocity();
      // Maybe come back here to refine monster collision
      if ((playerVel.y > 0) && (mPos.y - playerPos.y > 0)) {
        // Kill monster
        e = _monsters.erase(e);
        ++_monstersScore;
        _monsterSound.play();
        sf::Vector2f vel = player.getVelocity();
        player.setVelocity(sf::Vector2f(vel.x,-(player.getImpulse()/4*3)));
      } else {
        if (_playerLives.size() > 1) {
          _playerLives.pop_back();
          player.kill();
        } else
          restart();

        ++e;
      }
    } else {
      ++e;
    }
  }

  for (int i=_tScore.size(); i<_treasuresScore; ++i) {
    sf::RectangleShape treasure;
    treasure.setSize(sf::Vector2f(6,6));
    treasure.setFillColor(_colors[7]);
    treasure.setPosition(16+(8*(i+1)), 32);
    _tScore.push_back(treasure);
  }

  for (int i=_mScore.size(); i<_monstersScore; ++i) {
    sf::RectangleShape monster;
    monster.setSize(sf::Vector2f(6,6));
    monster.setFillColor(_colors[6]);
    monster.setPosition(16+(8*(i+1)), 40);
    _mScore.push_back(monster);
  }
}

bool Level::finished()
{
  if ((_monstersScore == _maxMonsterScore) &&
      (_treasuresScore == _maxTreasureScore)) {
    ++_currentLevel;
    return true;
  }

  return false;
}

void Level::saveProgress()
{
  std::ofstream file;
  file.open ("Assets/Levels/current_level.txt");
  file << _currentLevel;
  file.close();
}

bool Level::nextLevel()
{
  clear();

  std::ostringstream os;
  os << _currentLevel;
  if (!loadFromFile("Assets/Levels/level"+os.str()+".tmx")) {
    // Unable to load the next level in other words, you finished the game
    _currentLevel = 1;
    saveProgress();

    return false;
  }

  _tileMap.load(_colors,_tileSize,_tiles,_levelSize.x,_levelSize.y);

  saveProgress();

  for (int i=0; i<_pPlayer->getLives(); ++i) {
    sf::RectangleShape life;
    life.setSize(sf::Vector2f(6,6));
    life.setFillColor(sf::Color::Red);
    life.setPosition(16+(8*(i+1)), 24);
    _playerLives.push_back(life);
  }

  return true;
}

Player* Level::getPlayer() const
{
  return &(*_pPlayer);
}

void Level::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
  target.draw(_tileMap);

  for (auto* treasure : _treasures)
    target.draw(*treasure);

  for (auto* monster : _monsters)
    target.draw(*monster);

  target.draw(*_pPlayer);

  for (int i=0; i<_playerLives.size(); ++i)
    target.draw(_playerLives[i]);

  for (int i=0; i<_monstersScore; ++i)
    target.draw(_mScore[i]);

  for (int i=0; i<_treasuresScore; ++i)
    target.draw(_tScore[i]);
}
