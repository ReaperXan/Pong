#include "Paddle.h"

// Konstruktor domy�lny Paddle
Paddle::Paddle() {
    // Implementacja konstruktora domy�lnego
}

// Konstruktor Paddle
Paddle::Paddle(sf::Vector2f size, sf::Vector2f position, sf::Color color) : score(0) {
    // Inicjalizacja rozmiaru, pozycji i koloru dla kszta�tu
    shape.setSize(size);
    shape.setPosition(position);
    shape.setFillColor(color);
}

// Metoda move
void Paddle::move(float y) {
    // Przesuni�cie kszta�tu o warto�� y
    shape.move(0, y);
}