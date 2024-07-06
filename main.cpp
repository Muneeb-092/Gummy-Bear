#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp> 
#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <Windows.h>

using namespace std;
using namespace sf;

// Base class for all characters in the game
class Character {
protected:
    string name;
    int level;
    int points;
    int health;
    int attackStat;
    int defenseStat;
    int speedStat;
public:
    // Constructor
    Character(string n, int l, int h, int a, int d, int s) : name(n), level(l), health(h), attackStat(a), defenseStat(d), speedStat(s) {
        points = 0;
    }

    // Getters and setters
    string getName() { return name; }
    int getLevel() { return level; }
    int getPoints() { return points; }
    int getHealth() { return health; }
    int getAttackStat() { return attackStat; }
    int getDefenseStat() { return defenseStat; }
    int getSpeedStat() { return speedStat; }

    void setName(string n) { name = n; }
    void setLevel(int l) { level = l; }
    void setPoints(int p) { points = p; }
    void setHealth(int h) { health = h; }
    void setAttackStat(int a) { attackStat = a; }
    void setDefenseStat(int d) { defenseStat = d; }
    void setSpeedStat(int s) { speedStat = s; }


    virtual void attack(Character& opponent) = 0;
    
    void takeDamage(int damage) {
        health -= damage;
        if (health < 0) {
            health = 0;
        }
    }

    bool isAlive() {
        return health > 0;
    }
};


class GummyBear : public Character {
public:
    GummyBear(string n, int l, int h, int a, int d, int s) : Character(n, l, h, a, d, s) {}

    
    void attack(Character& opponent) override {
        points = points + 10;
    }

    void nextRound()
    {
        health = 100;
    }
};

// Opponent class, inherits from Character
class Opponent : public Character {
public:
    Opponent(string n, int l, int h, int a, int d, int s) : Character(n, l, h, a, d, s) {}

   
    void attack(Character& opponent) override {
        points = points + 10;
    }

    void nextRound()
    {
        level++;
        attackStat++;
        defenseStat++;
        speedStat++;
        health = 100;
    }
    
};


// Training class
class Training {
public:
    static void trainGummyBear(GummyBear& bear) {
        int attacking, defending, speed, level, points;
        attacking = bear.getAttackStat();
        defending = bear.getDefenseStat();
        speed = bear.getSpeedStat();
        level = bear.getLevel();
        points = bear.getPoints();

        level++;
        attacking++;
        defending++;
        speed++;
        if (points - 50 > 0)
            points -= 50;
        else
            points = 0;

    }
};

// Save and Load functions
void saveGame(Character& character, bool player)
{
    if (player) {
        ofstream outFile("playerState.txt");
        if (outFile.is_open()) {
            // Write character data to file
            outFile << character.getName() << endl;
            outFile << character.getLevel() << endl;
            outFile << character.getPoints() << endl;
            outFile << character.getHealth() << endl;
            outFile << character.getAttackStat() << endl;
            outFile << character.getDefenseStat() << endl;
            outFile << character.getSpeedStat() << endl;
            outFile.close();
            cout << "Game saved successfully." << endl;
        }
        else {
            cout << "Unable to open file for saving." << endl;
        }
    }
    else
    {
        ofstream outFile("enemyState.txt");
        if (outFile.is_open()) {
            // Write character data to file
            outFile << character.getName() << endl;
            outFile << character.getLevel() << endl;
            outFile << character.getPoints() << endl;
            outFile << character.getHealth() << endl;
            outFile << character.getAttackStat() << endl;
            outFile << character.getDefenseStat() << endl;
            outFile << character.getSpeedStat() << endl;
            outFile.close();
            cout << "Game saved successfully." << endl;
        }
        else {
            cout << "Unable to open file for saving." << endl;
        }
    }
}

