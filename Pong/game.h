    #include "ball.h"
    #include "paddle.h"
    #include <conio.h>
    #include <fstream>
    #include <regex>
    #include <filesystem>
    #include <SFML/Audio.hpp>
    class Game :public Paddle, public Ball {
    public:
        Game();
        void run();
        sf::Font mFont;
    private:
        void loadSounds();
        void processEvents(sf::Time deltaTime);
        void update(sf::Time deltaTime);
        void render();
        std::string getScoreString();
        void saveScoreToFile(std::string scoreString, std::string directoryPath);
        sf::RenderWindow mWindow;
        Paddle mLeftPaddle;
        Paddle mRightPaddle;
        Ball mBall;
        sf::Text mLeftScoreText;
        sf::Text mRightScoreText;
        sf::VertexArray mLine;
        sf::Text mGameOverText;
        sf::Text mPausedText;
        sf::Text player1Text;
        sf::Text player2Text;
        bool mGameOver;
        bool mPaused;
        int mMatchNumber;
        sf::SoundBuffer mWallSoundBuffer;
        sf::Sound mWallSound;
        sf::SoundBuffer mPaddleSoundBuffer;
        sf::Sound mPaddleSound;
        sf::SoundBuffer mPointSoundBuffer;
        sf::Sound mPointSound;
    };