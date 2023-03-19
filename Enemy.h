#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Bullet.h"
class Enemy
{

private:

	
	sf::Texture m_texture;
	sf::Sprite m_sprite;
	sf::Clock m_movementTimer;
	sf::FloatRect m_collisionBox;
	unsigned short x;
	unsigned short y;
	int original_x;
	int original_y;
	int created = 0;
	int difficulty = 10;
	int step = 0;
	
	sf::IntRect area;
	
	bool IsDead = false;
	bool IsChanging = false;
	bool HasLowered = false;
	int m_stepSize = 20;
	int m_direction = 1;
	float x_pos = m_sprite.getPosition().x;
	float y_pos = m_sprite.getPosition().y;
	float willShoot;
	float TimeAction = 1;





public:
	Enemy();
	void setDead(bool dead)
	{
		IsDead = dead;
	}

	void setOriginal_Y(int y)
	{
		original_y = y;
	}
	void setOriginal_X(int x)
	{
		original_x = x;
	}

	int getOriginal_Y()
	{
		return original_y;
	}

	int getOriginal_X()
	{
		return original_x;
	}


	void setChanging(bool change)
	{
		IsDead = change;
	}
	
	unsigned short get_y()
	{
		return m_sprite.getPosition().y;
	}
	float getSpritePosition()
	{
		return m_sprite.getPosition().x;
	}

	float getSpriteYPosition()
	{
		return m_sprite.getPosition().y;
	}
	float getGlobalBounds()
	{
		return m_sprite.getGlobalBounds().width;
	}
	void ChangeDirection(float deltaTime);
	void OnDeath();
	Enemy::Enemy(sf::RenderWindow& i_window);
	void Update(float deltaTime);
	sf::FloatRect Enemy::GetCollisionBox();
	void Enemy::setPosition(float x, float y);
	bool Enemy::CheckCollision(sf::FloatRect otherBox);
	void Draw(sf::RenderWindow& game_window);
	void Enemy::Shoot(unsigned short enemy_x, unsigned short enemy_y, std::vector<Bullet*>& bullets);
};