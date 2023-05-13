#pragma once
#include <list>
#include <vector>
#include "./Object.hpp"
#include "./Platform.hpp"
#include "./Floor.hpp"
#include "./Pipe.hpp"
#include "./Turtle.hpp"
#include "./ScoreBoard.hpp"

class Game {
public:
  enum State {
    MENU,
    PLAYING,
    PAUSE,
    OVER
  };
  Game(sf::RenderWindow &_win);
  void init(int turtleCount = 5);
  void run(void);
private:
  sf::RenderWindow &win;
  bool initialised = false;
  State state = State::PLAYING;
  ScoreBoard scoreBoard;
  Floor floor;
  std::vector<Platform> platforms;
  std::vector<Pipe> pipes;
  std::list<Turtle *> turtles;
  void handleEvents(void);
  void initTurtles(int turtleCount);
  void initStatic(void);
  void mainMenu(void);
  void playing(void);
  void pause(void);
  void over(void);
};
