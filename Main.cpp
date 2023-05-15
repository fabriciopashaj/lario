#include <iostream>
#include <SFML/Window.hpp>
#include "./Object.hpp"
#include "./Platform.hpp"
#include "./Floor.hpp"
#include "./Turtle.hpp"
#include "./Game.hpp"

int main(void)
{
  sf::VideoMode mode = sf::VideoMode::getDesktopMode();
  int size = std::min(mode.height, mode.width) - 30;
  sf::RenderWindow win(sf::VideoMode(size, size - 75), "Mario");
  Game game(win);
  game.init();
  game.run();
  return 0;
}
