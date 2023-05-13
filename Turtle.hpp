#pragma once
#include "./Object.hpp"

class Turtle : public Object {
public:
  enum class State : int {
    BAFFLED,
    FEET_EXTENDED,
    FEET_RETRACTED,
    TURNING,
    FLIPPED
  };
  Turtle(Turtle::State _state = Turtle::State::FEET_EXTENDED);
  void setState(Turtle::State _state);
  Turtle::State getState(void);
  void setHeading(int _heading);
  int getHeading(void);
  float getVelocity();
  void step(void);
private:
  Turtle::State state;
  sf::Texture texture;
  int heading = 0; // 0: right, 1: left
  float velocity = 1.f;
  bool falling = false;
};
