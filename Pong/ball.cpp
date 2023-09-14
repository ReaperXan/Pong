#include "Ball.h"

// Konstruktor domy�lny Ball
Ball::Ball() {
    // Implementacja konstruktora domy�lnego
}

// Konstruktor Ball
Ball::Ball(sf::Vector2f position, float radius, sf::Color color, float speed, float directionX, float directionY) :
    speed(speed),
    directionX(directionX),
    directionY(directionY) {
    // Inicjalizacja promienia, koloru, pr�dko�ci oraz kierunk�w dla kszta�tu
    shape.setRadius(radius);
    shape.setFillColor(color);
    shape.setPosition(position);
}

// Metoda move
void Ball::move(float deltaTime) {
    // Przesuni�cie kszta�tu o warto�� pr�dko�ci pomno�on� przez kierunki i czas (deltaTime)
    shape.move(speed * directionX * deltaTime, speed * directionY * deltaTime);
}