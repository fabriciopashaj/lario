#pragma once
#include "./Object.hpp"

class Pipe : public Object {
public:
  enum Kind {
    NORMAL,
    S_SHAPED
  };
  Pipe(Kind _kind, int _exitSide = 0);
private:
  sf::Texture texture;
  Kind kind;
  int exitSide; // 0: right, 1: left
};
