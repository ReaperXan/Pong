#include "Paddle.h"

// Konstruktor domyœlny Paddle
Paddle::Paddle() {
    // Implementacja konstruktora domyœlnego
}

// Konstruktor Paddle
Paddle::Paddle(sf::Vector2f size, sf::Vector2f position, sf::Color color) : score(0) {
    // Inicjalizacja rozmiaru, pozycji i koloru dla kszta³tu
    shape.setSize(size);
    shape.setPosition(position);
    shape.setFillColor(color);
}

// Metoda move
void Paddle::move(float y) {
    // Przesuniêcie kszta³tu o wartoœæ y
    shape.move(0, y);
}