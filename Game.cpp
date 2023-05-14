#include <iostream>
#include "./Game.hpp"

Game::Game(sf::RenderWindow &_win)
  : win(_win), floor(_win.getSize()), scoreBoard(3, 0)
{}

void Game::init(int turtleCount)
{
  initStatic();
  initTurtles(turtleCount);
  pauseText.setFont(scoreBoard.getFont());
  pauseText.setString("PAUSE");
  sf::FloatRect pauseTextBounds = pauseText.getLocalBounds();
  pauseText.setPosition(
      sf::Vector2f((win.getSize().x - pauseTextBounds.width) / 2,
                   200));
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
  std::sort(platforms.begin(), platforms.end(),
            [](Platform &p1, Platform &p2) {
              return p1.getPosition().x < p2.getPosition().x;
            });
  //////////////////////////////// Pipes //////////////////////////////////////
  pipes[0] = Pipe(Pipe::Kind::NORMAL, 0);
  pipes[0].setPosition(
      sf::Vector2f(0,
                   floor.boundingBox().top - pipes[0].boundingBox().height));
  pipes[1] = Pipe(Pipe::Kind::NORMAL, 1);
  pipes[1].setPosition(
      sf::Vector2f(winSize.x - pipes[1].boundingBox().width,
                   pipes[0].boundingBox().top));
  pipes[2] = Pipe(Pipe::Kind::S_SHAPED, 0);
  pipes[2].setPosition(
      sf::Vector2f(0,
                   pl5.boundingBox().top -
                    pipes[2].boundingBox().height * 9.f / 8.f));
  pipes[3] = Pipe(Pipe::Kind::S_SHAPED, 1);
  pipes[3].setPosition(
      sf::Vector2f(winSize.x - pipes[3].boundingBox().width,
                   pipes[2].boundingBox().top));
}

void Game::initTurtles(int turtleCount)
{
  sf::Vector2u winSize = win.getSize();
  Turtle *turtle = new Turtle();
  turtle->setPosition(
      sf::Vector2f(600,
                   floor.boundingBox().top - turtle->boundingBox().height));
  // TODO: Set turtle initial position
  turtles.emplace_back(turtle);
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
    if (clock.getElapsedTime().asSeconds() >= 0.095)
    {
      turtle->step(clock.restart());
      sf::FloatRect bounds = turtle->boundingBox();
      if ((bounds.left < 0) ||
          ((bounds.left + bounds.width) > win.getSize().x))
      {
        if (bounds.top >= (floor.boundingBox().top - bounds.height))
        {
          sf::Vector2f newPos;
          newPos.y = pipes[2].boundingBox().top;
          newPos.x = bounds.left < 0 ?
                      pipes[2].boundingBox().width - bounds.width / 2 :
                      pipes[3].boundingBox().left - bounds.width / 2;
          turtle->setPosition(newPos);
          turtle->setFalling(true);
        } else if (bounds.left < 0)
          turtle->setPosition(sf::Vector2f(5, bounds.top));
        else
          turtle->setPosition(sf::Vector2f(win.getSize().x - bounds.width - 5,
                                           bounds.top));
        turtle->setState(Turtle::State::TURNING);
        continue;
      }
      turtle->setFalling(true);
      for (auto &plat : platforms)
      {
        if (bounds.intersects(plat.boundingBox()) && turtle->getFalling())
        {
          turtle->setFalling(false);
          sf::Vector2f newPos(bounds.left, 0);
          newPos.y = plat.boundingBox().top - bounds.height;
          turtle->setPosition(newPos);
          break;
        }
      }
      if (bounds.intersects(floor.boundingBox()) && turtle->getFalling())
      {
        turtle->setFalling(false);
        sf::Vector2f newPos(bounds.left, 0);
        newPos.y = floor.boundingBox().top - bounds.height;
        turtle->setPosition(newPos);
      }
    }
  }
  for (auto &platform : platforms)
  {
    platform.draw(win);
  }
  for (int i = 0; i < 4; ++i)
  {
    pipes[i].draw(win);
  }
  scoreBoard.draw(win);
  win.display();
}

void Game::pause(void)
{
  win.draw(pauseText);
  win.display();
  clock.restart();
}

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
