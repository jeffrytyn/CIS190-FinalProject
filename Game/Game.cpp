#include "Game.hpp"

sf::Font Board::font = sf::Font();

Game::Game() : board{Board::BOARD_VERT_OFFSET, Board::BOARD_HORZ_OFFSET}, score{0}
{
  sinceLastClick = sf::Time::Zero;
  sinceLastMove = sf::Time::Zero;
  sf::Text scoreBoard;
  if (!Board::font.loadFromFile("open-sans/OpenSans-Regular.ttf"))
  {
    std::cout << "Error loading font.\n";
  }

  reset_helper();
  scores.fill(0);

  std::ifstream file{"highscores.txt"};
  std::string buffer;
  int i = 0;
  while (getline(file, buffer))
  {
    scores[i] = std::stoi(buffer);
    i++;
  }
}

void Game::handleKey(const sf::Keyboard::Key &c, const sf::Time &delta)
{
  sinceLastClick += delta;
  switch (c)
  {
  case sf::Keyboard::Left:
  {
    if (sinceLastClick > KEY_BUFFER_TIME && can_move(-1, 0))
    {
      piece.move_left();
      sinceLastClick = sf::Time::Zero;
    }
    break;
  }
  case sf::Keyboard::Right:
  {
    if (sinceLastClick > KEY_BUFFER_TIME && can_move(1, 0))
    {
      piece.move_right();
      sinceLastClick = sf::Time::Zero;
    }
    break;
  }
  case sf::Keyboard::Down:
  {
    if (!can_move(0, 1))
      newRound();
    else if (sinceLastClick > KEY_BUFFER_TIME)
    {
      piece.move_down();
      sinceLastClick = sf::Time::Zero;
    }
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
  case sf::Keyboard::R:
  {
    reset();
    break;
  }
  case sf::Keyboard::C:
  {
    hold();
    break;
  }
  case sf::Keyboard::Space:
  {
    while (can_move(0, 1))
    {
      piece.move_down();
    }
    sinceLastClick = sf::Time::Zero;
    newRound();
    break;
  }
  }
}

void Game::update(const sf::Time &delta)
{
  if (is_moving_down && can_move(0, 1))
  {
    piece.move_down();
  }
  sinceLastMove += delta;
  if (sinceLastMove > FRAME_TIME && is_playing)
  {
    if (!can_move(0, 1))
    {
      newRound();
    }
    else
      piece.move_down();
    sinceLastMove = sf::Time::Zero;
    // sinceLastClick = sf::Time::Zero;
  }

  if (score > scores[lowest_index_on_highscore])
  {
    scores[9] = scores[lowest_index_on_highscore];
    scores[lowest_index_on_highscore] = score;
    lowest_index_on_highscore--;
    std::sort(scores.begin(), scores.end(), std::greater<>());
    std::string str{""};
    for (int i = 0; i < 10; i++)
    {
      str = str + std::to_string(scores[i]) + "\n";
    }
    std::ofstream ofs{"highscores.txt"};
    ofs << str;
  }
}

void Game::genPiece()
{
  Shape shape = (Shape)(rand() % 7);
  Tetromino piece_next = Tetromino{shape};
  piece_next.move(board.COLS / 2 - 2, 0);
  sf::Vector2i center = piece_next.get_center();
  bool is_space = board.get_x_y(center.x, center.y) == -1;

  for (sf::Vector2i offset : piece_next.get_offsets())
  {
    // there's space if all blocks level or lower than center can fit
    if (offset.y >= 0 && board.get_x_y(center.x + offset.x, center.y + offset.y) != -1)
      is_space = false;
  }
  if (is_space)
  {
    piece = piece_next;
  }
  else
  {
    is_playing = false;
  }
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
    // should set a min frame time i.e. can't go below it
    FRAME_TIME = sf::milliseconds(FRAME_TIME.asMilliseconds() * pow(.9, cleared));
  }
  genPiece();
  can_hold = true;
}

bool Game::check_free_coord(int x, int y)
{
  return x < board.COLS && y < board.ROWS && x >= 0 && y >= 0 && board.get_x_y(x, y) == -1;
}

bool Game::can_move(int x_delta, int y_delta)
{
  if (!is_playing)
    return false;
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

void Game::reset()
{
  board.reset();
  reset_helper();
}

void Game::reset_helper()
{
  srand(time(0));
  genPiece();
  sinceLastMove = sf::milliseconds(0);
  is_playing = true;
  can_hold = true;
  Tetromino null_piece{};
  piece_hold = null_piece;
  lowest_index_on_highscore = 9;
}

void Game::hold()
{
  if (can_hold)
  {
    Tetromino new_piece_hold{piece};
    Tetromino hold_center{piece.get_shape()};
    hold_center.move(Board::COLS + 2, 2);
    new_piece_hold.set_center(hold_center.get_center());

    if (piece_hold.get_is_null())
    {
      genPiece();
    }
    else
    {
      Tetromino new_piece{piece_hold};
      Tetromino center{piece_hold.get_shape()};
      center.move(board.COLS / 2 - 2, 0);
      new_piece.set_center(center.get_center());
      piece = new_piece;
    }

    piece_hold = new_piece_hold;
    can_hold = false;
  }
}

std::string Game::get_highscores() const
{
  std::string str{""};
  for (int i = 0; i < 10; i++)
  {
    str = str + "\n" + std::to_string(i + 1) + ". " + std::to_string(scores[i]);
  }
  return str;
}

void Game::draw(sf::RenderTarget &rt) const
{
  board.draw(rt);
  piece.draw(rt, board);
  if (!piece_hold.get_is_null())
    piece_hold.draw(rt, board);

  sf::Text holdText;
  holdText.setPosition(sf::Vector2f(Board::BOARD_HORZ_OFFSET + Board::BOARD_WIDTH + Board::BOARD_HORZ_OFFSET_TEXT, Board::BOARD_VERT_OFFSET));
  holdText.setFont(Board::font);
  if (is_playing)
    holdText.setString("Hold");
  else
    holdText.setString("GAME OVER");
  holdText.setCharacterSize(30);
  holdText.setFillColor(sf::Color::White);
  rt.draw(holdText);

  sf::Text scoreBoard;
  scoreBoard.setPosition(sf::Vector2f(Board::BOARD_HORZ_OFFSET + Board::BOARD_WIDTH + Board::BOARD_HORZ_OFFSET_TEXT, Board::BOARD_VERT_OFFSET + 200));
  scoreBoard.setFont(Board::font);
  scoreBoard.setString("Score: " + std::to_string(score));
  scoreBoard.setCharacterSize(30);
  scoreBoard.setFillColor(sf::Color::White);
  rt.draw(scoreBoard);

  sf::Text highScores;
  highScores.setPosition(sf::Vector2f(Board::BOARD_HORZ_OFFSET + Board::BOARD_WIDTH + Board::BOARD_HORZ_OFFSET_TEXT, Board::BOARD_VERT_OFFSET + 240));
  highScores.setFont(Board::font);
  highScores.setString("High Scores" + get_highscores());
  highScores.setCharacterSize(20);
  highScores.setFillColor(sf::Color::Blue);
  rt.draw(highScores);
}