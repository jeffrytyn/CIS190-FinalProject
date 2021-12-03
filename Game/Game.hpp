#include "../SFML-2.5.1/include/SFML/Graphics.hpp"
#include "../Tetromino/Tetromino.hpp"
#include "../Board/Board.hpp"
#include <random>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

class Game
{
public:
  static constexpr unsigned int BOARD_VERT_OFFSET = 50;
  static constexpr unsigned int BOARD_HORZ_OFFSET = 25;
  static sf::Font font;

  const sf::Time FRAME_TIME = sf::seconds(1);
  Game();
  void handleKey(const sf::Keyboard::Key &c);
  void update(const sf::Time &delta);
  void draw(sf::RenderTarget &rt) const;

  bool check_free_coord(int x, int y);
  bool can_move(int x_delta, int y_delta);
  bool attempt_rotate(bool cw);
  void genPiece();
  void newRound();
  void reset();

  std::string get_highscores() const;

private:
  sf::Time sinceLastMove;
  Board board;
  Tetromino piece;
  int score;
  bool is_playing;
};