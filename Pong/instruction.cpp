#include "instruction.h"

void Instruction::Show(sf::RenderWindow& window) {
    // Tworzenie nowego okna
    sf::RenderWindow scoresWindow(sf::VideoMode(800, 600), "Scores");
    scoresWindow.setVerticalSyncEnabled(true);

    // Obraz z instrukcjami
    sf::Texture instructionsTexture;
    if (!instructionsTexture.loadFromFile("obraz/instr.png")) {
        std::cerr << "Failed to load instructions image!" << std::endl;
        return;
    }
    sf::Sprite instructionsSprite(instructionsTexture);
    instructionsSprite.setPosition(scoresWindow.getSize().x / 2.f - instructionsSprite.getLocalBounds().width / 2.f,
        scoresWindow.getSize().y / 2.f - instructionsSprite.getLocalBounds().height / 2.f);

    // Tekst "Naciœnij PPM aby wróciæ do menu"
    sf::Font font;
    if (!font.loadFromFile("font/arial.ttf")) {
        std::cerr << "Failed to load font!" << std::endl;
        return;
    }
   

    while (scoresWindow.isOpen()) {
        sf::Event event;
        while (scoresWindow.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                scoresWindow.close();
            }
            else if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Right) {
                scoresWindow.close();
            }
        }

        scoresWindow.clear();
        scoresWindow.draw(instructionsSprite);
        scoresWindow.display();
    }
}