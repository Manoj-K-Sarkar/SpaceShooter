#pragma once
#include <SFML/Graphics.hpp>
#include "Player.h"
#include "Bullet.h"
#include "Enemy.h"

/* 
	Class That Act As the Game Engine
	Wrapper Class
*/

class Game
{
private:
	//Variable;
	//Window
	sf::RenderWindow *window;
	sf::VideoMode videoMode;
	sf::Event event;

	bool pause;
	int score;

	//UI Things
	sf::Font *font;
	sf::Text gameOverText;
	sf::Text pauseText;
	sf::Text scoreText;

	//Game Objects
	Player *player;
	Bullet bullet;
	std::vector<Bullet> bullets;
	Enemy enemy;
	std::vector<Enemy> enemies;

	//Functions
	void initVariables();
	void initFont();
	void initWindow();
	void initObjects();
	void initTexts();
	
public:
	//Constructors / Destructors
	Game();
	virtual ~Game();

	//Accessors
	bool play();
	bool isGameOver();
	//bool isGamePause();TODO================

	//Function
	void pollEvent();
	void guiUpdate();
	void collisionControl();
	void guiRender();
	void update();
	void render();
};