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
  int size = std::min(mode.height, mode.width) - 50;
  sf::RenderWindow win(sf::VideoMode(size, size - 75), "Malario");
  Game game(win);
  game.init(5);
  game.run();
  return 0;
}
