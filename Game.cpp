#include <iostream>
#include "./Game.hpp"

Game::Game(sf::RenderWindow &_win)
  : win(_win), floor(_win.getSize()), scoreBoard(3, 0)
{}

void Game::init(int turtleCount)
{
  initStatic();
  initTurtles(turtleCount);
  initialised = true;
}

void Game::initStatic(void)
{
  sf::Vector2u winSize = win.getSize();
  ////////////////////////////// Platforms ////////////////////////////////////
  Platform pl1(4);
  pl1.setPosition(sf::Vector2f(0, (float)winSize.y * 13.f / 25.f));
  platforms.push_back(pl1);
  Platform pl2(4);
  pl2.setPosition(sf::Vector2f(winSize.x - pl1.boundingBox().width,
                               pl1.boundingBox().top));
  platforms.push_back(pl2);
  Platform middle(16);
  middle.setPosition(
      sf::Vector2f(winSize.x / 2 - middle.boundingBox().width / 2,
                   pl2.boundingBox().top -
                    pl2.boundingBox().height * 10.f / 6.f));
  platforms.push_back(middle);
  Platform pl3(12);
  pl3.setPosition(sf::Vector2f(0, (float)winSize.y * 14.f / 20.f));
  platforms.push_back(pl3);
  Platform pl4(12);
  pl4.setPosition(sf::Vector2f(winSize.x - pl3.boundingBox().width,
                              pl3.boundingBox().top));
  platforms.push_back(pl4);
  Platform pl5(14);
  pl5.setPosition(sf::Vector2f(0, (float)winSize.y * 5.3f / 20.f));
  platforms.push_back(pl5);
  Platform pl6(14);
  pl6.setPosition(sf::Vector2f(winSize.x - pl5.boundingBox().width,
                              pl5.boundingBox().top));
  platforms.push_back(pl6);
  //////////////////////////////// Pipes //////////////////////////////////////
  Pipe pi1(Pipe::Kind::NORMAL, 0);
  pi1.setPosition(
      sf::Vector2f(0, floor.boundingBox().top - pi1.boundingBox().height));
  pipes.push_back(pi1);
  Pipe pi2(Pipe::Kind::NORMAL, 1);
  pi2.setPosition(
      sf::Vector2f(winSize.x - pi2.boundingBox().width,
                   pi1.boundingBox().top));
  pipes.push_back(pi2);
  Pipe pi3(Pipe::Kind::S_SHAPED, 0);
  pi3.setPosition(
      sf::Vector2f(0,
                   pl5.boundingBox().top -
                    pi3.boundingBox().height * 9.f / 8.f));
  pipes.push_back(pi3);
  Pipe pi4(Pipe::Kind::S_SHAPED, 1);
  pi4.setPosition(
      sf::Vector2f(winSize.x - pi4.boundingBox().width,
                   pi3.boundingBox().top));
  pipes.push_back(pi4);
}

void Game::initTurtles(int turtleCount)
{
  sf::Vector2u winSize = win.getSize();
  for (int i = 0; i < turtleCount; ++i)
  {
    Turtle *turtle = new Turtle();
    turtle->setPosition(sf::Vector2f(150 * i,
                                     floor.boundingBox().top -
                                     turtle->boundingBox().height));
    // TODO: Set turtle initial position
    turtles.emplace_back(turtle);
  }
}

void Game::mainMenu(void)
{}

void Game::playing(void)
{
  win.clear();
  floor.draw(win);
  for (auto turtle : turtles)
  {
    turtle->draw(win);
    turtle->move(sf::Vector2f(1e-1f, 0.f));
  }
  for (auto &platform : platforms)
  {
    platform.draw(win);
  }
  for (auto &pipe : pipes)
  {
    pipe.draw(win);
  }
  scoreBoard.draw(win);
  win.display();
}

void Game::pause(void)
{}

void Game::over(void)
{}

void Game::run(void)
{
  while (win.isOpen())
  {
    handleEvents();
    switch (state)
    {
      case State::MENU   : mainMenu(); break;
      case State::PLAYING: playing();  break;
      case State::PAUSE  : pause();    break;
      case State::OVER   : over();     break;
    }
  }
}

void Game::handleEvents(void)
{
  sf::Event event;
  while (win.pollEvent(event))
  {
    if (event.type == sf::Event::Closed) win.close();
    else if (event.type == sf::Event::KeyPressed &&
             event.key.code == sf::Keyboard::Escape)
    {
      if (state == State::PLAYING) state = State::PAUSE;
      else if (state == State::PAUSE) state = State::PLAYING;
    }
  }
}
