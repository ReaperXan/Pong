#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>
class Paddle {
public:
    sf::RectangleShape shape;
    int score;
    Paddle();
    Paddle(sf::Vector2f size, sf::Vector2f position, sf::Color color);
    void move(float y);
};