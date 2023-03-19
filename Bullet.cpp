#include "Bullet.h"
#include "controller.h"

#include <iostream>


Bullet::Bullet(unsigned short position_x, unsigned short position_y, int direction) :

    bullet_sprite(),
    m_direction(direction)

{
    if (m_texture.loadFromFile("Resources/sprites/Bullet.png")) {
        bullet_sprite.setPosition(position_x, position_y);
    }
    bullet_sprite.setTexture(m_texture);
    m_collisionBox = sf::FloatRect(bullet_sprite.getPosition().x, bullet_sprite.getPosition().y, m_texture.getSize().x, m_texture.getSize().y);

}
bool Bullet::CheckCollision(sf::FloatRect otherBox) {
    return m_collisionBox.intersects(otherBox);
}

void Bullet::Draw(sf::RenderWindow& i_window) {
    sf::RectangleShape collisionBoxRect(sf::Vector2f(m_collisionBox.width, m_collisionBox.height));
    collisionBoxRect.setPosition(m_collisionBox.left, m_collisionBox.top);
    collisionBoxRect.setFillColor(sf::Color::Transparent);
    collisionBoxRect.setOutlineColor(sf::Color::Red);
    collisionBoxRect.setOutlineThickness(2.f);
    i_window.draw(collisionBoxRect);
    i_window.draw(bullet_sprite);
}

void Bullet::Update() {
    bullet_sprite.move(0, -m_bullet_speed * m_direction);
    m_collisionBox.left = bullet_sprite.getPosition().x;
    m_collisionBox.top = bullet_sprite.getPosition().y;

}

sf::FloatRect Bullet::GetCollisionBox() {
    return m_collisionBox;
}
