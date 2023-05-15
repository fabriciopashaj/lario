#include <iostream>
#include "./Turtle.hpp"

static char const *const texturePaths[] = {
  ".\\assets\\turtle1.png",
  ".\\assets\\turtle2.png",
  ".\\assets\\turtle3.png",
  ".\\assets\\turtle4.png",
  ".\\assets\\turtle5.png"
};

static sf::Texture textures[5][2];
static bool initialised = false;

Turtle::Turtle(Turtle::State _state)
  : state(_state), vel(110.f, 0), acc(5.5f, 0), moveCount(0)
{
  if (!initialised)
  {
    for (int i = 0; i < 5; ++i)
    {
      sf::Image image;
      if (image.loadFromFile(texturePaths[i]))
      {
        textures[i][0].loadFromImage(image);
        image.flipHorizontally();
        textures[i][1].loadFromImage(image);
      } else
      {
        // TODO: Throw error
      }
    }
    initialised = true;
  }
  sprite.setTexture(textures[(int)state][heading]);
  sprite.setScale(7.5f / 10.f, 7.5f / 10.f);
}

void Turtle::setState(State _state)
{
  state = _state;
  sprite.setTexture(textures[(int)_state][heading]);
  if (state == State::TURNING)
  {
    vel.x *= -1.f;
    acc.x *= -1.f;
  }
}

Turtle::State Turtle::getState(void)
{
  return state;
}

void Turtle::setHeading(int _heading)
{
  sprite.setTexture(textures[(int)state][_heading]);
  heading = _heading;
  vel.x = _heading == 0 ? std::abs(vel.x) : -std::abs(vel.x);
  acc.x = _heading == 0 ? std::abs(acc.x) : -std::abs(acc.x);
}

int Turtle::getHeading(void)
{
  return heading;
}

float Turtle::getAcceleration(void)
{
  return acc.x;
}

void Turtle::setAcceleration(float _acc)
{
  acc.x = _acc;
}

sf::Vector2f Turtle::getVelocity(void)
{
  return vel;
}

void Turtle::setFalling(bool falling)
{
  acc.y = falling ? 2e4f : 0.f;
  vel.y = falling * 7 * 9.8e1f;
}

bool Turtle::getFalling(void)
{
  return acc.y != 0;
}

void Turtle::step(sf::Time elapsed)
{
  if (state == State::TURNING)
  {
    heading = !heading;
    state = State::MOVING_1;
    return;
  }
  move(elapsed.asSeconds() * vel);
  vel.x += acc.x * elapsed.asSeconds();
  vel.y += acc.y * elapsed.asSeconds();
  if (moveCount == 7)
  {
    if (state != State::FLIPPED)
      setState((Turtle::State)(((int)state + 1) % 3));
    moveCount = 0;
  } else
  {
    ++moveCount;
  }
}

void Turtle::die(void)
{
  setState(State::FLIPPED);
  vel.x = 0;
  vel.y = -50.f;
  acc.x = 0;
  acc.y = 500.f;
}
