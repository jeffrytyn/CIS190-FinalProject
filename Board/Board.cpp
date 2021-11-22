#include "Board.hpp"

Board::Board(int t, int l) : top{t}, left{l}
{
  for (int i = 0; i < ROWS; i++)
  {
    std::array<int, COLS> row;
    row.fill(-1);
    board.push_back(row);
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

int Board::clear_rows()
{
  int num_cleared = 0;
  int i = 0;
  while (i < ROWS)
  {
    std::array row = board.at(i);
    if (!std::count(row.begin(), row.end(), -1))
    {
      board.erase(std::next(board.begin() + i));
      std::array<int, COLS> empty_row;
      empty_row.fill(-1);
      board.push_back(empty_row);
      num_cleared++;
    }
    else
    {
      i++;
    }
  }
  return num_cleared;
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