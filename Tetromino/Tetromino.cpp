#include "Tetromino.hpp"
#include <iostream>

Tetromino::Tetromino(int shape) : shape{shape}
{
  switch (shape)
  {
  case 0: // I
  {
    coords[0] = sf::Vector2i(0, 0);
    coords[1] = sf::Vector2i(1, 0);
    coords[2] = sf::Vector2i(2, 0);
    coords[3] = sf::Vector2i(3, 0);
    center = -1;
    break;
  }
  case 1: // J
  {
    coords[0] = sf::Vector2i(0, 0);
    coords[1] = sf::Vector2i(0, 1);
    coords[2] = sf::Vector2i(1, 1);
    coords[3] = sf::Vector2i(2, 1);
    center = 2;
    break;
  }
  case 2: // L
  {
    coords[0] = sf::Vector2i(0, 1);
    coords[1] = sf::Vector2i(1, 1);
    coords[2] = sf::Vector2i(2, 1);
    coords[3] = sf::Vector2i(2, 0);
    center = 1;
    break;
  }
  case 3: // O
  {
    coords[0] = sf::Vector2i(0, 0);
    coords[1] = sf::Vector2i(1, 0);
    coords[2] = sf::Vector2i(0, 1);
    coords[3] = sf::Vector2i(1, 1);
    center = -1;
    break;
  }
  case NUM_BLOCKS: // S
  {
    coords[0] = sf::Vector2i(0, 1);
    coords[1] = sf::Vector2i(1, 1);
    coords[2] = sf::Vector2i(1, 0);
    coords[3] = sf::Vector2i(2, 0);
    center = 1;
    break;
  }
  case 5: // T
  {
    coords[0] = sf::Vector2i(0, 1);
    coords[1] = sf::Vector2i(1, 1);
    coords[2] = sf::Vector2i(1, 0);
    coords[3] = sf::Vector2i(2, 1);
    center = 1;
    break;
  }
  case 6: // Z
  {
    coords[0] = sf::Vector2i(0, 0);
    coords[1] = sf::Vector2i(1, 0);
    coords[2] = sf::Vector2i(1, 1);
    coords[3] = sf::Vector2i(2, 1);
    center = 2;
    break;
  }
  default:
    break;
  }
}

Tetromino &Tetromino::operator=(const Tetromino &tet)
{
  center = tet.center;
  shape = tet.shape;
  coords = tet.coords;
  return *this;
}

bool Tetromino::in_piece(int x, int y)
{
  for (auto &coord : coords)
  {
    if (coord.x == x && coord.y == y)
      return true;
  }
  return false;
}

bool Tetromino::can_move(Board &board, int x_delta, int y_delta)
{
  int cols = board.COLS, rows = board.ROWS;
  for (int i = 0; i < NUM_BLOCKS; i++)
  {
    int x = coords[i].x + x_delta, y = coords[i].y + y_delta;
    if (!(x < cols && y < rows && x >= 0 && y >= 0 && (in_piece(x, y) || board.get_x_y(x, y) == -1)))
      return false;
  }
  return true;
}

bool Tetromino::offset(Board &board, int x_delta, int y_delta)
{
  if (!can_move(board, x_delta, y_delta))
    return false;
  for (int i = 0; i < NUM_BLOCKS; i++)
  {
    board.set_x_y(coords[i].x, coords[i].y, -1);
  }
  for (int i = 0; i < NUM_BLOCKS; i++)
  {
    coords[i].x += x_delta;
    coords[i].y += y_delta;
    board.set_x_y(coords[i].x, coords[i].y, shape);
  }
  return true;
}

bool Tetromino::place(Board &board)
{
  return this->offset(board, 0, 0);
}

bool Tetromino::move_down(Board &board)
{
  return this->offset(board, 0, 1);
}

bool Tetromino::move_left(Board &board)
{
  return this->offset(board, -1, 0);
}

bool Tetromino::move_right(Board &board)
{
  return this->offset(board, 1, 0);
}