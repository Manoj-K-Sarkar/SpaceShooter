#include "Game.h"

#define SPE 10 // Score Per Enemy

//Private functions
void Game::initVariables()
{
	this->window = nullptr;
	this->font = nullptr;
	this->videoMode.height = 800;
	this->videoMode.width = 1600;
	this->score = 0;
	this->pause = false;
}

void Game::initFont()
{
	this->font = new sf::Font;
	if (!this->font->loadFromFile("Fonts/Inconsolata-Regular.ttf")) {
		throw "Could not Open Fonts/Inconsolata-Regular.ttf";
	}
}

void Game::initWindow() {
	this->window = new sf::RenderWindow(this->videoMode, "Shooter Game");
	this->window->setFramerateLimit(60);
}

void Game::initObjects()
{
	this->player = new Player(this->font, this->window);
}

void Game::initTexts()
{
	//Score Board
	this->scoreText.setFont(*font);
	this->scoreText.setStyle(sf::Text::Bold);
	this->scoreText.setFillColor(sf::Color::Green);
	this->scoreText.setCharacterSize(30);
	this->scoreText.setPosition(this->window->getSize().x - 250.f, 5.f);
	
	//Game Over
	this->gameOverText.setFont(*font);
	this->gameOverText.setFillColor(sf::Color::Red);
	this->gameOverText.setCharacterSize(50);
	this->gameOverText.setPosition(this->window->getSize().x / 2 - 220.f, this->window->getSize().y / 2 - 100.f);
	this->gameOverText.setString("GAME OVER!");
	this->gameOverText.setLetterSpacing(5);
	this->gameOverText.setStyle(sf::Text::Bold);

	//Game Pause
	this->pauseText.setFont(*font);
	this->pauseText.setFillColor(sf::Color::Yellow);
	this->pauseText.setCharacterSize(30);
	this->pauseText.setPosition(this->window->getSize().x / 2 - 250.f, this->window->getSize().y / 2 - 100.f);
	this->pauseText.setString("PRESS SPACE FOR CONTINUE");
	this->pauseText.setLetterSpacing(4);
}


//Public
//Constructors / Destructors
Game::Game()
{
	this->initVariables();
	this->initFont();
	this->initWindow();
	this->initObjects();
	this->initTexts();
}

Game::~Game()
{
	delete this->window;
	delete this->player;
	delete this->font;
}

//Accessors
bool Game::play() {
	return this->window->isOpen();
}

bool Game::isGameOver()
{
	if (this->player->getHp() <= 0) {
		this->player->update(this->window);
		return true;
	}
	return false;
}

//TODO=============================================
//bool Game::isGamePause()
//{
//	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
//		this->pause = !this->pause;
//		//std::cout << pause << std::endl;
//	}
//	return this->pause;
//}

//Functions
void Game::pollEvent()
{
	//Event Polling
	while (this->window->pollEvent(this->event)) {
		if (event.type == sf::Event::Closed) {
			this->window->close();
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
			this->pause = true;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
			this->pause = false;
		}
	}
}

void Game::guiUpdate()
{
	this->scoreText.setString("SCORE : " + std::to_string(this->score));
}

void Game::collisionControl()
{
	for (size_t i = 0; i < this->enemies.size(); i++) {
		//with player
		if (this->enemies[i].getShape().getGlobalBounds().intersects(this->player->getShape().getGlobalBounds())) {
			this->enemies.erase(this->enemies.begin() + i);
			this->player->dicrementHp();
			break;
		}
		//with bullets
		for (size_t k = 0; k < this->bullets.size(); k++) {
			if (this->enemies[i].getShape().getGlobalBounds().intersects(this->bullets[k].getShape().getGlobalBounds())) {
				this->enemies[i].dicrementHp();
				this->bullets.erase(this->bullets.begin() + k);
				break;
			}
		}
		//Remove Enemy
		if (!this->enemies[i].getHp()) {
			this->enemies.erase(this->enemies.begin() + i);
			this->score += SPE; //Update Score
			break;
		}
	}
}

void Game::guiRender()
{
	//Score Board
	this->window->draw(this->scoreText);

	//Game Over
	if (this->isGameOver())
		this->window->draw(this->gameOverText);

	//Game Pause
	if (this->pause)
		this->window->draw(this->pauseText);
}

void Game::update()
{
	/*
		@void return

		- Polling control
		- Player update
		- set starting point of bullet
		- Bullets update
		- Enemies update
		- Collision Control
	*/
	this->pollEvent();
	if (!this->isGameOver() && !pause) {
		this->player->update(this->window);
		sf::Vector2f sp(this->player->getShape().getPosition().x - 20.f,
			this->player->getShape().getPosition().y - this->player->getShape().getGlobalBounds().height / 2 - 10.f);
		this->bullet.update(this->bullets, sp, this->window);
		this->enemy.update(this->font, this->enemies, this->window);
		this->collisionControl();
		this->guiUpdate();
	}
}

void Game::render()
{
	/*
		@void return

		-clearing window
		-drawing updates of player 
		-drawing updates of bullets
		-drawing updates of enemies
		-show if Game Over
		-show if Game Pause
		-Display All The Above Thins In Window
	*/

	this->window->clear();

	//Draw Game
	this->bullet.render(this->bullets,this->window);
	this->enemy.render(this->enemies, this->window);
	this->player->render(this->window);
	this->guiRender();

	this->window->display();
}