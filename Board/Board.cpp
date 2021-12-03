#include "Board.hpp"

const sf::Color Board::EMPTY_CELL = sf::Color(127, 127, 127);
const std::array<sf::Color, 7> Board::colors = {
    sf::Color(0, 255, 255),
    sf::Color(255, 255, 0),
    sf::Color(128, 0, 128),
    sf::Color(0, 255, 0),
    sf::Color(255, 0, 0),
    sf::Color(255, 127, 0),
    sf::Color(0, 0, 255)};

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
  static auto full_row = [](std::array<int, COLS> &row)
  {
    return std::count(row.begin(), row.end(), -1) == 0;
  };
  std::vector<std::array<int, COLS>>::iterator curr = board.end() - 1;
  int num_cleared = 0;
  while (curr >= board.begin())
  {
    if (full_row(*curr))
    {
      num_cleared++;
      if (curr == board.begin())
        break;
      curr--;
      continue;
    }
    *(curr + num_cleared) = std::move(*curr);
    if (curr == board.begin())
      break;
    curr--;
  }
  for (int i = 0; i < num_cleared; i++)
  {
    (*(board.begin() + i)).fill(-1);
  }
  return num_cleared;
}

void Board::reset()
{
  for (int i = 0; i < ROWS; i++)
  {
    (*(board.begin() + i)).fill(-1);
  }
}

// implemented where top left = [ROW, 0] and bottom right = [0, COLS]
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
      block.setFillColor(shape == -1 ? EMPTY_CELL : colors.at(shape));
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

std::ostream &operator<<(std::ostream &out, const Board &b)
{
  for (std::array<int, Board::COLS> row : b.board)
  {
    out << "{ ";
    for (int shape : row)
    {
      out << shape << " ";
    }
    out << "}\n";
  }
  return out;
}