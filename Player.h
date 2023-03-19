#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Bullet.h"

class Player
{

private:
	

	//bool dead;
	unsigned short x;
	int y_offset = 150;
	float y_position;
	sf::Sprite m_sprite;
	sf::Texture m_texture;
	sf::SoundBuffer buffer;
	sf::Sound shoot;
	sf::Vector2f m_velocity;
	sf::FloatRect m_collisionBox;
	bool m_space_pressed = false;
	bool m_canShoot = true;
public:
	Player();
	Player::Player(sf::RenderWindow& i_window);
	unsigned short get_x()
	{
		return x;
	}
	void Draw(sf::RenderWindow& game_window);
	bool get_pressed() {
		return m_space_pressed;
	}
	void set_pressed(bool s)
	{
		m_space_pressed = s;
	}
	sf::FloatRect Player::GetCollisionBox();
	
	void set_canShoot(bool shoot)
	{
		m_canShoot = shoot;
	}
	void Update();

	void Shoot(unsigned short player_x, std::vector<Bullet*> & bullets);


};