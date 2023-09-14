#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>
class Ball {
public:
    sf::CircleShape shape;
    float speed;
    float directionX;
    float directionY;
    Ball();
    Ball(sf::Vector2f position, float radius, sf::Color color, float speed, float directionX, float directionY);
    void move(float deltaTime);
};