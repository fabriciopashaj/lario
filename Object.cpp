#include "./Object.hpp"

void Object::draw(sf::RenderWindow &win)
{
  win.draw(sprite);
}

sf::FloatRect Object::boundingBox(void)
{
  return sprite.getGlobalBounds();
}

void Object::setPosition(sf::Vector2f pos)
{
  sprite.setPosition(pos);
}

sf::Vector2f Object::getPosition()
{
  return sprite.getPosition();
}

void Object::move(sf::Vector2f offset)
{
  sprite.move(offset);
}
