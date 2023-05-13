#pragma once
#include "./Object.hpp"

class Floor : public Object {
public:
  Floor(sf::Vector2u winSize);
  void determinePosition(sf::Vector2u winSize);
};
