#include <SFML/Graphics.hpp>
#include "../Tetromino/Tetromino.hpp"
#include "../Board/Board.hpp"

class Game
{
public:
  static constexpr unsigned int BOARD_VERT_OFFSET = 50;
  static constexpr unsigned int BOARD_HORZ_OFFSET = 25;

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

private:
  sf::Time secondsSinceLastMove;
  Board board;
  Tetromino piece;
  int score;
};