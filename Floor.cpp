#include "./Floor.hpp"

static sf::Texture texture;
static bool initialised = false;

Floor::Floor(sf::Vector2u winSize)
{
  if (!initialised)
  {
    if (!texture.loadFromFile(".\\assets\\floor.png"))
    {
      // TODO: Throw exception
    }
    texture.setRepeated(true);
    initialised = true;
  }
  sf::IntRect rect(0, 0, winSize.x, winSize.y);
  sprite.setTextureRect(rect);
  determinePosition(winSize);
  sprite.setTexture(texture);
}

void Floor::determinePosition(sf::Vector2u winSize)
{
  sf::Vector2f pos(0, winSize.y - texture.getSize().y);
  sprite.setPosition(pos);
}
