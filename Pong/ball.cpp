#include "Ball.h"

// Konstruktor domyœlny Ball
Ball::Ball() {
    // Implementacja konstruktora domyœlnego
}

// Konstruktor Ball
Ball::Ball(sf::Vector2f position, float radius, sf::Color color, float speed, float directionX, float directionY) :
    speed(speed),
    directionX(directionX),
    directionY(directionY) {
    // Inicjalizacja promienia, koloru, prêdkoœci oraz kierunków dla kszta³tu
    shape.setRadius(radius);
    shape.setFillColor(color);
    shape.setPosition(position);
}

// Metoda move
void Ball::move(float deltaTime) {
    // Przesuniêcie kszta³tu o wartoœæ prêdkoœci pomno¿on¹ przez kierunki i czas (deltaTime)
    shape.move(speed * directionX * deltaTime, speed * directionY * deltaTime);
}