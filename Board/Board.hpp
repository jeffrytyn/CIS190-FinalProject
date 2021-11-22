#pragma once
#include <array>
#include <SFML/Graphics.hpp>

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

  const std::array<sf::Color, 7> colors = {
      sf::Color(0, 255, 255),
      sf::Color(255, 255, 0),
      sf::Color(128, 0, 128),
      sf::Color(0, 255, 0),
      sf::Color(255, 0, 0),
      sf::Color(255, 127, 0),
      sf::Color(0, 0, 255)};

  Board(int t, int l);
  void set_x_y(int x, int y, int shape);
  int get_x_y(int x, int y);
  int clear_rows();
  void draw(sf::RenderTarget &rt) const;
  void drawCoord(sf::RenderTarget &rt, int x, int y, int color) const;

private:
  std::vector<std::array<int, COLS>> board;
  int top;
  int left;
};