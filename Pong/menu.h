#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "MenuItem.h"
#include <iostream>
#include "Scores.h"
#include "instruction.h"
class Menu {
public:
    Menu(sf::RenderWindow& window);

    int run();

private:
    sf::RenderWindow& mWindow;
    sf::Font font;
    sf::Text mTitleText;
    std::vector<MenuItem> mItems;
    sf::Texture mBackgroundTexture;
    sf::Sprite mBackgroundSprite;
    // Nowe pola dla muzyki
    sf::Music mMusic;
    bool mMusicPlaying;
    sf::SoundBuffer mButtonClickBuffer;
    sf::Sound mButtonClickSound;
    void playMusic();
    void stopMusic();
};