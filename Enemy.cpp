#include "Enemy.h"
#include "controller.h"
#include <iostream>
#include <cstdlib>
#include "Bullet.h"
Enemy::Enemy()

{
    m_texture.loadFromFile("Resources/sprites/Enemy.png");

    m_sprite.setPosition(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);

}

Enemy::Enemy(sf::RenderWindow& i_window) :
    area(0, 0, 32, 23)
    //m_sprite(m_texture,area)
{

    m_texture.loadFromFile("Resources/sprites/Enemy2.png");

    m_collisionBox = sf::FloatRect(m_sprite.getPosition().x, m_sprite.getPosition().y, m_texture.getSize().x, m_texture.getSize().y);
    m_movementTimer.restart();

    //Draw(i_window);

}

void Enemy::Draw(sf::RenderWindow& i_window) {
    if (IsDead == false) {
        sf::RectangleShape collisionBoxRect(sf::Vector2f(m_collisionBox.width / 2, m_collisionBox.height));
        collisionBoxRect.setPosition(m_collisionBox.left, m_collisionBox.top);
        collisionBoxRect.setFillColor(sf::Color::Transparent);
        collisionBoxRect.setOutlineColor(sf::Color::Blue);
        collisionBoxRect.setOutlineThickness(2.f);
        i_window.draw(collisionBoxRect);
        m_sprite.setTexture(m_texture, false);
        i_window.draw(m_sprite);
        m_sprite.setTextureRect(area);
    }

}

sf::FloatRect Enemy::GetCollisionBox() {

    return m_collisionBox;

}
void Enemy::setPosition(float x, float y) {
    if (IsDead == false) {
        m_sprite.setPosition(x, y);
        m_collisionBox.left = x;
        m_collisionBox.top = y;
    }
    else {
        m_collisionBox.left = 9998;
        m_collisionBox.top = 9999;

    }
}
bool Enemy::CheckCollision(sf::FloatRect otherBox) {
    if (IsDead == false) {
        return m_collisionBox.intersects(otherBox);
    }
}
void Enemy::Update(float deltaTime) {

    if (IsDead == false) {
        bool Animation = 0;

        if (m_movementTimer.getElapsedTime().asSeconds() >= TimeAction && IsChanging == false) {

            if (difficulty == 0) {
                difficulty = 10;
                if (TimeAction > 0.4) {
                    TimeAction -= 0.2;
                }
            }
            else {
                difficulty--;
            }

            x_pos = m_sprite.getPosition().x;
            y_pos = m_sprite.getPosition().y;
            // Move the enemy
            m_sprite.setPosition(x_pos + m_stepSize * m_direction, y_pos + 0);

            m_collisionBox.left = x_pos + m_stepSize * m_direction;
            m_collisionBox.top = y_pos;
            if (area.left == 32) {

                area.left = 0;

            }
            else {
                area.left += 32;

            }
            //std::cout << area.left<< " "<< area.top;

            // Restart the movement timer
            m_sprite.setTextureRect(area);
            m_movementTimer.restart();
        }
    }
    else {
        m_collisionBox.left = 9999;
        m_collisionBox.top = 9999;
    }
}
void Enemy::ChangeDirection(float deltaTime) {

    // Move the enemy down
    m_sprite.setPosition(x_pos, y_pos + m_stepSize + 40);

    // Update the collision box
    m_collisionBox.left = x_pos;
    m_collisionBox.top = y_pos + m_stepSize + 40;

    // Change direction
    m_direction = -m_direction;
    IsChanging = false;
    HasLowered = true;
    // Restart the movement timer
    m_movementTimer.restart();
}

void Enemy::Shoot(unsigned short enemy_x, unsigned short enemy_y, std::vector < Bullet* >& bullets) {
    if (IsDead == false) {
        willShoot = rand() % 1000;

        if (willShoot < 0.0001) {
            Bullet* b = new Bullet(enemy_x, enemy_y, -1);

            created++;
            //std::cout << creada << "balas creadas" << std::endl;
            bullets.push_back(b);
        }
    }
}

void Enemy::OnDeath() {
    m_collisionBox.left = 9998;
    m_collisionBox.top = 9999;
}

