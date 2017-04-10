#ifndef PLAYER_H
#define PLAYER_H

#include "Creature.h"

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

class Player : public Creature {
public:
  Player(std::string type, sf::Vector2u size, sf::Vector2u position, sf::Color color);

  void processEvents(sf::Event& event);
  void update(sf::Time deltaTime);

  void setFalling(bool isFalling);

  void kill();

  float getImpulse() const;
  void releaseEvents();

  int getLives() const;
  void setLives(int lives);
private:
  sf::Vector2f _startPosition;

  bool _isJumping;
  bool _isGrounded;
  bool _isFalling;

  float _impulse;

  bool _releaseEvents;

  int _lives;

  sf::SoundBuffer _jumpBuffer;
  sf::SoundBuffer _deathBuffer;

  sf::Sound _jumpSound;
  sf::Sound _deathSound;
};
#endif // PLAYER_H

