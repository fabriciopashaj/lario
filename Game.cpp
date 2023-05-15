#include <iostream>
#include "./Game.hpp"

Game::Game(sf::RenderWindow &_win)
  : win(_win), floor(_win.getSize()), scoreBoard(3, 0)
{}

void Game::init(void)
{
  initStatic();
  // initTurtles(turtleCount);
  pauseText.setFont(scoreBoard.getFont());
  pauseText.setString("PAUSE");
  pauseText.setCharacterSize(45);
  sf::FloatRect pauseTextBounds = pauseText.getLocalBounds();
  pauseText.setPosition(
      sf::Vector2f((win.getSize().x - pauseTextBounds.width) / 2.f,
                   200));
  menu.title.setFont(scoreBoard.getFont());
  menu.title.setString("MARIOOOO");
  menu.title.setCharacterSize(70);
  menu.title.setPosition(
      sf::Vector2f((win.getSize().x - menu.title.getLocalBounds().width) / 2,
                   win.getSize().y / 4.f));
  menu.button.setFont(scoreBoard.getFont());
  menu.button.setString("New game");
  menu.button.setCharacterSize(40);
  menu.button.setFillColor(sf::Color::Yellow);
  menu.button.setPosition(
      sf::Vector2f((win.getSize().x - menu.button.getLocalBounds().width) / 2,
                   menu.title.getGlobalBounds().height + 300));
  win.clear();
  win.draw(menu.title);
  win.draw(menu.button);
  win.display();
  initialised = true;
}

void Game::initStatic(void)
{
  sf::Vector2u winSize = win.getSize();
  ////////////////////////////// Platforms ////////////////////////////////////
  platforms[0] = Platform(4);
  platforms[0].setPosition(sf::Vector2f(0, (float)winSize.y * 13.5f / 25.f));
  platforms[1] = Platform(4);
  platforms[1].setPosition(
      sf::Vector2f(winSize.x - platforms[0].boundingBox().width,
                   platforms[0].boundingBox().top));
  platforms[2] = Platform(16);
  platforms[2].setPosition(
      sf::Vector2f(winSize.x / 2 - platforms[2].boundingBox().width / 2,
                   platforms[1].boundingBox().top -
                    platforms[1].boundingBox().height * 2.5f));
  platforms[3] = Platform(11);
  platforms[3].setPosition(sf::Vector2f(0, (float)winSize.y * 14.f / 20.f));
  platforms[4] = Platform(11);
  platforms[4].setPosition(
      sf::Vector2f(winSize.x - platforms[3].boundingBox().width,
                   platforms[3].boundingBox().top));
  platforms[5] = Platform(12);
  platforms[5].setPosition(sf::Vector2f(0, (float)winSize.y * 5.1f / 20.f));
  platforms[6] = Platform(12);
  platforms[6].setPosition(
      sf::Vector2f(winSize.x - platforms[5].boundingBox().width,
                   platforms[5].boundingBox().top));
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
                   platforms[5].boundingBox().top -
                    pipes[2].boundingBox().height * 9.f / 8.f));
  pipes[3] = Pipe(Pipe::Kind::S_SHAPED, 1);
  pipes[3].setPosition(
      sf::Vector2f(winSize.x - pipes[3].boundingBox().width,
                   pipes[2].boundingBox().top));
  // sort the platforms
  std::sort(&platforms[0], &platforms[7],
            [](Platform &p1, Platform &p2) {
              return p1.getPosition().x < p2.getPosition().x;
            });
}

