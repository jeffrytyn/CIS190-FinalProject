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

std::array<sf::Vector2i, Tetromino::NUM_BLOCKS> Tetromino::get_coords() const
{
  return coords;
}

int Tetromino::get_shape() const
{
  return shape;
}

void Tetromino::offset(int x_delta, int y_delta)
{
  for (int i = 0; i < NUM_BLOCKS; i++)
  {
    coords[i].x += x_delta;
    coords[i].y += y_delta;
  }
}

void Tetromino::move_down()
{
  return this->offset(0, 1);
}

void Tetromino::move_left()
{
  return this->offset(-1, 0);
}

void Tetromino::move_right()
{
  return this->offset(1, 0);
}

void Tetromino::draw(sf::RenderTarget &rt, const Board &board) const
{
  for (sf::Vector2i coord : coords)
  {
    board.drawCoord(rt, coord.x, coord.y, shape);
  }
}