void loadGame(Character& character, bool player)  // 1 for player and 0 for enemy
{
    if (player) {
        ifstream inFile("playerState.txt");

        if (inFile.is_open()) {
            // Read character data from file
            string name;
            int level, points, health, attackStat, defenseStat, speedStat;
            inFile >> name >> level >> points >> health >> attackStat >> defenseStat >> speedStat;
            character.setName(name);
            character.setLevel(level);
            character.setPoints(points);
            character.setHealth(health);
            character.setAttackStat(attackStat);
            character.setDefenseStat(defenseStat);
            character.setSpeedStat(speedStat);
            cout << "Game loaded successfully." << endl;
        }
        else {
            cout << "Unable to open file for loading." << endl;
        }
    }
    else
    {
        ifstream inFile("enemyState.txt");

        if (inFile.is_open()) {
            // Read character data from file
            string name;
            int level, points, health, attackStat, defenseStat, speedStat;
            inFile >> name >> level >> points >> health >> attackStat >> defenseStat >> speedStat;
            character.setName(name);
            character.setLevel(level);
            character.setPoints(points);
            character.setHealth(health);
            character.setAttackStat(attackStat);
            character.setDefenseStat(defenseStat);
            character.setSpeedStat(speedStat);
            cout << "Game loaded successfully." << endl;
        }
        else {
            cout << "Unable to open file for loading." << endl;
        }
    }
}

class Ball {
private:
    Sprite ballSprite;
    float speed;
    bool active;

public:
    Ball(Texture& texture) : speed(6.0f), active(false) {
        ballSprite.setTexture(texture);
        ballSprite.setScale(Vector2f(0.2f, 0.2f)); // Scale the ball sprite
    }

    void launch(Vector2f position) {
        ballSprite.setPosition(position);
        active = true;
    }

    void update(bool con) {
        if (active && con) {
            ballSprite.move(speed, 0.0f);
        }
        else if (active && con == 0) {
            ballSprite.move(-speed, 0.0f);
        }

    }

    void draw(RenderWindow& window) {
        if (active) {
            window.draw(ballSprite);
        }
    }

    Sprite& getSprite() { return ballSprite; }

    bool isActive() const { return active; }

    void deactivate() { active = false; }

   
};


float windowWidth = VideoMode::getDesktopMode().width;
float windowHeight = VideoMode::getDesktopMode().height;