void Game::initTurtles(int turtleCount)
{
  sf::Vector2u winSize = win.getSize();
  Turtle *turtle = new Turtle();
  turtle->setPosition(
      sf::Vector2f(pipes[2].boundingBox().width,
                   pipes[2].boundingBox().top + pipes[2].boundingBox().height -
                    turtle->boundingBox().height));
  // TODO: Set turtle initial position
  turtles.emplace_back(turtle);
  turtle = new Turtle();
  turtle->setPosition(
      sf::Vector2f(win.getSize().x - pipes[3].boundingBox().width -
                    turtle->boundingBox().width,
                   pipes[2].boundingBox().top + pipes[2].boundingBox().height -
                    turtle->boundingBox().height));
  turtle->setHeading(1);
  turtles.emplace_back(turtle);
  turtle = new Turtle();
  turtle->setPosition(
      sf::Vector2f(win.getSize().x / 2.f,
                   platforms[3].boundingBox().top -
                    turtle->boundingBox().height));
  turtle->setHeading(1);
  turtles.emplace_back(turtle);
  turtle = new Turtle();
  turtle->setPosition(
      sf::Vector2f(win.getSize().x / 3.f,
                   floor.boundingBox().top - turtle->boundingBox().height));
  turtles.emplace_back(turtle);
  turtle = new Turtle();
  turtle->setPosition(
      sf::Vector2f(win.getSize().x * 2.f / 3.f,
                   floor.boundingBox().top - turtle->boundingBox().height));
  turtle->setHeading(1);
  turtles.emplace_back(turtle);
}

void Game::initMario(void)
{
  mario.setPosition(
      sf::Vector2f(win.getSize().x / 4.f,
                   floor.boundingBox().top - mario.boundingBox().height));
  marioClock.restart();
  marioRotationClock.restart();
  mario.stop();
}

void Game::playing(void)
{
  win.clear();
  floor.draw(win);
  sf::Time elapsed;
  bool doStep = false;
  if (marioRotationClock.getElapsedTime().asSeconds() >= 8e-2f &&
      moveCmd != Move::NONE)
  {
    mario.rotateTexture();
    marioRotationClock.restart();
  }
  if (clock.getElapsedTime().asSeconds() >= 1.8e-2f)
  {
    elapsed = clock.restart();
    doStep = true;
  }
  mario.step(marioClock.restart());
  if (mario.getState() != Mario::State::FALL &&
      mario.boundingBox().intersects(floor.boundingBox()))
  {
    mario.setPosition(
        sf::Vector2f(mario.boundingBox().left,
                     floor.boundingBox().top - mario.boundingBox().height));
    mario.stop();
    moveCmd = Move::NONE;
  }
  if (turtles.size() == 0)
  {
    over();
    return;
  }
  for (auto turtle : turtles)
  {
    turtle->draw(win);
    if (mario.boundingBox().intersects(turtle->boundingBox()) &&
        std::abs(mario.boundingBox().left - turtle->boundingBox().left) <
          turtle->boundingBox().width / 2 &&
        mario.boundingBox().top > turtle->boundingBox().top &&
        turtle->getState() != Turtle::State::FLIPPED)
    {
      turtle->die();
      mario.jump();
      scoreBoard.setScore(scoreBoard.getScore() + 100);
      std::cout<<"Turtle dead"<<std::endl;
    }
    if (doStep)
    {
      turtle->step(elapsed);
      if (turtle->getState() == Turtle::State::FLIPPED)
      {
        if (turtle->boundingBox().top >= win.getSize().y)
        {
          std::cout<<"Turtle removed"<<std::endl;
          turtles.remove(turtle);
        }
        continue;
      }
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
        {
          turtle->setPosition(sf::Vector2f(5, bounds.top));
        } else
        {
          turtle->setPosition(sf::Vector2f(win.getSize().x - bounds.width - 5,
                                           bounds.top));
        }
        turtle->setState(Turtle::State::TURNING);
        continue;
      }
      bool shouldFall = true; // !turtle->getFalling();
      bounds = turtle->boundingBox();
      for (Platform *plat = &platforms[0]; plat < &platforms[7]; ++plat)
      {
        sf::FloatRect platBounds = plat->boundingBox();
        if (bounds.intersects(platBounds) && turtle->getFalling() &&
            (bounds.top + bounds.height) <=
            (platBounds.top + platBounds.height * 4.f / 5.f))
        {
          turtle->setFalling(false);
          sf::Vector2f newPos(bounds.left, platBounds.top - bounds.height);
          turtle->setPosition(newPos);
          shouldFall = false;
          break;
        }
      }
      if (bounds.intersects(floor.boundingBox()) && turtle->getFalling())
      {
        turtle->setFalling(false);
        sf::Vector2f newPos(bounds.left, 0);
        newPos.y = floor.boundingBox().top - bounds.height;
        turtle->setPosition(newPos);
        shouldFall = false;
      }
      if (shouldFall) turtle->setFalling(true);
    }
  }
  for (Platform *plat = &platforms[0]; plat < &platforms[7]; ++plat)
  {
    plat->draw(win);
  }
  for (Pipe *pipe = &pipes[0]; pipe < &pipes[4]; ++pipe)
  {
    pipe->draw(win);
  }
  mario.draw(win);
  scoreBoard.draw(win);
  win.display();
}

