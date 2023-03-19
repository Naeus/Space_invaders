#pragma once
#include <SFML/Graphics.hpp>
class Bullet {

private:

    //bool dead;
    unsigned short x = 0;
    unsigned short y = 0;
    int m_bullet_speed = 8;
    int m_direction = 1;
    sf::Sprite bullet_sprite;
    sf::Texture m_texture;
    sf::Vector2f m_velocity;
    sf::FloatRect m_collisionBox;

    bool printed = false;
public:

    Bullet(unsigned short position_x, unsigned short position_y, int direction);
    ~Bullet() = default;

    sf::FloatRect Bullet::GetCollisionBox();
    bool Bullet::CheckCollision(sf::FloatRect otherBox);
    float getSpritePosition() {
        return bullet_sprite.getPosition().y;
    }
    int getDirection() {
        return m_direction;
    }

    void Draw(sf::RenderWindow& game_window);

    void Update();

};