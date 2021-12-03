#pragma once
#include <array>
#include <iostream>
#include "../SFML-2.5.1/include/SFML/Graphics.hpp"

class Board
{
public:
  static constexpr int ROWS = 20;
  static constexpr int COLS = 10;
  static constexpr int BOARD_WIDTH = 300;
  static constexpr int BOARD_HEIGHT = 600;

  static constexpr float CELL_BORDER = 1.5f;
  static constexpr float CELL_SIZE = BOARD_HEIGHT / ROWS - (2 * CELL_BORDER);
  static constexpr float BORDERED_CELL_SIZE = CELL_SIZE + 2 * CELL_BORDER;

  static const sf::Color EMPTY_CELL;
  static const std::array<sf::Color, 7> colors;

  Board(int t, int l);
  void set_x_y(int x, int y, int shape);
  int get_x_y(int x, int y);
  int clear_rows();
  void reset();
  void draw(sf::RenderTarget &rt) const;
  void drawCoord(sf::RenderTarget &rt, int x, int y, int color) const;

  friend std::ostream &operator<<(std::ostream &out, const Board &b);

private:
  std::vector<std::array<int, COLS>> board;
  int top;
  int left;
};