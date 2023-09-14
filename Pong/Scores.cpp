#include "Scores.h"

void Scores::Show(sf::RenderWindow& window) {
    // Tworzenie nowego okna
    sf::RenderWindow scoresWindow(sf::VideoMode(800, 600), "Scores");
    scoresWindow.setVerticalSyncEnabled(true);

    // Otwórz plik z wynikami
    std::ifstream file("my_scores/mecz 1.txt");
    std::string line;
    std::string scoresText;

    // Odczytaj zawartoœæ pliku linia po linii
    while (std::getline(file, line)) {
        scoresText += line + "\n";
    }
    file.close();

    sf::Font font;
    if (!font.loadFromFile("font/arial.ttf")) {
        std::cerr << "Failed to load font!" << std::endl;
        return;
    }

    // Tekst "Ostatni wynik"
    sf::Text lastScore;
    lastScore.setFont(font);
    lastScore.setString("Ostatni wynik");
    lastScore.setCharacterSize(40);
    lastScore.setFillColor(sf::Color::Green); // Ustawienie koloru na zielony
    lastScore.setPosition(scoresWindow.getSize().x / 2.f - lastScore.getLocalBounds().width / 2.f,
        scoresWindow.getSize().y / 2.f - 50.f - lastScore.getLocalBounds().height);

    // Tekst z wynikami
    sf::Text scores;
    scores.setFont(font);
    scores.setString(scoresText);
    scores.setCharacterSize(30);
    scores.setFillColor(sf::Color::White);
    scores.setPosition(scoresWindow.getSize().x / 2.f - scores.getLocalBounds().width / 2.f,
        scoresWindow.getSize().y / 2.f - scores.getLocalBounds().height / 2.f);

    // Tekst "Naciœnij PPM aby wróciæ do menu"
    sf::Text returnText;
    returnText.setFont(font);
    returnText.setString("Nacisnij PPM aby wrocic do menu");
    returnText.setCharacterSize(16);
    returnText.setFillColor(sf::Color::White);
    returnText.setPosition(scoresWindow.getSize().x - returnText.getLocalBounds().width - 10.f,
        scoresWindow.getSize().y - returnText.getLocalBounds().height - 10.f);

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
        scoresWindow.draw(lastScore);
        scoresWindow.draw(scores);
        scoresWindow.draw(returnText);
        scoresWindow.display();
    }
}