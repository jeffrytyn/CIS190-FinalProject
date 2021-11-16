#include "Board.hpp"

Board::Board(int t, int l) : top{t}, left{l}
{
  board.fill(std::array<int, COLS>{});
  for (auto &row : board)
  {
    row.fill(-1);
  }
};

void Board::set_x_y(int x, int y, int shape)
{
  board.at(y).at(x) = shape;
}

int Board::get_x_y(int x, int y)
{
  return board.at(y).at(x);
}

void Board::draw(sf::RenderTarget &rt) const
{
  sf::RectangleShape block{sf::Vector2f(CELL_SIZE, CELL_SIZE)};
  block.setOutlineThickness(CELL_BORDER);
  block.setOutlineColor(sf::Color::Black);
  for (int i = 0; i < ROWS; i++)
  {
    for (int j = 0; j < COLS; j++)
    {
      int shape = board.at(i).at(j);
      block.setFillColor(shape == -1 ? sf::Color(127, 127, 127) : colors.at(shape));
      block.setPosition(left + j * BORDERED_CELL_SIZE, top + i * BORDERED_CELL_SIZE);
      rt.draw(block);
    }
  }
}

void Board::drawCoord(sf::RenderTarget &rt, int x, int y, int color) const
{
  sf::RectangleShape block{sf::Vector2f(CELL_SIZE, CELL_SIZE)};
  block.setOutlineThickness(CELL_BORDER);
  block.setOutlineColor(sf::Color::Black);
  block.setFillColor(colors.at(color));
  block.setPosition(left + x * BORDERED_CELL_SIZE, top + y * BORDERED_CELL_SIZE);
  rt.draw(block);
}