#pragma once
#include "./Object.hpp"

class Turtle : public Object {
public:
  enum State {
    MOVING_1,
    MOVING_2,
    MOVING_3,
    TURNING,
    FLIPPED
  };
  Turtle(Turtle::State _state = Turtle::State::MOVING_1);
  void setState(Turtle::State _state);
  Turtle::State getState(void);
  void setHeading(int _heading);
  int getHeading(void);
  float getAcceleration(void);
  void setAcceleration(float _acc);
  sf::Vector2f getVelocity();
  void setFalling(bool falling);
  bool getFalling(void);
  void step(sf::Time elapsed);
private:
  Turtle::State state;
  sf::Texture texture;
  int heading = 0; // 0: right, 1: left
  sf::Vector2f vel;
  sf::Vector2f acc;
};
