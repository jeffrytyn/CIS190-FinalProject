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

  bool in_piece(int x, int y);
  bool can_move(Board &board, int x_delta, int y_delta);
  bool offset(Board &board, int x_delta, int y_delta);
  bool place(Board &board);
  bool move_down(Board &board);
  bool move_left(Board &board);
  bool move_right(Board &board);
  bool rotate_right(Board &board);
  bool rotate_left(Board &board);

private:
  int shape;
  int center;
  int l, r, t, b;
  std::array<sf::Vector2i, NUM_BLOCKS> coords;
};