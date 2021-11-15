#pragma once
#include <memory>
#include <SFML/System.hpp>

class Tetromino
{
private:
  int shape;
  int center;
  std::unique_ptr<sf::Vector2i[]> coords;

public:
  Tetromino(int);

  void move_down();
  void move_left();
  void move_right();
  void rotate_right();
  void rotate_left();
  void render() const;
};