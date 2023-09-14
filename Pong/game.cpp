#include "Game.h"

// Konstruktor Game
Game::Game() :
    mFont(),
    mLeftScoreText(),
    mRightScoreText(),
    mLine(sf::Lines, 2),
    mGameOverText(),
    mPausedText(),
    mPaused(false),
    mGameOver(false)
{
    // Tworzenie okna
    mWindow.create(sf::VideoMode(800, 600), "Pong");

    // Inicjalizacja paletek i pi³ki
    mLeftPaddle = Paddle(sf::Vector2f(20, 100), sf::Vector2f(50, 250), sf::Color::Blue);
    mRightPaddle = Paddle(sf::Vector2f(20, 100), sf::Vector2f(730, 250), sf::Color::Red);
    mBall = Ball(sf::Vector2f(400, 300), 10.f, sf::Color::Green, 500.f, -1.f, 0.f);

    // Inicjalizacja numeru meczu
    mMatchNumber = 1;

    // Wczytanie czcionki
    if (!mFont.loadFromFile("font/arial.ttf")) {
        std::cerr << "Nie mo¿na za³adowaæ czcionki" << std::endl;
    }

    // Konfiguracja tekstu "Gracz 1"
    player1Text.setFont(mFont);
    player1Text.setCharacterSize(20);
    player1Text.setString("Gracz 1");
    player1Text.setPosition(230, 50);
    player1Text.setFillColor(sf::Color::Blue);

    // Konfiguracja tekstu "Gracz 2"
    player2Text.setFont(mFont);
    player2Text.setCharacterSize(20);
    player2Text.setString("Gracz 2");
    player2Text.setPosition(480, 50);
    player2Text.setFillColor(sf::Color::Red);

    // Konfiguracja tekstu wyników graczy
    mLeftScoreText.setFont(mFont);
    mLeftScoreText.setCharacterSize(40);
    mLeftScoreText.setPosition(250, 10);

    mRightScoreText.setFont(mFont);
    mRightScoreText.setCharacterSize(40);
    mRightScoreText.setPosition(500, 10);

    // Konfiguracja linii œrodkowej
    mLine[0].position = sf::Vector2f(400, 0);
    mLine[1].position = sf::Vector2f(400, 800);
    mLine[0].color = sf::Color::White;
    mLine[1].color = sf::Color::White;

    // Konfiguracja tekstu "Koniec gry!"
    mGameOverText.setFont(mFont);
    mGameOverText.setCharacterSize(80);
    mGameOverText.setString("Koniec gry!");
    mGameOverText.setPosition(250, 200);

    // Konfiguracja tekstu "PAUZA"
    mPausedText.setFont(mFont);
    mPausedText.setCharacterSize(80);
    mPausedText.setString("PAUZA");
    mPausedText.setPosition(270, 200);

    // Wczytanie dŸwiêków
    if (!mPaddleSoundBuffer.loadFromFile("music/paddle_sound.wav")) {
        std::cerr << "Nie mo¿na za³adowaæ pliku dŸwiêkowego" << std::endl;
    }
    mPaddleSound.setBuffer(mPaddleSoundBuffer);

    if (!mWallSoundBuffer.loadFromFile("music/wall_sound.wav")) {
        std::cerr << "Nie mo¿na za³adowaæ pliku dŸwiêkowego" << std::endl;
    }
    mWallSound.setBuffer(mWallSoundBuffer);

    if (!mPointSoundBuffer.loadFromFile("music/point_sound.wav")) {
        std::cerr << "Nie mo¿na za³adowaæ pliku dŸwiêkowego" << std::endl;
    }
    mPointSound.setBuffer(mPointSoundBuffer);
}

// Metoda run
void Game::run() {
    sf::Clock clock;
    while (mWindow.isOpen()) {
        sf::Time deltaTime = clock.restart();
        processEvents(deltaTime);
        render();

        if (!mPaused) {
            update(deltaTime);
            render();
        }

        if (mGameOver) {
            std::string scoreString = getScoreString();
            saveScoreToFile(scoreString, "my_scores");
        }
    }
}

// Metoda getScoreString
std::string Game::getScoreString() {
    std::stringstream ss;
    ss << "Gracz 1: " << mLeftPaddle.score << "\n";
    ss << "Gracz 2: " << mRightPaddle.score << "\n";
    return ss.str();
}

// Metoda saveScoreToFile
void Game::saveScoreToFile(std::string scoreString, std::string directoryPath) {
    std::filesystem::create_directory(directoryPath);

    std::string fileName = "mecz " + std::to_string(mMatchNumber) + ".txt";
    std::ofstream outputFile(directoryPath + "/" + fileName);
    if (outputFile.is_open()) {
        std::regex scoreRegex("Gracz ([12]): (\\d+)");
        std::smatch scoreMatch;

        while (std::regex_search(scoreString, scoreMatch, scoreRegex)) {
            int playerNumber = std::stoi(scoreMatch[1]);
            int playerScore = std::stoi(scoreMatch[2]);
            outputFile << "Gracz " << playerNumber << ": " << playerScore << std::endl;
            scoreString = scoreMatch.suffix();
        }
        outputFile.close();
        mMatchNumber++;
        mWindow.close();
        system("cls");
    }
    else {
        std::cout << "Nie uda³o siê otworzyæ pliku " << fileName << " do zapisu" << std::endl;
    }
}
// Metoda processEvents
void Game::processEvents(sf::Time deltaTime) {
    sf::Event event;
    while (mWindow.pollEvent(event)) {
        switch (event.type) {
        case sf::Event::Closed:
            mWindow.close();
            break;
        case sf::Event::KeyPressed:
            if (event.key.code == sf::Keyboard::Escape) {
                mWindow.close();
            }
            if (event.key.code == sf::Keyboard::P) {
                mPaused = !mPaused;
            }
            break;
        default:
            break;
        }
    }

    float leftPaddleSpeed = 0.f;
    float rightPaddleSpeed = 0.f;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
        leftPaddleSpeed -= 400.f;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
        leftPaddleSpeed += 400.f;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
        rightPaddleSpeed -= 400.f;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
        rightPaddleSpeed += 400.f;
    }

    mLeftPaddle.move(leftPaddleSpeed * deltaTime.asSeconds());
    mRightPaddle.move(rightPaddleSpeed * deltaTime.asSeconds());

    mLeftScoreText.setString(std::to_string(mLeftPaddle.score));
    mRightScoreText.setString(std::to_string(mRightPaddle.score));
}

