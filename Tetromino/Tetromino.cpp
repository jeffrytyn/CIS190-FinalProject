#include "Tetromino.hpp"
#include <iostream>

Tetromino::Tetromino() {}

Tetromino::Tetromino(Shape shape) : shape{shape}, orientation{0}
{
  switch (shape)
  {
  case I: // I
  {
    center = sf::Vector2i(1, 0);
    offsets[0] = sf::Vector2i(-1, 0);
    offsets[1] = sf::Vector2i(2, 0);
    offsets[2] = sf::Vector2i(3, 0);
    break;
  }
  case J: // J
  {
    center = sf::Vector2i(1, 1);
    offsets[0] = sf::Vector2i(-1, -1);
    offsets[1] = sf::Vector2i(-1, 0);
    offsets[2] = sf::Vector2i(1, 0);
    break;
  }
  case L: // L
  {
    center = sf::Vector2i(1, 1);
    offsets[0] = sf::Vector2i(-1, 0);
    offsets[1] = sf::Vector2i(1, 0);
    offsets[2] = sf::Vector2i(1, -1);
    break;
  }
  case O: // O
  {
    center = sf::Vector2i(0, 0);
    offsets[0] = sf::Vector2i(1, 0);
    offsets[1] = sf::Vector2i(0, 1);
    offsets[2] = sf::Vector2i(1, 1);
    break;
  }
  case S: // S
  {
    center = sf::Vector2i(1, 1);
    offsets[0] = sf::Vector2i(-1, 0);
    offsets[1] = sf::Vector2i(0, -1);
    offsets[2] = sf::Vector2i(1, -1);
    break;
  }
  case T: // T
  {
    center = sf::Vector2i(1, 1);
    offsets[0] = sf::Vector2i(-1, 0);
    offsets[1] = sf::Vector2i(0, -1);
    offsets[2] = sf::Vector2i(1, 0);
    break;
  }
  case Z: // Z
  {
    center = sf::Vector2i(1, 1);
    offsets[0] = sf::Vector2i(0, -1);
    offsets[1] = sf::Vector2i(-1, -1);
    offsets[2] = sf::Vector2i(1, 0);
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
  offsets = tet.offsets;
  orientation = tet.orientation;
  return *this;
}

Shape Tetromino::get_shape() const
{
  return shape;
}

sf::Vector2i Tetromino::get_center() const
{
  return center;
}

std::array<sf::Vector2i, Tetromino::NUM_OFFSETS> Tetromino::get_offsets() const
{
  return offsets;
}

void Tetromino::move(int x_delta, int y_delta)
{
  center.x += x_delta;
  center.y += y_delta;
}

void Tetromino::move_down()
{
  return this->move(0, 1);
}

void Tetromino::move_left()
{
  return this->move(-1, 0);
}

void Tetromino::move_right()
{
  return this->move(1, 0);
}

void Tetromino::rotate_right()
{
  // wall kicks implement in Game.cpp (if we even do that lOl)
  // rotate clockwise
  if (shape == O)
    return;
  if (shape == I)
  {
  }
  else
  {
    std::array temp = offsets;
    for (sf::Vector2i offset : offsets)
    {
      int old_x = offset.x;
      int old_y = offset.y;
      offset.x = -old_y;
      offset.y = old_x;
    }
    // if rotation is out of bounds, try wall kicks
    // all wall kicks fail = restore temp as offsets
  }
}

void Tetromino::rotate_left()
{
  // rotate counterclockwise
  if (shape == O)
    return;
  if (shape == I)
  {
  }
  else
  {
    std::array temp = offsets;
    for (sf::Vector2i offset : offsets)
    {
      int old_x = offset.x;
      int old_y = offset.y;
      offset.x = old_y;
      offset.y = -old_x;
    }
  }
}

void Tetromino::draw(sf::RenderTarget &rt, const Board &board) const
{
  board.drawCoord(rt, center.x, center.y, shape);
  for (sf::Vector2i offset : offsets)
  {
    board.drawCoord(rt, center.x + offset.x, center.y + offset.y, shape);
  }
}