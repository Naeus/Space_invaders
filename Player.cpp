#include "Player.h"
#include "controller.h"
#include <iostream>
#include "Bullet.h"



Player::Player() :
    x(0.5f * (SCREEN_WIDTH - 16)),
    m_sprite(),
    y_position(SCREEN_HEIGHT - y_offset)

{
    m_texture.loadFromFile("Resources/sprites/Player.png");

    m_sprite.setPosition(SCREEN_WIDTH / 2, y_position);

}

Player::Player(sf::RenderWindow& i_window) :
    x(0.5f * (SCREEN_WIDTH - 16)),
    m_sprite(),
    y_position(SCREEN_HEIGHT - y_offset)

{
    m_texture.loadFromFile("Resources/sprites/Player.png");
    m_collisionBox = sf::FloatRect(m_sprite.getPosition().x, m_sprite.getPosition().y, m_texture.getSize().x, m_texture.getSize().y);
    m_sprite.setPosition(SCREEN_WIDTH / 2, y_position);
    Draw(i_window);
}

void Player::Draw(sf::RenderWindow& i_window) {
    sf::RectangleShape collisionBoxRect(sf::Vector2f(m_collisionBox.width, m_collisionBox.height));
    collisionBoxRect.setPosition(m_collisionBox.left, m_collisionBox.top);
    collisionBoxRect.setFillColor(sf::Color::Transparent);
    collisionBoxRect.setOutlineColor(sf::Color::Green);
    collisionBoxRect.setOutlineThickness(2.f);
    i_window.draw(collisionBoxRect);
    m_sprite.setTexture(m_texture);
    i_window.draw(m_sprite);
}
sf::FloatRect Player::GetCollisionBox() {
    return m_collisionBox;
}
void Player::Update() {

    char step_x = sf::Keyboard::isKeyPressed(sf::Keyboard::Right) - sf::Keyboard::isKeyPressed(sf::Keyboard::Left);

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        x = std::clamp < int >(x + PLAYER_SPEED * step_x, BASE_SIZE, SCREEN_WIDTH - 2 * BASE_SIZE); //we clamp so the player dosent get out of bounds
        m_sprite.setPosition(x, y_position);
    }
    m_collisionBox.left = m_sprite.getPosition().x;
    m_collisionBox.top = m_sprite.getPosition().y;
}

void Player::Shoot(unsigned short player_x, std::vector < Bullet* >& bullets) {

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && m_space_pressed == false && m_canShoot == true) {
        buffer.loadFromFile("Resources/audio/shoot.wav");
        shoot.setBuffer(buffer);
        shoot.play();
        //std::unique_ptr<Bullet> b(new Bullet(player_x + 17, 900, 1));
        Bullet* b = new Bullet(player_x + 17, 900, 1);
        bullets.push_back(b);
        m_canShoot = false;

        m_space_pressed = true;
    }
}