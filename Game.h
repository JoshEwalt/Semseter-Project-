#ifndef GAME_H
#define GAME_H
#include <SFML/Graphics.hpp>
#include "KeyManager.h"
#include "Zombie.h"
#include "PLayer.h"
#include "Image.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "Fire.h"
#include "Texture.h"

using namespace std;
class Game {
public:
    Player player = Player();
    KeyManger keys = KeyManger();
    sf::Texture image;
    sf::Vector2f firePosition;
    sf::Text gameOverText;
    sf::Text restartText;
    sf::Font font;
    sf::Text fireText;
    sf::Text helpText;
    sf::Text exitText;
    Image* playerImage;
    Image* zombieImage;
    Image* heartImage;
    Image* deadFire;
    Texture* fireImages = new Texture[7];
    int fireIndex = 0;
    float timerMax = 0.3;
    float timerValue = 0;
    Fire fire;

    
    float playerSpeed = 600;
    sf::Clock clock = sf::Clock();
    float lastTime = 0;
    float deltaTime = 0;
    const static int maxZombies = 100;
    int playerWidth = 64;
    bool managedDeath = false;

    Zombie zombies[maxZombies];


    int currentZombieCount = 0;
    int currentZmbieMaxCount = 0;

    const int width = 2560;
    const int height = 1440;

    Game() {}

