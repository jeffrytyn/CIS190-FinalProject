#include "SFML/Graphics.hpp"
#include "../Tetromino/Tetromino.hpp"
#include "../Board/Board.hpp"
#include <random>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <array>

class Game
{
public:
  sf::Time FRAME_TIME = sf::seconds(1);
  const sf::Time KEY_BUFFER_TIME = sf::milliseconds(100);
  Game();
  void handleKey(const sf::Keyboard::Key &c);
  void update(const sf::Time &delta);
  void draw(sf::RenderTarget &rt) const;

  bool check_free_coord(int x, int y);
  bool can_move(int x_delta, int y_delta);
  bool can_move_buffer();
  bool attempt_rotate(bool cw);
  void genPiece();
  void newRound();
  void reset();
  void reset_helper();
  void hold();

  std::string get_highscores() const;

private:
  sf::Time sinceLastMove;
  sf::Time sinceLastClick;
  Board board;
  Tetromino piece;

  Tetromino piece_hold;
  bool can_hold;

  int score;
  std::array<int, 10> scores;
  bool is_playing;
  bool is_moving_down;
};