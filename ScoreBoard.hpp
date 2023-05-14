#pragma once
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

class ScoreBoard {
public:
  ScoreBoard(int _lives, int _score);
  void draw(sf::RenderWindow &win);
  void setScore(int score);
  sf::Font &getFont(void);
  inline int getScore(void) const
  {
    return score;
  }
  inline void setLives(int lives)
  {
    this->lives = lives;
  }
  inline int getLives(void) const
  {
    return lives;
  }
private:
  int score;
  int lives;
  sf::Text scoreText;
  sf::Sprite lifeSprite;
};