    void start() {
        srand(time(NULL));
        firePosition = sf::Vector2f(width * 0.5 - playerWidth * 0.5, height * 0.5 - playerWidth * 0.5);
        fire.setPosition(firePosition);
        player.setPosition(sf::Vector2f(width * 0.5 - playerWidth * 0.5, height * 0.5 + playerWidth * 0.5));
        image.loadFromFile("./images/image.png");
        //fireImages = {

        fireImages[0] = Texture(new Image("fire1", image, 47, playerWidth));
        fireImages[1] = Texture(new Image("fire2", image, 48, playerWidth));
        fireImages[2] = Texture(new Image("fire3", image, 49, playerWidth));
        fireImages[3] = Texture(new Image("fire4", image, 50, playerWidth));
        fireImages[4] = Texture(new Image("fire5", image, 51, playerWidth));
        fireImages[5] = Texture(new Image("fire6", image, 52, playerWidth));
        fireImages[6] = Texture(new Image("fire7", image, 53, playerWidth));
        //};
        playerImage = new Image ("player" , image, 4990, playerWidth);
        zombieImage = new Image ("zombie" , image, 4999, playerWidth);
        heartImage = new Image ("heart" , image, 1970, playerWidth);
        deadFire = new Image ("deadFire" , image, 46, playerWidth);

        sf::RenderWindow window(sf::VideoMode(width, height), "Fire Protector!", sf::Style::Fullscreen);
        manageUI();
        //addZombie(sf::Vector2f(500, 700));
        while (window.isOpen()) {
            update(window);
            draw(window);
        }

	
	}
    void addZombie(sf::Vector2f postiton) {
        for (int i = 0; i < maxZombies; i++) {
            if (!zombies[i].active) {
                zombies[i].init(postiton);
                currentZombieCount++;
                break;
            }
        }
    }
    void drawZombies(sf::RenderWindow &window){
        for (int i = 0; i < maxZombies; i++) {
            if (zombies[i].active) {
                zombieImage->draw(window, zombies[i].getPosition());
            }
        }
    }
    void spawnZombies() {
        for (int i = 0; i < currentZmbieMaxCount; i++) {
            int x = 0, y = 0;
           
            //left/top
            if (rand() % 2 == 0) {
                //left
                if (rand() % 2 == 0) {
                    x = -playerWidth;
                    y = rand() % (height - playerWidth * 2) - playerWidth;
                }
                //top
                else {
                    y = -playerWidth;
                    x = rand() % (width - playerWidth * 2) - playerWidth;
                }
            }
            //right/bottom
            else {
                //rihgt
                if (rand() % 2 == 0) {
                    x = width + playerWidth;
                    y = rand() % (height - playerWidth * 2) - playerWidth;
                }
                //bottum
                else {
                    y = height + playerWidth;
                    x = rand() % (width - playerWidth * 2) - playerWidth;
                }
            }

            addZombie(sf::Vector2f(x, y));
        }
    }
    void manageUI() {
        font.loadFromFile("./fonts/arial.ttf");
        gameOverText.setFont(font);
        gameOverText.setString("Game Over");
        gameOverText.setCharacterSize(69);
        gameOverText.setFillColor(sf::Color::Red);
        gameOverText.setStyle(sf::Text::Bold);
        gameOverText.setPosition(sf::Vector2f(width * 0.5 - gameOverText.getGlobalBounds().width * 0.5, height * 0.5 - gameOverText.getGlobalBounds().height * 0.5));
        restartText.setFont(font);
        restartText.setString("Press Any Key to Play again");
        restartText.setCharacterSize(25);
        restartText.setFillColor(sf::Color::Blue);
        restartText.setStyle(sf::Text::Bold);
        restartText.setPosition(sf::Vector2f(width * 0.5 - restartText.getGlobalBounds().width * 0.5, height * 0.55 - restartText.getGlobalBounds().height * 0.5));
        fireText.setFont(font);
        fireText.setString("20/20");
        fireText.setCharacterSize(20);
        fireText.setFillColor(sf::Color::White);
        fireText.setStyle(sf::Text::Bold);
        fireText.setPosition(sf::Vector2f(width * 0.5 - fireText.getGlobalBounds().width * 0.5, height * 0.45 - fireText.getGlobalBounds().height * 0.5));
        helpText.setFont(font);
        helpText.setString("Do Not Let The Fire Go Out      OR DIE!!!!!!!!");
        helpText.setCharacterSize(30);
        helpText.setFillColor(sf::Color(255,94,19));
        helpText.setStyle(sf::Text::Bold);
        helpText.setPosition(sf::Vector2f(width * 0.5 - helpText.getGlobalBounds().width * 0.5, height * 0.05 - helpText.getGlobalBounds().height * 0.5));
        exitText.setFont(font);
        exitText.setString("Press  [ alt  =  F4 ] to Exit.");
        exitText.setCharacterSize(30);
        exitText.setFillColor(sf::Color(255,94,18));
        exitText.setStyle(sf::Text::Bold);
        exitText.setPosition(sf::Vector2f(width * 0.5 - exitText.getGlobalBounds().width * 0.5, height * 0.95 - exitText.getGlobalBounds().height * 0.5));

    }
    void manageEvents(sf::RenderWindow &window) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            else if (event.type == sf::Event::KeyPressed) {
                if (player.isDead()) {
                    restartGame();
                }
                keys.manageKey(event.key.code, true);
            }
            else if (event.type == sf::Event::KeyReleased) {
                keys.manageKey(event.key.code, false);
            }
        }
    }
    void update(sf::RenderWindow& window) {

        manageEvents(window);
        if (player.isDead()) {
            return;
        }
        if (currentZombieCount == 0) {
            currentZmbieMaxCount++;
            spawnZombies();
        }
        for (int i = 0; i < maxZombies; i++) {
            if (zombies[i].active) {
                if (getDis(zombies[i].getPosition(), player.getPosition()) < getDis(zombies[i].getPosition(), fire.getPosition())) {
                    if (zombies[i].move(player.getPosition(), deltaTime * 150, deltaTime)) {
                        player.takeDamage(1);
                    }
                }
                else {
                    if (zombies[i].move(fire.getPosition(), deltaTime * 150, deltaTime)) {
                        fire.takeDamage(1);
                    }
                }





            }
        }
        if (fire.getHealth() <= 0) {
            player.takeDamage(69);
        }
        fireText.setString(to_string(fire.getHealth()) + "/20");
        float currentTime = clock.restart().asSeconds();
        deltaTime = currentTime;
        float fps = 1.f / currentTime;
        lastTime = currentTime;

        
        if (keys.space) {
            float distance = 999999;
            int index = 0;
            for (int i = 0; i < maxZombies; i++) {
                if (zombies[i].active) {
                    if (getDis(zombies[i].getPosition(), player.getPosition()) < distance) {
                        index = i;
                        distance = getDis(zombies[i].getPosition(), player.getPosition());
                    }
                }
            }
            if (distance < 64 + 32) {
                zombies[index].takeDamage(5);
                keys.space = false;
                if (!zombies[index].active) {
                    currentZombieCount--;
                }
            }
            //zombies[0].takeDamage(5);
        }


        if (keys.a)
            player.addToX (-playerSpeed * deltaTime);
        if (keys.d)
            player.addToX (playerSpeed * deltaTime);
        if (keys.w)
            player.addToY (-playerSpeed * deltaTime);
        if (keys.s)
            player.addToY (playerSpeed * deltaTime);
        if (player.getPosition().x > width - playerWidth)
            player.setX (width - playerWidth);
        if (player.getPosition().y > height - playerWidth)
            player.setY (height - playerWidth);
        if (player.getPosition().x < 0)
            player.setX  (0);
        if (player.getPosition().y < 0)
            player.setY (0);

        timerValue += deltaTime;
        if (timerValue >= timerMax) {
            timerValue = 0;
            fireIndex++;
            if (fireIndex > 6) {
                fireIndex = 0;
            }
        }

    }
    void draw(sf::RenderWindow &window) {
        window.clear();
        //fireImage->draw(window, firePosition);
        if (fire.getHealth() > 0)
            fireImages[fireIndex].image->draw(window, firePosition);
        else
            deadFire->draw(window, firePosition);
        drawZombies(window);
        
        playerImage->draw(window, player.getPosition());
        int currentX = 0;
        for (int i = 0; i < player.getHealth(); i++) {
            heartImage->draw(window, sf::Vector2f(currentX, 0));
            currentX += playerWidth * 1.2;
        }
        window.draw(fireText);
        window.draw(helpText);
        window.draw(exitText);
        if (player.isDead()) {
            window.draw(gameOverText);
            window.draw(restartText);

        }
        window.display();
    }
    float getDis(sf::Vector2f pos1, sf::Vector2f pos2) {
        return sqrt(pow((pos2.x + playerWidth * 0.5) - (pos1.x + playerWidth * 0.5), 2) + pow((pos2.y + playerWidth * 0.5) - (pos1.y + playerWidth * 0.5), 2));
    }
    void restartGame() {
        currentZombieCount = 0;
        currentZmbieMaxCount = 0;
        player.setHealth();
        fire.setHealth();
        player.setPosition(sf::Vector2f(width * 0.5 - playerWidth * 0.5, height * 0.5 + playerWidth * 0.5));
        for (int i = 0; i < maxZombies; i++) {
            zombies[i].active = false;
        }
    }




};

#endif 
