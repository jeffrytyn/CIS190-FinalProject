#pragma once
#include <SFML/Graphics.hpp>
#include <array>
#include "../Board/Board.hpp"

enum Shape
{
  I = 0,
  J = 1,
  L = 2,
  O = 3,
  S = 4,
  T = 5,
  Z = 6
};

class Tetromino
{
public:
  static constexpr int NUM_OFFSETS = 3;
  const std::array<std::array<sf::Vector2i, 4>, 4> norm_cw_wallkicks = {{{sf::Vector2i(0, 0), sf::Vector2i(0, 0), sf::Vector2i(0, 0), sf::Vector2i(0, 0)},
                                                                         {sf::Vector2i(0, 0), sf::Vector2i(0, 0), sf::Vector2i(0, 0), sf::Vector2i(0, 0)},
                                                                         {sf::Vector2i(0, 0), sf::Vector2i(0, 0), sf::Vector2i(0, 0), sf::Vector2i(0, 0)},
                                                                         {sf::Vector2i(0, 0), sf::Vector2i(0, 0), sf::Vector2i(0, 0), sf::Vector2i(0, 0)}}};

  Tetromino();
  Tetromino(Shape shape);
  Tetromino &operator=(const Tetromino &t);

  Shape get_shape() const;
  sf::Vector2i get_center() const;
  std::array<sf::Vector2i, NUM_OFFSETS> get_offsets() const;
  void move(int x_delta, int y_delta);
  void move_down();
  void move_left();
  void move_right();
  void rotate_right();
  void rotate_left();
  void right_wallkick(int test_num);
  void left_wallkick(int test_num);

  void draw(sf::RenderTarget &rt, const Board &board) const;

private:
  Shape shape;
  sf::Vector2i center;
  std::array<sf::Vector2i, NUM_OFFSETS> offsets;
  int orientation;
};