void Game::over(void)
{}

void Game::run(void)
{
  while (win.isOpen())
  {
    handleEvents();
    if (state == State::PLAYING) playing();
  }
}

void Game::handleEvents(void)
{
  sf::Event event;
  while (win.pollEvent(event))
  {
    if (event.type == sf::Event::Closed)
    {
      win.close();
      break;
    } else if (event.type == sf::Event::KeyPressed)
    {
      if (event.key.code == sf::Keyboard::Escape)
      {
        if (state == State::PLAYING)
        {
          state = State::PAUSE;
          win.draw(pauseText);
          win.display();
        } else if (state == State::PAUSE)
        {
          clock.restart();
          marioClock.restart();
          marioRotationClock.restart();
          state = State::PLAYING;
          moveCmd = Move::NONE;
        }
      } else if (event.key.code == sf::Keyboard::Backspace)
      {
        if (state == State::PAUSE)
        {
          scoreBoard.setLives(3);
          scoreBoard.setScore(0);
          state = State::MENU;
          for (auto turtle : turtles)
          {
            delete turtle;
          }
          moveCmd = Move::NONE;
          turtles.clear();
          win.clear();
          win.draw(menu.title);
          win.draw(menu.button);
          win.display();
        }
      } else if (event.key.code == sf::Keyboard::Enter)
      {
        if (state == State::MENU)
        {
          clock.restart();
          marioClock.restart();
          marioRotationClock.restart();
          state = State::PLAYING;
          initTurtles(5);
          initMario();
        }
      } else if (event.key.code == sf::Keyboard::Up && !mario.getJumping())
      {
        std::cout<<"Jumping"<<std::endl;
        mario.jump();
        moveCmd = Move::JUMP;
      }
      if (moveCmd == Move::NONE)
      {
        if (event.key.code == sf::Keyboard::Left && !mario.getJumping())
        {
          std::cout<<"Going left"<<std::endl;
          mario.setHeading(1);
          mario.initMove();
          moveCmd = moveCmd == Move::RIGHT ? Move::NONE : Move::LEFT;
        } else if (event.key.code == sf::Keyboard::Right &&
                   !mario.getJumping())
        {
          std::cout<<"Going right"<<std::endl;
          mario.setHeading(0);
          mario.initMove();
          moveCmd = moveCmd == Move::LEFT ? Move::NONE : Move::RIGHT;
        }
      }
    } else if (event.type == sf::Event::KeyReleased &&
               (event.key.code == sf::Keyboard::Left ||
                event.key.code == sf::Keyboard::Right) &&
               !mario.getJumping())
    {
      mario.stop();
      moveCmd = Move::NONE;
      std::cout<<"KeyReleased"<<std::endl;
    } else if (event.type == sf::Event::Resized)
    {
      clock.restart();
      marioClock.restart();
      marioRotationClock.restart();
    }
  }
}

