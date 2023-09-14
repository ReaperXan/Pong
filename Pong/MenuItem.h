#pragma once
#include <SFML/Graphics.hpp>
class MenuItem {
public:
    MenuItem(sf::Vector2f position, sf::Vector2f size, sf::Color color, const std::string& text, sf::Font& font);
    bool contains(sf::Vector2f point) const;
    void draw(sf::RenderWindow& window, sf::Font& font) const;
    void setOutline(const sf::Color& color, float thickness);
private:
    sf::RectangleShape mShape;
    sf::Text mText;
    sf::Color mOutlineColor; // Kolor obramowania
    float mOutlineThickness; // Gruboœæ obramowania
};