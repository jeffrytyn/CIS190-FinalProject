#include "Game.hpp"
#include <random>
#include <iostream>
#include <string>

sf::Font Game::font = sf::Font();

Game::Game() : board{BOARD_VERT_OFFSET, BOARD_HORZ_OFFSET}, score{0}
{
  sf::Text scoreBoard;
  if (!font.loadFromFile("open-sans/OpenSans-Regular.ttf"))
  {
    std::cout << "Error loading font.\n";
  }
  srand(time(0));
  genPiece();
  sinceLastMove = sf::milliseconds(0);
}

void Game::handleKey(const sf::Keyboard::Key &c)
{
  switch (c)
  {
  case sf::Keyboard::Left:
  {
    if (can_move(-1, 0))
      piece.move_left();
    break;
  }
  case sf::Keyboard::Right:
  {
    if (can_move(1, 0))
      piece.move_right();
    break;
  }
  case sf::Keyboard::Down:
  {
    if (!can_move(0, 1))
      newRound();
    else
      piece.move_down();
    sinceLastMove = sf::Time::Zero;
    break;
  }
  case sf::Keyboard::X:
  {
    attempt_rotate(true);
    break;
  }
  case sf::Keyboard::Z:
  {
    attempt_rotate(false);
    break;
  }
  }
}

void Game::update(const sf::Time &delta)
{
  sinceLastMove += delta;
  if (sinceLastMove > FRAME_TIME)
  {
    if (!can_move(0, 1))
    {
      newRound();
    }
    else
      piece.move_down();
    sinceLastMove = sf::Time::Zero;
  }
}

void Game::genPiece()
{
  Shape shape = (Shape)(rand() % 7);
  piece = Tetromino{shape};
  piece.move(board.COLS / 2 - 2, 0);
}

void Game::newRound()
{
  sf::Vector2i center = piece.get_center();
  board.set_x_y(center.x, center.y, piece.get_shape());
  for (sf::Vector2i offset : piece.get_offsets())
  {
    board.set_x_y(center.x + offset.x, center.y + offset.y, piece.get_shape());
  }
  int cleared = board.clear_rows();
  if (cleared != 0)
  {
    // increment score
    score += cleared;
  }
  genPiece();
}

bool Game::check_free_coord(int x, int y)
{
  return x < board.COLS && y < board.ROWS && x >= 0 && y >= 0 && board.get_x_y(x, y) == -1;
}

bool Game::can_move(int x_delta, int y_delta)
{
  sf::Vector2i center = piece.get_center();
  if (!check_free_coord(center.x + x_delta, center.y + y_delta))
    return false;
  for (sf::Vector2i offset : piece.get_offsets())
  {
    if (!check_free_coord(center.x + offset.x + x_delta, center.y + offset.y + y_delta))
      return false;
  }
  return true;
}

bool Game::attempt_rotate(bool cw)
{
  sf::Vector2i old_cent = piece.get_center();
  std::array<sf::Vector2i, Tetromino::NUM_OFFSETS> old_offsets = piece.get_offsets();
  int test_num = 0;
  if (cw)
    piece.rotate_right();
  else
    piece.rotate_left();
  while (!can_move(0, 0) && test_num < 4)
  {
    if (cw)
      piece.right_wallkick(test_num);
    else
      piece.left_wallkick(test_num);
    test_num++;
  }
  if (test_num == 4)
  {
    piece.set_center(old_cent);
    piece.set_offsets(old_offsets);
    return false;
  }
  else
  {
    return true;
  }
}

void Game::draw(sf::RenderTarget &rt) const
{
  board.draw(rt);
  piece.draw(rt, board);
  sf::Text scoreBoard;
  scoreBoard.setPosition(sf::Vector2f(BOARD_HORZ_OFFSET + Board::BOARD_WIDTH + 50, BOARD_VERT_OFFSET));
  scoreBoard.setFont(font);
  scoreBoard.setString("Score: " + std::to_string(score));
  scoreBoard.setCharacterSize(30);
  scoreBoard.setFillColor(sf::Color::White);
  rt.draw(scoreBoard);
}