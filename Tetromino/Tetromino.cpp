#include "Tetromino.hpp"

Tetromino::Tetromino(int shape) : shape{shape}, coords{std::make_unique<sf::Vector2i[]>(4)}
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
  case 4: // S
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

void Tetromino::move_down()
{
  for (int i = 0; i < 4; i++)
  {
    coords[i].y += 1;
  }
}

void Tetromino::move_left()
{
  for (int i = 0; i < 4; i++)
  {
    coords[i].x -= 1;
  }
}

void Tetromino::move_right()
{
  for (int i = 0; i < 4; i++)
  {
    coords[i].x += 1;
  }
}