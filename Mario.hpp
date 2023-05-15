#pragma once
#include "./Object.hpp"

class Mario : public Object {
public:
  enum State {
    STAND,
    RUN_1,
    RUN_2,
    RUN_3,
    SLIDE,
    JUMP,
    FALL
  };
  Mario(void);
  void setState(State _state);
  State getState(void);
  void setHeading(int _heading);
  int getHeading(void);
  float getAcceleration(void);
  void setAcceleration(float _acc);
  sf::Vector2f getVelocity();
  bool getFalling(void);
  void step(sf::Time elapsed);
  void rotateTexture(void);
  void jump(void);
  bool getJumping(void);
  void stop(void);
  void initMove(void);
private:
  State state;
  int heading = 0; // 0: right, 1: left
  sf::Vector2f vel;
  float acc; // vertical acceleration a.k.a. gravity
};
