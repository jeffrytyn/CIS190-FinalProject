#include "SFML/Window.hpp"
#include "Game/Game.hpp"

static constexpr unsigned int WINDOW_X = 100;
static constexpr unsigned int WINDOW_Y = 50;
static constexpr unsigned int WINDOW_WIDTH = 600;
static constexpr unsigned int WINDOW_HEIGHT = 700;

int main()
{
  sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Tetris!");
  window.setPosition(sf::Vector2i(WINDOW_X, WINDOW_Y));
  window.setVerticalSyncEnabled(true);
  sf::Event event;
  sf::Clock clock;
  Game game;

  while (window.isOpen())
  {
    while (window.pollEvent(event))
    {
      switch (event.type)
      {
      case sf::Event::KeyPressed:
        game.handleKey(event.key.code);
        break;
      case sf::Event::Closed:
        window.close();
        break;
      default:
        break;
      }
    }
    game.update(clock.restart());
    window.clear();
    game.draw(window);
    window.display();
  }

  return 0;
}