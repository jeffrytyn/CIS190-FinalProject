#include "Tetromino.hpp"

const std::array<std::array<sf::Vector2i, Tetromino::NUM_KICKS>, Tetromino::NUM_ORIENTATIONS> Tetromino::norm_cw_wallkicks = {{{sf::Vector2i(-1, 0), sf::Vector2i(-1, -1), sf::Vector2i(0, 2), sf::Vector2i(-1, 2)},
                                                                                                                               {sf::Vector2i(1, 0), sf::Vector2i(1, 1), sf::Vector2i(0, -2), sf::Vector2i(1, -2)},
                                                                                                                               {sf::Vector2i(1, 0), sf::Vector2i(1, -1), sf::Vector2i(0, 2), sf::Vector2i(1, 2)},
                                                                                                                               {sf::Vector2i(-1, 0), sf::Vector2i(-1, 1), sf::Vector2i(0, -2), sf::Vector2i(-1, -2)}}};
const std::array<std::array<sf::Vector2i, Tetromino::NUM_KICKS>, Tetromino::NUM_ORIENTATIONS> Tetromino::i_cw_wallkicks = {{{sf::Vector2i(-2, 0), sf::Vector2i(1, 0), sf::Vector2i(-2, 1), sf::Vector2i(1, -2)},
                                                                                                                            {sf::Vector2i(-1, 0), sf::Vector2i(2, 0), sf::Vector2i(-1, -2), sf::Vector2i(2, 1)},
                                                                                                                            {sf::Vector2i(2, 0), sf::Vector2i(-1, 0), sf::Vector2i(2, -1), sf::Vector2i(-1, 2)},
                                                                                                                            {sf::Vector2i(1, 0), sf::Vector2i(-2, 0), sf::Vector2i(1, 2), sf::Vector2i(-2, -1)}}};

Tetromino::Tetromino() {}

Tetromino::Tetromino(Shape shape) : shape{shape}, orientation{0}
{
  switch (shape)
  {
  case I:
  {
    center = sf::Vector2i(1, 0);
    offsets[0] = sf::Vector2i(-1, 0);
    offsets[1] = sf::Vector2i(1, 0);
    offsets[2] = sf::Vector2i(2, 0);
    break;
  }
  case J:
  {
    center = sf::Vector2i(1, 1);
    offsets[0] = sf::Vector2i(-1, -1);
    offsets[1] = sf::Vector2i(-1, 0);
    offsets[2] = sf::Vector2i(1, 0);
    break;
  }
  case L:
  {
    center = sf::Vector2i(1, 1);
    offsets[0] = sf::Vector2i(-1, 0);
    offsets[1] = sf::Vector2i(1, 0);
    offsets[2] = sf::Vector2i(1, -1);
    break;
  }
  case O:
  {
    center = sf::Vector2i(0, 0);
    offsets[0] = sf::Vector2i(1, 0);
    offsets[1] = sf::Vector2i(0, 1);
    offsets[2] = sf::Vector2i(1, 1);
    break;
  }
  case S:
  {
    center = sf::Vector2i(1, 1);
    offsets[0] = sf::Vector2i(-1, 0);
    offsets[1] = sf::Vector2i(0, -1);
    offsets[2] = sf::Vector2i(1, -1);
    break;
  }
  case T:
  {
    center = sf::Vector2i(1, 1);
    offsets[0] = sf::Vector2i(-1, 0);
    offsets[1] = sf::Vector2i(0, -1);
    offsets[2] = sf::Vector2i(1, 0);
    break;
  }
  case Z:
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

void Tetromino::set_center(sf::Vector2i new_center)
{
  center = new_center;
}

std::array<sf::Vector2i, Tetromino::NUM_OFFSETS> Tetromino::get_offsets() const
{
  return offsets;
}

void Tetromino::set_offsets(std::array<sf::Vector2i, Tetromino::NUM_OFFSETS> new_offsets)
{
  offsets = new_offsets;
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

// rotations will just swap the offset x and y coords
// center remains unchanged except for I pieces
void Tetromino::rotate_right()
{
  // rotate clockwise
  if (shape == O)
    return;
  else
  {
    for (sf::Vector2i &offset : offsets)
    {
      int old_x = offset.x;
      int old_y = offset.y;
      offset.x = -old_y;
      offset.y = old_x;
    }
    if (shape == I)
    {
      if (orientation == 0)
      {
        center.x++;
      }
      else if (orientation == 1)
      {
        center.y++;
      }
      else if (orientation == 2)
      {
        center.x--;
      }
      else
      {
        center.y--;
      }
    }
    orientation = (orientation + 1) % 4;
  }
}

void Tetromino::rotate_left()
{
  // rotate counterclockwise
  if (shape == O)
    return;
  else
  {
    for (sf::Vector2i &offset : offsets)
    {
      int old_x = offset.x;
      int old_y = offset.y;
      offset.x = old_y;
      offset.y = -old_x;
    }
    if (shape == I)
    {
      if (orientation == 0)
      {
        center.y++;
      }
      else if (orientation == 1)
      {
        center.x--;
      }
      else if (orientation == 2)
      {
        center.y--;
      }
      else
      {
        center.x++;
      }
    }
    orientation = orientation == 0 ? 3 : orientation - 1;
  }
}

// wallkicks are used in case rotations go out of bounds/collide with other pieces
// called after rotation
void Tetromino::right_wallkick(int test_num)
{
  sf::Vector2i kick;
  if (shape == I)
  {
    kick = i_cw_wallkicks.at(orientation == 0 ? 3 : orientation - 1).at(test_num);
  }
  else
  {
    kick = norm_cw_wallkicks.at(orientation == 0 ? 3 : orientation - 1).at(test_num);
  }
  move(kick.x, kick.y);
}

void Tetromino::left_wallkick(int test_num)
{
  sf::Vector2i kick;
  if (shape == I)
  {
    kick = i_cw_wallkicks.at(orientation).at(test_num);
  }
  else
  {
    kick = norm_cw_wallkicks.at(orientation).at(test_num);
  }
  move(-kick.x, -kick.y);
}

void Tetromino::draw(sf::RenderTarget &rt, const Board &board) const
{
  board.drawCoord(rt, center.x, center.y, shape);
  for (sf::Vector2i offset : offsets)
  {
    board.drawCoord(rt, center.x + offset.x, center.y + offset.y, shape);
  }
}

std::ostream &operator<<(std::ostream &out, const Tetromino &t)
{
  out << t.shape << "\n";
  out << "Center: " << t.center.x << ", " << t.center.y << "\n";
  out << "Offsets: ";
  for (auto offset : t.offsets)
  {
    out << "{" << offset.x << ", " << offset.y << "} ";
  }
  out << "\n";
  return out;
}