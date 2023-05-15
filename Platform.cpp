#include "./Platform.hpp"

static sf::Texture brick;
static bool initialised = false;

Platform::Platform(int width)
{
  if (!initialised)
  {
    if (!brick.loadFromFile(".\\assets\\brick.png"))
    {
      // TODO: Do some throwing or idk
    }
  } else
  {
    initialised = true;
  }
  brick.setRepeated(true);
  sf::Vector2u brickSize = brick.getSize();
  sf::IntRect rect(0, 0, brickSize.x * width, brickSize.y);
  sprite.setTextureRect(rect);
  sprite.setTexture(brick);
  sprite.setScale(7.25f / 10.f, 7.25f / 10.f);
}
