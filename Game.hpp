#pragma once
#include <list>
#include <vector>
#include "./Object.hpp"
#include "./Platform.hpp"
#include "./Floor.hpp"
#include "./Pipe.hpp"
#include "./Turtle.hpp"
#include "./ScoreBoard.hpp"
#include "./Mario.hpp"

class Game {
public:
  enum State {
    MENU,
    PLAYING,
    PAUSE,
    OVER
  };
  Game(sf::RenderWindow &_win);
  void init(void);
  void run(void);
private:
  sf::RenderWindow &win;
  sf::Clock clock;
  bool initialised = false;
  State state = State::MENU;
  sf::Text pauseText;
  ScoreBoard scoreBoard;
  Floor floor;
  Platform platforms[7];
  Pipe pipes[4];
  std::list<Turtle *> turtles;
  Mario mario;
  sf::Clock marioClock;
  sf::Clock marioRotationClock;
  enum Move {
    NONE,
    LEFT,
    RIGHT,
    JUMP
  } moveCmd = Move::NONE;
  bool jump = false;
  struct {
    sf::Text title;
    sf::Text button;
  } menu;
  void handleEvents(void);
  void initTurtles(int turtleCount);
  void initMario(void);
  void initStatic(void);
  void mainMenu(void);
  void playing(void);
  void pause(void);
  void over(void);
  void drawTurtles(bool doTurtleStep, sf::Time elapsed);
};
