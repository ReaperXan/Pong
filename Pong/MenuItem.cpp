#include "MenuItem.h"

// Konstruktor MenuItem
MenuItem::MenuItem(sf::Vector2f position, sf::Vector2f size, sf::Color color, const std::string& text, sf::Font& font) {
    // Ustawianie pozycji, rozmiaru i koloru dla kszta³tu
    mShape.setPosition(position);
    mShape.setSize(size);
    mShape.setFillColor(color);

    // Ustawianie czcionki, tekstu, rozmiaru, koloru i pozycji dla tekstu
    mText.setFont(font);
    mText.setString(text);
    mText.setCharacterSize(30);
    mText.setFillColor(sf::Color::White);
    mText.setPosition(position.x + (size.x - mText.getLocalBounds().width) / 2.f,
        position.y + (size.y - mText.getLocalBounds().height) / 4.f);
}

// Sprawdzanie, czy punkt znajduje siê w obszarze kszta³tu
bool MenuItem::contains(sf::Vector2f point) const {
    return mShape.getGlobalBounds().contains(point);
}
void MenuItem::setOutline(const sf::Color& color, float thickness) {
    mOutlineColor = color;
    mOutlineThickness = thickness;
}

// Rysowanie elementu menu
void MenuItem::draw(sf::RenderWindow& window, sf::Font& font) const {
    window.draw(mShape);
    sf::RectangleShape outlineShape(mShape.getSize());
    outlineShape.setPosition(mShape.getPosition());
    outlineShape.setFillColor(sf::Color::Transparent);
    outlineShape.setOutlineColor(mOutlineColor);
    outlineShape.setOutlineThickness(mOutlineThickness);
    window.draw(outlineShape);
    window.draw(mText);
}