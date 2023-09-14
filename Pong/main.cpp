#include <SFML/Graphics.hpp>
#include "menu.h"
int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Menu");
    Menu menu(window);
    menu.run();
    return 0;
}