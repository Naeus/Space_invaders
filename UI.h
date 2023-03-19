#pragma once
#include <SFML/Graphics.hpp>
#include "controller.h"
#include <string>

class UI {


private:
    sf::RenderWindow& m_window;
    sf::Font m_font;
    sf::Text m_text;
    sf::Text m_GameOver;
    int m_score;
    int m_level;

public:
    UI(sf::RenderWindow& window) : m_window(window), m_score(0) 
    {
        m_font.loadFromFile("Resources/Fonts/space_invaders.ttf");
        m_text.setFont(m_font);
        m_text.setString("Score: " + std::to_string(m_score));
        m_text.setCharacterSize(24);
        m_text.setFillColor(sf::Color::White);
        m_text.setPosition(10, 10);
    }

    void setScore(int score)
    {
        m_score = score;
        m_text.setString("Score: " + std::to_string(m_score));
    }
    void SetLevel(int level)
    {
        m_level = level;
    
    }
    void draw()
    {
        m_window.draw(m_text);
    }

    void GameOver(sf::RenderWindow& window)
    {
        m_GameOver.setFont(m_font);
        m_GameOver.setCharacterSize(50);
        m_GameOver.setString("GAME OVER. PRESS R TO RESTART");

        m_GameOver.setPosition(SCREEN_HEIGHT / 2, SCREEN_WIDTH / 2);
        window.draw(m_GameOver);
    }
    
};