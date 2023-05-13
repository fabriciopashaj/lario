#include <iostream>
#include "./Turtle.hpp"

static char const *const texturePaths[] = {
  ".\\assets\\turtle1.png",
  ".\\assets\\turtle2.png",
  ".\\assets\\turtle3.png",
  ".\\assets\\turtle4.png",
  ".\\assets\\turtle5.png"
};

static sf::Image images[5][2];
static bool initialised = false;

Turtle::Turtle(Turtle::State _state): state(_state)
{
  if (!initialised)
  {
    for (int i = 0; i < 5; ++i)
    {
      if (images[i][0].loadFromFile(texturePaths[i]))
      {
        sf::Vector2u imgSize = images[i][0].getSize();
        images[i][1].create(imgSize.x, imgSize.y);
        images[i][1].copy(images[i][0], 0, 0);
        images[i][1].flipHorizontally();
      } else
      {
        // TODO: Throw error
      }
    }
    initialised = true;
  }
  texture.loadFromImage(images[(int)state][heading]);
  sprite.setTexture(texture);
  sf::Vector2u size = texture.getSize();
  sf::IntRect rect(0, 0, size.x, size.y);
  sprite.setScale(6.f / 10.f, 6.f / 10.f);
}

void Turtle::setState(Turtle::State _state)
{
  state = _state;
  setHeading(heading);
  texture.update(images[(int)_state][heading]);
}

Turtle::State Turtle::getState(void)
{
  return state;
}

void Turtle::setHeading(int _heading)
{
  texture.update(images[(int)state][_heading]);
  heading = _heading;
}

int Turtle::getHeading(void)
{
  return heading;
}
