#include "Game.hpp"
#include <random>
#include <iostream>

Game::Game() : board{BOARD_VERT_OFFSET, BOARD_HORZ_OFFSET}, piece{1}
{
  secondsSinceLastMove = sf::milliseconds(0);
}

void Game::handleKey(const sf::Keyboard::Key &c)
{
  switch (c)
  {
  case sf::Keyboard::Left:
  {
    if (can_move(-1, 0))
      piece.move_left();
    break;
  }
  case sf::Keyboard::Right:
  {
    if (can_move(1, 0))
      piece.move_right();
    break;
  }
  case sf::Keyboard::Down:
  {
    if (!can_move(0, 1))
      newRound();
    else
      piece.move_down();
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
    if (!can_move(0, 1))
      newRound();
    else
      piece.move_down();
    secondsSinceLastMove = sf::Time::Zero;
  }
}

void Game::newRound()
{
  std::array<sf::Vector2i, Tetromino::NUM_BLOCKS> coords = piece.get_coords();
  for (int i = 0; i < Tetromino::NUM_BLOCKS; i++)
  {
    board.set_x_y(coords[i].x, coords[i].y, piece.get_shape());
  }
  piece = Tetromino{rand() % 7};
}

bool Game::can_move(int x_delta, int y_delta)
{
  int cols = board.COLS, rows = board.ROWS;
  std::array<sf::Vector2i, Tetromino::NUM_BLOCKS> coords = piece.get_coords();
  for (int i = 0; i < Tetromino::NUM_BLOCKS; i++)
  {
    int x = coords[i].x + x_delta, y = coords[i].y + y_delta;
    if (!(x < cols && y < rows && x >= 0 && y >= 0 && board.get_x_y(x, y) == -1))
      return false;
  }
  return true;
}

void Game::draw(sf::RenderTarget &rt) const
{
  board.draw(rt);
  piece.draw(rt, board);
}