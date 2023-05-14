#include <iostream>
#include <cstring>
#include "./ScoreBoard.hpp"

static sf::Font font;
static sf::Texture marioHead;
static bool initialised = false;

ScoreBoard::ScoreBoard(int _lives, int _score)
  : lives(_lives), score(_score)
{
  if (!initialised)
  {
    if (!font.loadFromFile(".\\assets\\font.ttf"))
    {
      // TODO: Throw error
    }
    if (!marioHead.loadFromFile(".\\assets\\mariohead.png"))
    {
      std::cerr<<"mariohead.png failed to load"<<std::endl;
      // TODO: Throw error
    }
  }
  scoreText.setFont(font);
  scoreText.setString("000000");
  scoreText.setPosition(30, 10);
  lifeSprite.setTexture(marioHead);
}

void ScoreBoard::setScore(int _score)
{
  this->score = _score;
  char scoreStr[] = "000000";
  for (int i = 5; i > 0 && _score != 0; --i)
  {
    char digit = (_score % 10) + '0';
    _score /= 10;
    scoreStr[i] = digit;
  }
  scoreText.setString(scoreStr);
}

void ScoreBoard::draw(sf::RenderWindow &win)
{
  win.draw(scoreText);
  sf::FloatRect textBounds = scoreText.getGlobalBounds();
  sf::Vector2f pos(textBounds.left + textBounds.width * 13.f / 12.f,
                   textBounds.top);
  lifeSprite.setPosition(pos);
  float offset = lifeSprite.getGlobalBounds().width;
  for (int i = 0; i < lives; ++i)
  {
    win.draw(lifeSprite);
    lifeSprite.move(offset, 0);
  }
}

sf::Font &ScoreBoard::getFont(void)
{
  return font;
}
