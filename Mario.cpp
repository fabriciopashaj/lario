#include <iostream>
#include "./Mario.hpp"

static char const *const imagePaths[] = {
  ".\\assets\\mario1.png",
  ".\\assets\\mario2.png",
  ".\\assets\\mario3.png",
  ".\\assets\\mario4.png",
  ".\\assets\\mario5.png",
  ".\\assets\\mario6.png",
  ".\\assets\\mario7.png"
};
static sf::Texture textures[7][2];
static bool initialised = false;

Mario::Mario(void): state(State::STAND), vel(0.f, 0.f), acc(0.f)
{
  if (!initialised)
  {
    sf::Image image;
    for (int i = 0; i < 7; ++i)
    {
      if (!image.loadFromFile(imagePaths[i]))
      {
        // TODO: Throw exception
      }
      textures[i][1].loadFromImage(image);
      image.flipHorizontally();
      textures[i][0].loadFromImage(image);
    }
    initialised = true;
  }
  sprite.setTexture(textures[(int)state][heading]);
  sprite.setScale(7.5f / 10.f, 7.5f / 10.f);
}

void Mario::setState(State _state)
{
  if (state != _state) sprite.setTexture(textures[(int)_state][heading]);
  state = _state;
  if (state == State::JUMP)
  {
    acc = 0.f;
  }
}

Mario::State Mario::getState(void)
{
  return state;
}

void Mario::setHeading(int _heading)
{
  if (heading != _heading) sprite.setTexture(textures[(int)state][_heading]);
  heading = _heading;
  vel.x = _heading == 0 ? std::abs(vel.x) : -std::abs(vel.x);
  acc = _heading == 0 ? std::abs(acc) : -std::abs(acc);
}

int Mario::getHeading(void)
{
  return heading;
}

float Mario::getAcceleration(void)
{
  return acc;
}

void Mario::setAcceleration(float _acc)
{
  acc = _acc;
}

sf::Vector2f Mario::getVelocity(void)
{
  return vel;
}

bool Mario::getFalling(void)
{
  return vel.y > 0;
}

void Mario::initMove(void)
{
  vel.x = 80.f * (1 - 2 * heading);
}

void Mario::step(sf::Time elapsed)
{
  if (state == State::SLIDE)
  {
    heading = !heading;
    setState(State::STAND);
    return;
  } else if (state == State::STAND)
  {
    setState(State::RUN_1);
  }
  move(1e-2f * vel);
  vel.y += acc * elapsed.asSeconds();
}

void Mario::rotateTexture(void)
{
  setState((State)(1 + ((int)state % 3)));
}

void Mario::jump(void)
{
  setState(State::JUMP);
  vel.y = -200.f;
  acc = 700.f;
}

bool Mario::getJumping(void)
{
  return acc != 0;
}

void Mario::stop(void)
{
  setState(State::STAND);
  vel.x = 0;
  vel.y = 0;
  acc = 0;
}
