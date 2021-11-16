#include "Game.hpp"
#include <random>
#include <iostream>

Game::Game() : board{BOARD_VERT_OFFSET, BOARD_HORZ_OFFSET}, piece{1}
{
  secondsSinceLastMove = sf::milliseconds(0);
  piece.place(board);
}

void Game::handleKey(const sf::Keyboard::Key &c)
{
  switch (c)
  {
  case sf::Keyboard::Left:
  {
    piece.move_left(board);
    break;
  }
  case sf::Keyboard::Right:
  {
    piece.move_right(board);
    break;
  }
  case sf::Keyboard::Down:
  {
    if (!piece.move_down(board))
      genRandPiece();
    secondsSinceLastMove = sf::Time::Zero;
    break;
  }
  }
}

void Game::update(const sf::Time &delta)
{
  secondsSinceLastMove += delta;
  if (secondsSinceLastMove > FRAME_TIME)
  {
    if (!piece.move_down(board))
      genRandPiece();
    secondsSinceLastMove = sf::Time::Zero;
  }
}

void Game::genRandPiece()
{
  piece = Tetromino{rand() % 7};
  piece.place(board);
}

void Game::draw(sf::RenderTarget &rt) const
{
  board.draw(rt);
}