// Metoda update
void Game::update(sf::Time deltaTime) {
    mBall.move(deltaTime.asSeconds());

    if (mBall.shape.getPosition().y <= 0) {
        mBall.directionY = 1.f;
        mWallSound.play(); // Odtwarzanie dŸwiêku przy odbiciu od œciany
    }
    else if (mBall.shape.getPosition().y + 2 * mBall.shape.getRadius() >= mWindow.getSize().y) {
        mBall.directionY = -1.f;
        mWallSound.play(); // Odtwarzanie dŸwiêku przy odbiciu od œciany
    }

    if (mBall.shape.getGlobalBounds().intersects(mLeftPaddle.shape.getGlobalBounds())) {
        mBall.directionX = 1.f;
        if (mBall.shape.getPosition().y < mLeftPaddle.shape.getPosition().y + mLeftPaddle.shape.getSize().y / 3.f) {
            mBall.directionY = -1.f;
        }
        else if (mBall.shape.getPosition().y < mLeftPaddle.shape.getPosition().y + 2.f * mLeftPaddle.shape.getSize().y / 3.f) {
            mBall.directionY = 0.f;
        }
        else {
            mBall.directionY = 1.f;
        }
        mPaddleSound.play(); // Odtwarzanie dŸwiêku przy odbiciu od paletki
    }
    else if (mBall.shape.getGlobalBounds().intersects(mRightPaddle.shape.getGlobalBounds())) {
        mBall.directionX = -1.f;
        if (mBall.shape.getPosition().y < mRightPaddle.shape.getPosition().y + mRightPaddle.shape.getSize().y / 3.f) {
            mBall.directionY = -1.f;
        }
        else if (mBall.shape.getPosition().y < mRightPaddle.shape.getPosition().y + 2.f * mRightPaddle.shape.getSize().y / 3.f) {
            mBall.directionY = 0.f;
        }
        else {
            mBall.directionY = 1.f;
        }
        mPaddleSound.play(); // Odtwarzanie dŸwiêku przy odbiciu od paletki
    }

    if (mBall.shape.getPosition().x <= 0) {
        mRightPaddle.score++;
        mRightScoreText.setString(std::to_string(mRightPaddle.score));
        mBall.shape.setPosition(400, 300);
        mBall.directionX = 1.f;
        mBall.directionY = 0.f;
        mPointSound.play(); // Odtwarzanie dŸwiêku przy zdobyciu punktu
    }
    else if (mBall.shape.getPosition().x + 2 * mBall.shape.getRadius() >= mWindow.getSize().x) {
        mLeftPaddle.score++;
        mLeftScoreText.setString(std::to_string(mLeftPaddle.score));
        mBall.shape.setPosition(400, 300);
        mBall.directionX = -1.f;
        mBall.directionY = 0.f;
        mPointSound.play(); // Odtwarzanie dŸwiêku przy zdobyciu punktu
    }

    if (mLeftPaddle.shape.getPosition().y < 0) {
        mLeftPaddle.shape.setPosition(mLeftPaddle.shape.getPosition().x, 0);
    }
    else if (mLeftPaddle.shape.getPosition().y + mLeftPaddle.shape.getSize().y > mWindow.getSize().y) {
        mLeftPaddle.shape.setPosition(mLeftPaddle.shape.getPosition().x, mWindow.getSize().y - mLeftPaddle.shape.getSize().y);
    }

    if (mRightPaddle.shape.getPosition().y < 0) {
        mRightPaddle.shape.setPosition(mRightPaddle.shape.getPosition().x, 0);
    }
    else if (mRightPaddle.shape.getPosition().y + mRightPaddle.shape.getSize().y > mWindow.getSize().y) {
        mRightPaddle.shape.setPosition(mRightPaddle.shape.getPosition().x, mWindow.getSize().y - mRightPaddle.shape.getSize().y);
    }

    if (mLeftPaddle.score >= 2 || mRightPaddle.score >= 2) {
        mGameOver = true;
    }
}

// Metoda render
void Game::render() {
    mWindow.clear();

    mWindow.draw(mLeftPaddle.shape);
    mWindow.draw(mRightPaddle.shape);
    mWindow.draw(mBall.shape);
    mWindow.draw(player1Text);
    mWindow.draw(player2Text);
    mWindow.draw(mLeftScoreText);
    mWindow.draw(mRightScoreText);

    mWindow.draw(mLine);

    if (mPaused) {
        mWindow.draw(mPausedText);
    }

    if (mGameOver) {
        mWindow.draw(mGameOverText);
    }
    
    mWindow.display();
}