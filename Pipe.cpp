#include "./Pipe.hpp"

static sf::Texture textures[2][2];
static bool initialised = false;

Pipe::Pipe(Kind _kind, int _exitSide): kind(_kind), exitSide(_exitSide)
{
  if (!initialised)
  {
    sf::Image images[2][2];
    if (!images[0][1].loadFromFile(".\\assets\\pipe.png"))
    {
      // TODO: Throw exception
    }
    sf::Vector2u size = images[0][1].getSize();
    images[0][0].create(size.x, size.y);
    images[0][0].copy(images[0][1], 0, 0);
    images[0][0].flipHorizontally();
    if (!images[1][0].loadFromFile(".\\assets\\pipeS.png"))
    {
      // TODO: Throw exception
    }
    size = images[1][0].getSize();
    images[1][1].create(size.x, size.y);
    images[1][1].copy(images[1][0], 0, 0);
    images[1][1].flipHorizontally();
    textures[0][0].loadFromImage(images[0][0]);
    textures[0][1].loadFromImage(images[0][1]);
    textures[1][0].loadFromImage(images[1][0]);
    textures[1][1].loadFromImage(images[1][1]);
    initialised = true;
  }
  sprite.setTexture(textures[(int)_kind][(int)_exitSide]);
  sprite.setScale(7.5f / 10.f, 7.5f / 10.f);
}
