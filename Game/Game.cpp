#include "Game.hpp"
#include <random>
#include <iostream>

Game::Game() : board{BOARD_VERT_OFFSET, BOARD_HORZ_OFFSET}, piece{(Shape)(rand() % 7)}
{
  secondsSinceLastMove = sf::milliseconds(0);
  piece.move(board.COLS / 2 - 1, 0);
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
    {
      std::cout << "Start new round\n";
      newRound();
    }
    else
      piece.move_down();
    secondsSinceLastMove = sf::Time::Zero;
  }
}

void Game::newRound()
{
  sf::Vector2i center = piece.get_center();
  board.set_x_y(center.x, center.y, piece.get_shape());
  for (sf::Vector2i offset : piece.get_offsets())
  {
    board.set_x_y(center.x + offset.x, center.y + offset.y, piece.get_shape());
  }
  piece = Tetromino{(Shape)(rand() % 7)};
  piece.move(board.COLS / 2 - 1, 0);
}

bool Game::check_free_coord(int x, int y)
{
  return x < board.COLS && y < board.ROWS && x >= 0 && y >= 0 && board.get_x_y(x, y) == -1;
}

bool Game::can_move(int x_delta, int y_delta)
{
  sf::Vector2i center = piece.get_center();
  if (!check_free_coord(center.x + x_delta, center.y + y_delta))
    return false;
  for (sf::Vector2i offset : piece.get_offsets())
  {
    if (!check_free_coord(center.x + offset.x + x_delta, center.y + offset.y + y_delta))
      return false;
  }
  return true;
}

void Game::draw(sf::RenderTarget &rt) const
{
  board.draw(rt);
  piece.draw(rt, board);
}