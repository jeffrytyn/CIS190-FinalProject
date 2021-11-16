#pragma once
#include <SFML/Graphics.hpp>
#include <array>
#include "../Board/Board.hpp"

class Tetromino
{
public:
  static constexpr int NUM_BLOCKS = 4;
  Tetromino(int shape);
  Tetromino &operator=(const Tetromino &t);

  std::array<sf::Vector2i, NUM_BLOCKS> get_coords() const;
  int get_shape() const;
  void offset(int x_delta, int y_delta);
  void move_down();
  void move_left();
  void move_right();
  void rotate_right();
  void rotate_left();

  void draw(sf::RenderTarget &rt, const Board &board) const;

private:
  int shape;
  int center;
  int l, r, t, b;
  std::array<sf::Vector2i, NUM_BLOCKS> coords;
};