int main() {

    bool Gamestate;
    // Create gummy bear and opponent
    GummyBear player("Player", 1, 100, 5, 5, 5);
    Opponent enemy("Enemy", 1, 100, 5, 5, 5);

    // Create SFML window
    RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "Gummy Bear Fighting Game");
    window.setFramerateLimit(80);


    // Loading Intro BG --------------------------------------------------
    Texture intoTexture;

    if (!intoTexture.loadFromFile("intro.png")) {
        std::cerr << "Failed to load background image\n";
        return 1;
    }

    Sprite introSprite(intoTexture);

    introSprite.setScale(
        static_cast<float>(windowWidth) / introSprite.getLocalBounds().width,
        static_cast<float>(windowHeight) / introSprite.getLocalBounds().height
    );

    window.clear();
    window.draw(introSprite);
    window.display();
    Sleep(1000);


    // Loading Start menu BG ----------------------------------------------------------------------
    Texture startMenuTexture;

    if (!startMenuTexture.loadFromFile("menu.png")) {
        std::cerr << "Failed to load background image\n";
        return 1;
    }

    Sprite startMenuSprite(startMenuTexture);

    startMenuSprite.setScale(
        static_cast<float>(windowWidth) / startMenuSprite.getLocalBounds().width,
        static_cast<float>(windowHeight) / startMenuSprite.getLocalBounds().height
    );


    Font font;
    if (!font.loadFromFile("font1.ttf")) {
        std::cerr << "Failed to load font\n";
        return 1;
    }

    Text New_Game;
    New_Game.setFont(font);
    New_Game.setCharacterSize(150);
    New_Game.setFillColor(Color::Black);
    New_Game.setPosition(1900, 640);
    New_Game.setString("1. New Game ");

    Text Load_Game;
    Load_Game.setFont(font);
    Load_Game.setCharacterSize(150);
    Load_Game.setFillColor(Color::Black);
    Load_Game.setPosition(1890, 820);
    Load_Game.setString("2. Load Game ");

    Text train;
    train.setFont(font);
    train.setCharacterSize(150);
    train.setFillColor(Color::Black);
    train.setPosition(1890, 820);
    train.setString("2. Train ");

    Text playGame;
    playGame.setFont(font);
    playGame.setCharacterSize(150);
    playGame.setFillColor(Color::Black);
    playGame.setPosition(1890, 640);
    playGame.setString("1. Play Game ");



    // Loading Game BG -------------------------------------------------
    Texture backgroundTexture;

    if (!backgroundTexture.loadFromFile("Background.jpg")) {
        std::cerr << "Failed to load background image\n";
        return 1;
    }

    Sprite backgroundSprite(backgroundTexture);

    backgroundSprite.setScale(
        static_cast<float>(windowWidth) / backgroundSprite.getLocalBounds().width,
        static_cast<float>(windowHeight) / backgroundSprite.getLocalBounds().height
    );

    Texture trainTexture;

    if (!trainTexture.loadFromFile("training.png")) {
        std::cerr << "Failed to load background image\n";
        return 1;
    }

    Sprite trainSprite(trainTexture);

    trainSprite.setScale(
        static_cast<float>(windowWidth) / trainSprite.getLocalBounds().width,
        static_cast<float>(windowHeight) / trainSprite.getLocalBounds().height
    );




    // Load gummy bear texture
    sf::Texture gummyTexture;
    if (!gummyTexture.loadFromFile("gummyBear.png")) {
        cout << "Failed to load gummy bear texture!" << endl;
        return -1;
    }

    // Load enemy gummy bear texture
    sf::Texture enemyTexture;
    if (!enemyTexture.loadFromFile("enemyBear.png")) {
        cout << "Failed to load enemy gummy bear texture!" << endl;
        return -1;
    }

    // Load ball texture
    sf::Texture ballTexture;
    if (!ballTexture.loadFromFile("Ball.png")) {
        cout << "Failed to load ball texture!" << endl;
        return -1;
    }

    // Create gummy bear sprite
    Sprite gummySprite(gummyTexture);
    gummySprite.setScale(sf::Vector2f(window.getSize().x / 800.0f, window.getSize().y / 600.0f));


    // Create enemy gummy bear sprite
    Sprite enemySprite(enemyTexture);
    enemySprite.setScale(sf::Vector2f(window.getSize().x / 800.0f, window.getSize().y / 600.0f));


    // Create Ball
    Ball ball1(ballTexture);
    Ball ball2(ballTexture);
    Ball ball3(ballTexture);
    Ball eball(ballTexture);


    // timer for enemy attack
    Clock clock;
    Clock clock1;
    float timer1 = 0.0f;
    float timer2 = 0.0f;



    float Attack_interval = 0;
    float Jump_interval = 0;

    if ((10 / enemy.getAttackStat()) > 1.5)
        Attack_interval = 10 / enemy.getAttackStat();
    else
        Attack_interval = 1.5;

    if ((10 / enemy.getDefenseStat()) > 1.5)
        Jump_interval = 10 / enemy.getDefenseStat();
    else
        Jump_interval = 1.5;

    float jumpSpeed = 0;
    if (player.getDefenseStat() * 3 < 25)
        jumpSpeed = player.getDefenseStat() * 3;
    else
        jumpSpeed = 25;

    float gravity = 0.3f; // Gravity for gummy bear fall
    float jumpVelocity = 2.0f; // Initial jump velocity


    float jSpeed = 0;
    if (enemy.getDefenseStat() * 3 < 30)
        jSpeed = enemy.getDefenseStat() * 5;
    else
        jSpeed = 30;
    float g = 0.5f; // Gravity for enemy bear fall
    float jVelocity = 2.0f; // Initial jump velocity

    int lenght = 0;


    Text trained;
    trained.setFont(font);
    trained.setCharacterSize(100);
    trained.setFillColor(Color::White);

    Text trainedError;
    trainedError.setFont(font);
    trainedError.setCharacterSize(100);
    trainedError.setFillColor(Color::White);
    



    Text Name;
    Name.setFont(font);
    Name.setCharacterSize(60);
    Name.setFillColor(Color::Black);
    Name.setPosition(60, 100);

    Text level;
    level.setFont(font);
    level.setCharacterSize(60);
    level.setFillColor(Color::Black);
    level.setPosition(60, 170);

    Text Points;
    Points.setFont(font);
    Points.setCharacterSize(60);
    Points.setFillColor(Color::Black);
    Points.setPosition(60, 240);

    Text Ename;
    Ename.setFont(font);
    Ename.setCharacterSize(60);
    Ename.setFillColor(Color::Black);
    Ename.setPosition(1850, 100);

    Text Elevel;
    Elevel.setFont(font);
    Elevel.setCharacterSize(60);
    Elevel.setFillColor(Color::Black);
    Elevel.setPosition(1850, 170);

    Text Epoints;
    Epoints.setFont(font);
    Epoints.setCharacterSize(60);
    Epoints.setFillColor(Color::Black);
    Epoints.setPosition(1850, 240);


    Text ending_note;
    ending_note.setFont(font);
    ending_note.setCharacterSize(100);
    ending_note.setFillColor(Color::Blue);
    ending_note.setPosition(windowWidth / 2 - 600, windowHeight / 2 - 300);

    Text gameloadMsg;
    gameloadMsg.setFont(font);
    gameloadMsg.setCharacterSize(50);
    gameloadMsg.setFillColor(Color::Black);
    gameloadMsg.setPosition(2000, 1500);
    gameloadMsg.setString("Game Loaded Successfully...!");

    SoundBuffer buffer;
    buffer.loadFromFile("sound.mp3");
    Sound sound;
    sound.setBuffer(buffer);

    SoundBuffer buffer1;
    buffer1.loadFromFile("hit.mp3");
    Sound sound1;
    sound1.setBuffer(buffer1);

    SoundBuffer buffer2;
    buffer2.loadFromFile("start.wav");
    Sound sound2;
    sound2.setBuffer(buffer2);

    SoundBuffer buffer3;
    buffer3.loadFromFile("training.mp3");
    Sound sound3;
    sound3.setBuffer(buffer3);

    int playerPos = 700;
    int enemyPos = 800;

    gummySprite.setPosition(150, playerPos); // Position the gummy bear sprite
    enemySprite.setPosition(2250, enemyPos); // Position the gummy bear sprite
    bool flag = 0;
    int i = 1;


    // Game loop
    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed)
                window.close();
            else if (Keyboard::isKeyPressed(Keyboard::Key::Escape))
                window.close();
        }

        if (i == 1)  // intro page 1 
        {
            bool con3 = 0;
            if (Keyboard::isKeyPressed(Keyboard::Key::Num1)) // new game
            {
                i++;
            }
            else if (Keyboard::isKeyPressed(Keyboard::Key::Num2)) // Load game
            {
                loadGame(player, 1);
                loadGame(enemy, 0);
                con3 = 1;
                i++;
            }

            window.clear();
            window.draw(startMenuSprite);
            window.draw(New_Game);
            window.draw(Load_Game);
            if (con3) {
                window.draw(gameloadMsg);
                window.display();
                Sleep(500);
            }
            else {
                window.display();
            }
        }
        if (i == 2)   // intro page 2
        {
            bool con4 = 1;
            if (con4)
            {
                Sleep(500); con4 = 0;
            }

            if (Keyboard::isKeyPressed(Keyboard::Key::Num1)) // play game
            {
                i++;
                flag = 1;
            }
            else if (Keyboard::isKeyPressed(Keyboard::Key::Num2)) // training
            {


                if (player.getPoints() < 50)
                {
                    trained.setString("You can't train");
                    trained.setPosition(windowWidth / 2 + 110, windowHeight / 2 + 20);

                }
                else
                {
                    Training camp;
                    camp.trainGummyBear(player);
                    sound1.stop();
                    sound2.stop();
                    sound3.play();

                    for (int j = 1; j <= 4; j++) {
                        if (j == 1)
                            trained.setString("> Attacking Skills");
                        else if (j == 2)
                            trained.setString("> Defencive Skills");
                        else if (j == 3)
                            trained.setString("> Speed");
                        else if (j == 4)
                            trained.setString("> Energy");
                        trained.setPosition(windowWidth / 2 + 120, windowHeight / 2 + 20);
                        window.clear();
                        window.draw(trainSprite);
                        window.draw(trained);
                        window.display();
                        Sleep(1200);
                    }

                    trained.setString("Done...");
                }
                window.clear();
                window.draw(trainSprite);
                window.draw(trained);
                window.display();
                Sleep(1000);
                sound3.stop();

            }

            window.clear();
            window.draw(startMenuSprite);
            window.draw(playGame);
            window.draw(train);
            window.display();


        
        }

        while (flag)   // main game loop
        {
            if (i == 3)
            {
                sound2.play();
                player.setHealth(100);
                enemy.setHealth(100);
                gummySprite.setPosition(150, playerPos);
                enemySprite.setPosition(2250, enemyPos);
                i++;
            }


            while (window.pollEvent(event)) {
                if (event.type == Event::Closed)
                    window.close();
                else if (Keyboard::isKeyPressed(Keyboard::Key::Escape))
                    window.close();
                if (event.type == sf::Event::KeyPressed) {
                    if (event.key.code == sf::Keyboard::Space) {
                        // Jump when space is pressed
                        jumpVelocity = -jumpSpeed;
                    }
                    if (event.key.code == sf::Keyboard::F) {
                        // Attack when F is pressed
                        // Launch a new ball from the player bear
                        if (!ball1.isActive()) {
                            Vector2f ballPosition = gummySprite.getPosition();
                            ballPosition.x += gummySprite.getGlobalBounds().width;
                            ballPosition.y += gummySprite.getGlobalBounds().height / 2;
                            sound.play();
                            ball1.launch(ballPosition);
                        }
                        else if (!ball2.isActive() && player.getLevel() >= 3) {
                            Vector2f ballPosition = gummySprite.getPosition();
                            ballPosition.x += gummySprite.getGlobalBounds().width;
                            ballPosition.y += gummySprite.getGlobalBounds().height / 2;
                            ball2.launch(ballPosition);
                            sound.play();
                        }
                        else if (!ball3.isActive() && player.getLevel() >= 5) {
                            Vector2f ballPosition = gummySprite.getPosition();
                            ballPosition.x += gummySprite.getGlobalBounds().width;
                            ballPosition.y += gummySprite.getGlobalBounds().height / 2;
                            ball3.launch(ballPosition);
                            sound.play();
                        }

                    }
                }
            }


            timer1 += clock.restart().asSeconds();
            timer2 += clock1.restart().asSeconds();

            //for attacking of enemy
            if (timer1 >= Attack_interval) {

                if (!eball.isActive()) {
                    Vector2f ballPosition = enemySprite.getPosition();
                    sound.play();
                    ballPosition.y += enemySprite.getGlobalBounds().height / 2;
                    eball.launch(ballPosition);
                }
                timer1 = 0.0f; // Reset the timer
            }


            // for jumping of enemy
            if (timer2 >= Jump_interval) {
                jVelocity = -jSpeed;
                timer2 = 0.0f; // Reset the timer
            }


            // Apply gravity to gummy bear
            jumpVelocity += gravity;
            gummySprite.move(0.0f, jumpVelocity);

            jVelocity += g;
            enemySprite.move(0.0f, jVelocity);

            // Check if gummy bear is on the ground
            if (gummySprite.getPosition().y >= playerPos) {
                gummySprite.setPosition(gummySprite.getPosition().x, playerPos);
                jumpVelocity = 0.0f;
            }

            // Check if enemy bear is on the ground
            if (enemySprite.getPosition().y >= enemyPos) {
                enemySprite.setPosition(enemySprite.getPosition().x, enemyPos);
                jVelocity = 0.0f;
            }
            // Update the ball
            ball1.update(1);
            ball2.update(1);
            ball3.update(1);
            eball.update(0);

            // Check for collisions between the ball and the enemy
            if (ball1.isActive() && ball1.getSprite().getGlobalBounds().intersects(enemySprite.getGlobalBounds())) {
                enemy.takeDamage(player.getAttackStat());
                player.attack(enemy);
                ball1.deactivate();
                sound1.play();
            }
            else if (ball1.isActive() && (ball1.getSprite().getGlobalBounds().getPosition().x >= (windowWidth - 50)))
            {
                ball1.deactivate();
            }

            if (ball2.isActive() && ball2.getSprite().getGlobalBounds().intersects(enemySprite.getGlobalBounds())) {
                enemy.takeDamage(player.getAttackStat());
                player.attack(enemy);
                ball2.deactivate();
                sound1.play();
            }
            else if (ball2.isActive() && (ball2.getSprite().getGlobalBounds().getPosition().x >= (windowWidth - 50)))
            {
                ball2.deactivate();
            }

            if (ball3.isActive() && ball3.getSprite().getGlobalBounds().intersects(enemySprite.getGlobalBounds())) {
                enemy.takeDamage(player.getAttackStat());
                player.attack(enemy);
                ball3.deactivate();
                sound1.play();
            }
            else if (ball3.isActive() && (ball3.getSprite().getGlobalBounds().getPosition().x >= (windowWidth - 50)))
            {
                ball3.deactivate();
            }

            if (eball.isActive() && eball.getSprite().getGlobalBounds().intersects(gummySprite.getGlobalBounds())) {
                player.takeDamage(enemy.getAttackStat());
                enemy.attack(player);
                eball.deactivate();
                sound1.play();
            }
            else if ((eball.getSprite().getGlobalBounds().getPosition().x <= 10))
            {
                eball.deactivate();
            }

            int templevel;
            if (!enemy.isAlive())
            {
                ending_note.setString(" YOU WON THE GAME...!");
                templevel = player.getLevel();
                player.setLevel(++templevel);
                flag = 0;
            }
            else if (!player.isAlive())
            {
                ending_note.setString(" YOU LOSE THE GAME...!");
                templevel = enemy.getLevel();
                enemy.setLevel(++templevel);
                flag = 0;
            }

            RectangleShape playerHealthBarBG(Vector2f(1000, 50));
            playerHealthBarBG.setFillColor(Color::Black);
            playerHealthBarBG.setPosition(60, 50);

            RectangleShape playerHealthBar(Vector2f(player.getHealth() * 10, 50));
            playerHealthBar.setFillColor(Color::Green);
            playerHealthBar.setPosition(60, 50);



            RectangleShape enemyHealthBarBG(Vector2f(1000, 50));
            enemyHealthBarBG.setFillColor(Color::Black);
            enemyHealthBarBG.setPosition(1850, 50);

            RectangleShape enemyHealthBar(Vector2f(enemy.getHealth() * 10, 50));
            enemyHealthBar.setFillColor(Color::Red);
            enemyHealthBar.setPosition(1850, 50);

            Name.setString("NAME: " + player.getName());
            level.setString("LEVEL: " + to_string(player.getLevel()));
            Points.setString("POINTS: " + to_string(player.getPoints()));

            Ename.setString("NAME: " + enemy.getName());
            Elevel.setString("LEVEL: " + to_string(enemy.getLevel()));
            Epoints.setString("POINTS: " + to_string(enemy.getPoints()));




            window.clear();

            // Draw gummy bear sprites
            window.draw(backgroundSprite);

            window.draw(playerHealthBarBG);
            window.draw(enemyHealthBarBG);
            window.draw(playerHealthBar);
            window.draw(enemyHealthBar);

            window.draw(Name);
            window.draw(level);
            window.draw(Points);

            window.draw(Ename);
            window.draw(Elevel);
            window.draw(Epoints);
            if (flag == 0)
                window.draw(ending_note);

            window.draw(gummySprite);
            window.draw(enemySprite);

            ball1.draw(window);
            ball2.draw(window);
            ball3.draw(window);

            eball.draw(window);

            window.display();
            if (flag == 0)
                Sleep(2500);
        }
        
        if (i == 4)   // ending menu page 
        {
            Texture MenuTexture;
            if (!MenuTexture.loadFromFile("menu.png")) {
                std::cerr << "Failed to load background image\n";
                return 1;
            }

            Sprite menuSprite(MenuTexture);
            menuSprite.setScale(
                static_cast<float>(windowWidth) / menuSprite.getLocalBounds().width,
                static_cast<float>(windowHeight) / menuSprite.getLocalBounds().height
            );


            Text option1;
            option1.setFont(font);
            option1.setCharacterSize(150);
            option1.setFillColor(Color::Black);
            option1.setPosition(1900, 640);
            option1.setString("1. Play Again");

            Text option2;
            option2.setFont(font);
            option2.setCharacterSize(150);
            option2.setFillColor(Color::Black);
            option2.setPosition(1895, 820);
            option2.setString("2. Save Game");

            Text gameSaveMsg;
            gameSaveMsg.setFont(font);
            gameSaveMsg.setCharacterSize(50);
            gameSaveMsg.setFillColor(Color::Black);
            gameSaveMsg.setPosition(2000, 1500);
            gameSaveMsg.setString("Game Saved Successfully...!");

            bool con = 0;

            if (Keyboard::isKeyPressed(Keyboard::Key::Num1))
            {
                // reseting all the conditions for play again
                flag = 1;
                player.nextRound();
                enemy.nextRound();
                gummySprite.setPosition(150, playerPos); // Position the gummy bear sprite
                enemySprite.setPosition(2250, enemyPos); // Position the gummy bear sprite
                if (ball1.isActive())
                    ball1.deactivate();
                if (ball2.isActive())
                    ball2.deactivate();
                if (ball3.isActive())
                    ball3.deactivate();
                if (eball.isActive())
                    eball.deactivate();
            }
            else if (Keyboard::isKeyPressed(Keyboard::Key::Num2))
            {
                saveGame(player, 1);
                saveGame(enemy, 0);
                con = 1;
            }


            window.clear();
            window.draw(menuSprite);
            window.draw(option1);
            window.draw(option2);

            if (con) {
                window.draw(gameSaveMsg);
                window.display();
                Sleep(500);
                con = 0;
            }
            else
            {
                window.display();
            }
        }
    }

    return 0;
}
