#pragma once
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

class Object {
protected:
  sf::Sprite sprite;
public:
  void draw(sf::RenderWindow &win);
  sf::FloatRect boundingBox(void);
  void setPosition(sf::Vector2f pos);
  sf::Vector2f getPosition();
  void move(sf::Vector2f offset);
};
