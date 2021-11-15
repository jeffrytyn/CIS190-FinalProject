#include <SFML/Window.hpp>
#include "globals.hpp"

sf::RectangleShape get_rect(int row, unsigned int col, sf::Color color)
{
  sf::RectangleShape rectangle(sf::Vector2f(CELL_SIZE, CELL_SIZE));
  rectangle.setOutlineThickness(CELL_BORDER);
  rectangle.setOutlineColor(sf::Color::Black);
  rectangle.setFillColor(color);
  rectangle.setPosition(BOARD_HORZ_OFFSET + col * BORDERED_CELL_SIZE, BOARD_VERT_OFFSET + row * BORDERED_CELL_SIZE);
  return rectangle;
}

int main()
{
  sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Tetris!");
  window.setPosition(sf::Vector2i(WINDOW_X, WINDOW_Y));
  window.setFramerateLimit(60);
  sf::Event event;
  sf::Clock clock;

  int curr_row = 0, curr_col = 0;
  while (window.isOpen())
  {
    while (window.pollEvent(event))
    {
      switch (event.type)
      {
      case sf::Event::KeyPressed:
      {
        switch (event.key.code)
        {
        case sf::Keyboard::Left:
        {
          curr_col -= 1;
          break;
        }
        case sf::Keyboard::Right:
        {
          curr_col += 1;
          break;
        }
        case sf::Keyboard::Down:
        {
          curr_row += 1;
          break;
        }
        }
        break;
      }
      case sf::Event::Closed:
      {
        window.close();
        break;
      }
      }
    }
    if (clock.getElapsedTime() >= FRAME_TIME)
    {
      curr_row++;
      clock.restart();
    }
    window.clear();
    sf::RectangleShape rectangle(sf::Vector2f(CELL_SIZE, CELL_SIZE));
    rectangle.setOutlineThickness(CELL_BORDER);
    rectangle.setOutlineColor(sf::Color::Black);
    for (unsigned int i = 0; i < ROWS; i++)
    {
      for (unsigned int j = 0; j < COLS; j++)
      {
        rectangle.setFillColor(sf::Color(127, 127, 127));
        rectangle.setPosition(BOARD_HORZ_OFFSET + j * BORDERED_CELL_SIZE, BOARD_VERT_OFFSET + i * BORDERED_CELL_SIZE);
        window.draw(rectangle);
      }
    }
    rectangle.setPosition(BOARD_HORZ_OFFSET + curr_col * BORDERED_CELL_SIZE, BOARD_VERT_OFFSET + curr_row * BORDERED_CELL_SIZE);
    rectangle.setFillColor(colors.at(0));
    window.draw(rectangle);
    window.display();
  }

  return 0;
}