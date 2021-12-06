#pragma once
#include "SFML/Graphics.hpp"
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
  static constexpr int NUM_ORIENTATIONS = 4;
  static constexpr int NUM_KICKS = 4;
  static const std::array<std::array<sf::Vector2i, NUM_KICKS>, NUM_ORIENTATIONS> norm_cw_wallkicks;
  static const std::array<std::array<sf::Vector2i, NUM_KICKS>, NUM_ORIENTATIONS> i_cw_wallkicks;

  Tetromino();
  Tetromino(Shape shape);
  Tetromino &operator=(const Tetromino &t);

  bool get_is_null() const;
  Shape get_shape() const;
  sf::Vector2i get_center() const;
  void set_center(sf::Vector2i new_center);
  std::array<sf::Vector2i, NUM_OFFSETS> get_offsets() const;
  void set_offsets(std::array<sf::Vector2i, NUM_OFFSETS> new_offsets);
  void move(int x_delta, int y_delta);
  void move_down();
  void move_left();
  void move_right();
  void rotate_right();
  void rotate_left();
  void right_wallkick(int test_num);
  void left_wallkick(int test_num);

  void draw(sf::RenderTarget &rt, const Board &board) const;

  friend std::ostream &operator<<(std::ostream &out, const Tetromino &t);

private:
  Shape shape;
  sf::Vector2i center;
  std::array<sf::Vector2i, NUM_OFFSETS> offsets;
  int orientation;
  bool is_null;
};