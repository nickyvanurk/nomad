#include "Treasure.h"

#include <iostream>

Treasure::Treasure(std::string type, sf::Vector2u size, sf::Vector2u position, sf::Color color)
    :Entity(type,size,position,color)
    ,_color(color)
    ,_maxColor(_color)
    ,_minColor(_color)
    ,_tweenPercentage(30.f)
    ,_tweenSpeed(3)
    ,_switch(false)
{
  _minColor = sf::Color(_color.r/100*(100-_tweenPercentage),
                        _color.g/100*(100-_tweenPercentage),
                        _color.b/100*(100-_tweenPercentage));
}

void Treasure::update(sf::Time deltaTime)
{
  if (_color.r == _maxColor.r &&
      _color.g == _maxColor.g &&
      _color.b == _maxColor.b) {
    _switch = false;
  }

  if (_color.r <= _minColor.r &&
      _color.g <= _minColor.g &&
      _color.b <= _minColor.b) {
    _switch = true;
  }

  if (_switch) {
    if (_color.r != _maxColor.r)
      _color.r += _tweenSpeed;
    if (_color.g != _maxColor.g)
      _color.g += _tweenSpeed;
    if (_color.b != _maxColor.b)
      _color.b += _tweenSpeed;
  } else {
    if (_color.r != _minColor.r)
      _color.r -= _tweenSpeed;
    if (_color.g != _minColor.g)
      _color.g -= _tweenSpeed;
    if (_color.b != _minColor.b)
      _color.b -= _tweenSpeed;
  }



  setColor(_color);
}
