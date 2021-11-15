#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

constexpr unsigned int WINDOW_X = 100;
constexpr unsigned int WINDOW_Y = 50;
constexpr unsigned int WINDOW_WIDTH = 600;
constexpr unsigned int WINDOW_HEIGHT = 700;

constexpr unsigned int BOARD_WIDTH = 300;
constexpr unsigned int BOARD_HEIGHT = 600;
constexpr unsigned int BOARD_VERT_OFFSET = (WINDOW_HEIGHT - BOARD_HEIGHT) / 2;
constexpr unsigned int BOARD_HORZ_OFFSET = 25;

constexpr float CELL_BORDER = 1.5f;
constexpr unsigned int COLS = 10;
constexpr unsigned int ROWS = 20;
constexpr float CELL_SIZE = BOARD_HEIGHT / ROWS - (2 * CELL_BORDER);
constexpr float BORDERED_CELL_SIZE = CELL_SIZE + 2 * CELL_BORDER;

const std::array<std::array<int, COLS>, ROWS> board = {0};

const std::array<sf::Color, 7> colors = {
    sf::Color(0, 255, 255),
    sf::Color(255, 0, 255),
    sf::Color(128, 0, 128),
    sf::Color(0, 255, 0),
    sf::Color(255, 0, 0),
    sf::Color(255, 127, 0),
    sf::Color(0, 0, 255)};

// in milliseconds
const sf::Time FRAME_TIME = sf::seconds(1);
