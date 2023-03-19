#include <SFML/Graphics.hpp>

#include "controller.h"

#include "Player.h"

#include "Bullet.h"

#include "Enemy.h"

#include "UI.h"

#include <iostream>

#include <filesystem>

#include <algorithm>


void createEnemies()

{

}
int main()

{

    srand(time(NULL));
    sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Invaders from space!", sf::Style::Close);
    sf::Clock deltaClock;
    sf::Time dt = deltaClock.restart();
    sf::Time elapsed;
    Player player(window);
    UI ui(window);

    std::vector < Bullet* > bullets;
    std::vector < Enemy > enemies;
    const int numRows = 5;
    const int numCols = 11;
    int AmountEnemy;
    const int spacing = 50;
    const int startX = 750;
    const int startY = 50;
    float timeElapsed = 0.0f;
    bool movable = false;
    bool IsPlayerDead = false;
    int score = 0;

    window.setFramerateLimit(60);
    AmountEnemy = numCols * numRows;
    for (int row = 0; row < numRows; row++) {
        for (int col = 0; col < numCols; col++) {
            Enemy enemy(window);
            enemy.setOriginal_X(startX + col * spacing);
            enemy.setOriginal_Y(startY + row * spacing);
            enemy.setPosition(startX + col * spacing, startY + row * spacing);
            enemies.push_back(enemy);
        }
    }

   

    while (window.isOpen())

    {

        sf::Event event;

        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Space)
                player.set_pressed(false);

        }

        for (auto it_enemy = enemies.begin(); it_enemy != enemies.end();) {
            timeElapsed += deltaClock.getElapsedTime().asSeconds();
            dt;
            if ((*it_enemy).getSpriteYPosition() > 900) {

                IsPlayerDead = true;
            }
            if (timeElapsed >= 100.f && IsPlayerDead == false) {
                it_enemy->Shoot(it_enemy->getSpritePosition(), it_enemy->get_y(), bullets);

            }

            bool enemy_destroyed = false;
            for (auto it_bullet = bullets.begin(); it_bullet != bullets.end();) {
                // std::cout << (*it_bullet)->getSpritePosition();
                if ((*it_bullet)->CheckCollision((*it_enemy).GetCollisionBox()) && (*it_bullet)->getDirection() == 1) {
                    it_bullet = bullets.erase(it_bullet);
                    delete *it_bullet;
                    player.set_canShoot(true);
                    score += 100;
                    enemy_destroyed = true;
                    // std::cout << "bullet erased";

                }
                else if ((*it_bullet)->CheckCollision(player.GetCollisionBox()) && IsPlayerDead == false) {
                    IsPlayerDead = true;

                }
                else if ((*it_bullet)->getSpritePosition() < 0) {
                    it_bullet = bullets.erase(it_bullet);
                    //std::cout << "bullet erased";

                    player.set_canShoot(true);
                }
                else if ((*it_bullet)->getSpritePosition() > 1000) {
                    it_bullet = bullets.erase(it_bullet);

                }
                else {
                    it_bullet++;
                }
            }

            if (enemy_destroyed) {
                it_enemy->setDead(true);
                it_enemy->OnDeath();

                AmountEnemy--;
            }
            else {
                it_enemy++;
            }
        }

        if (AmountEnemy == 0) {
            AmountEnemy = numCols * numRows;
            for (auto& enemy : enemies) {
                enemy.setDead(false);
                enemy.setPosition(enemy.getOriginal_X(), enemy.getOriginal_Y());

                movable = false;
            }

        }

        ui.setScore(score);
        std::cout << IsPlayerDead;
        if (IsPlayerDead == false) {
            player.Update();
            player.Shoot(player.get_x(), bullets);
            window.clear();
            player.Draw(window);
        }
        if (IsPlayerDead == true) {
            window.clear();
            ui.GameOver(window);
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::R) && IsPlayerDead == true)
            for (auto& enemy : enemies) {
                IsPlayerDead = false;
                enemy.setDead(false);
                enemy.setPosition(enemy.getOriginal_X(), enemy.getOriginal_Y());

                movable = false;
                score = 0;

            }
        timeElapsed += deltaClock.getElapsedTime().asSeconds();
        dt;

        if (timeElapsed >= 300.f) {
            movable = true;

        }
        for (auto& enemy : enemies) {

            if (movable == true && IsPlayerDead == false) {

                if (enemy.getSpritePosition() <= 0 || enemy.getSpritePosition() + enemy.getGlobalBounds() >= SCREEN_WIDTH) //tenemos que hacer que el enemigo baje 13032023
                {
                    for (auto& enemy : enemies) {
                        enemy.ChangeDirection(elapsed.asSeconds());
                    }
                }

                enemy.Update(elapsed.asSeconds());

            }
            enemy.Draw(window);
        }
        ui.draw();

        for (auto& bullet : bullets) {

            bullet->Update();
            bullet->Draw(window);

        }

        //bullet.Draw(window);

        window.display();

    }

    return 0;
}