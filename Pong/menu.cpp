#include "Menu.h"

Menu::Menu(sf::RenderWindow& window) : mWindow(window) {
    // £adowanie czcionki
    if (!font.loadFromFile("font/arial.ttf")) {
        std::cerr << "Failed to load font!" << std::endl;
    }

    // £adowanie muzyki
    if (!mMusic.openFromFile("music/16bit.wav")) {
        std::cerr << "Failed to load music!" << std::endl;
    }
    if (!mButtonClickBuffer.loadFromFile("music/click.wav")) {
        std::cerr << "Failed to load button click sound!" << std::endl;
    }

    mButtonClickSound.setBuffer(mButtonClickBuffer);

  // £adowanie tekstury t³a
    if (!mBackgroundTexture.loadFromFile("obraz/obraz.png")) {
        std::cerr << "Failed to load background texture!" << std::endl;
    }

    // Ustawienie tekstury dla sprite'a t³a
    mBackgroundSprite.setTexture(mBackgroundTexture);

    // Dodawanie elementów menu
    mItems.push_back(MenuItem(
        sf::Vector2f(window.getSize().x / 2.f - 100.f, window.getSize().y / 2.f - 100.f),
        sf::Vector2f(200.f, 50.f),
        sf::Color::Black,
        "Graj",
        font
    ));
    mItems.back().setOutline(sf::Color::White, 5.f); // Dodanie obramowania

    mItems.push_back(MenuItem(
        sf::Vector2f(window.getSize().x / 2.f - 100.f, window.getSize().y / 2.f),
        sf::Vector2f(200.f, 50.f),
        sf::Color::Black,
        "Wynik",
        font
    ));
    mItems.back().setOutline(sf::Color::White, 5.f); // Dodanie obramowania

    mItems.push_back(MenuItem(
        sf::Vector2f(window.getSize().x / 2.f - 100.f, window.getSize().y / 2.f + 100.f),
        sf::Vector2f(200.f, 50.f),
        sf::Color::Black,
        "Instrukcja",
        font
    ));
    mItems.back().setOutline(sf::Color::White, 5.f); // Dodanie obramowania

    mItems.push_back(MenuItem(
        sf::Vector2f(window.getSize().x / 2.f - 100.f, window.getSize().y / 2.f + 200.f),
        sf::Vector2f(200.f, 50.f),
        sf::Color::Black,
        "Wyjscie",
        font
    ));
    mItems.back().setOutline(sf::Color::White, 5.f);



}

int Menu::run() {
    mMusic.play();
    while (mWindow.isOpen()) {
        sf::Event event;
        while (mWindow.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                mWindow.close();
                return 0;
            }
            else if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                sf::Vector2f mousePosition(event.mouseButton.x, event.mouseButton.y);
                for (std::size_t i = 0; i < mItems.size(); ++i) {
                    if (mItems[i].contains(mousePosition)) {
                        mButtonClickSound.play();
                        if (i == 0) {
                            Game game;
                            game.run();
                        }
                        else if (i == 1) {
                            Scores scores;
                            scores.Show(mWindow);
                        }
                        else if (i == 2) {
                            Instruction instruction;
                            instruction.Show(mWindow);
                        }
                        else if (i == 3) {
                            return 0;
                        }
                    }
                }
            }
        }

        mWindow.clear();
        mWindow.draw(mBackgroundSprite);
        mWindow.draw(mTitleText);
        for (const auto& item : mItems) {
            item.draw(mWindow, font);
        }
        mWindow.display();
    }
    mMusic.stop();
    return 0;
}