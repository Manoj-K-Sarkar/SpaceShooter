#include "Enemy.h"

#define ST 20 //Spawn Timer of Enemies
#define MS -10.f //Movment Speed of Enemies
#define HPM 3; //Enemies Max Health Point 3

//Private Functions
void Enemy::initVariables()
{
	this->hpMax = HPM;
	this->hp = this->hpMax;
	this->spawnTimer = ST;
	this->movementSpeed = MS;
}

void Enemy::initTexture()
{
	if (!this->texture.loadFromFile("Textures/enemy.png")) {
		throw "Could Not Open Textures/enemy.png";
	}
}

void Enemy::initShape()
{
	this->shape.setTexture(this->texture);
	this->shape.setScale(0.08f, 0.08f);
	this->shape.rotate(180.f);
}

void Enemy::initText(sf::Font *font)
{
	this->hpText.setFont(*font);
	this->hpText.setFillColor(sf::Color::Red);
	this->hpText.setCharacterSize(20);
}

//Public
//Constructor / Destructors
Enemy::Enemy()
{
	this->initTexture();
	this->initShape();
	this->initVariables();
}

Enemy::~Enemy()
{
}

//Accessors
const sf::Sprite & Enemy::getShape() const
{
	// TODO: insert return statement here
	return this->shape;
}

const int & Enemy::getHp() const
{
	// TODO: insert return statement here
	return this->hp;
}

const int & Enemy::getHpMAx() const
{
	// TODO: insert return statement here
	return this->hpMax;
}

//Functions
void Enemy::dicrementHp()
{
	this->hp--;
}

void Enemy::update(sf::Font *font, std::vector<Enemy>& enemies, sf::RenderTarget *target)
{
	float y = (rand() % target->getSize().y) + this->shape.getGlobalBounds().height;
	if (y > target->getSize().y)
		y = target->getSize().y / 2;

	if (this->spawnTimer <= 0) {
		this->shape.setPosition(sf::Vector2f(target->getSize().x, y));
		//Enemy health Point Initialize
		this->initText(font);
		enemies.push_back(Enemy(*this));

		this->spawnTimer = ST;
	}
	else
		this->spawnTimer--;

	for (size_t i = 0; i < enemies.size(); i++) {
		enemies[i].shape.move(this->movementSpeed, 0.f);
		//Enemy health point
		enemies[i].hpText.setPosition(enemies[i].shape.getPosition().x - this->shape.getGlobalBounds().width + 2.f,
			enemies[i].shape.getPosition().y - this->shape.getGlobalBounds().height);
		enemies[i].hpText.setString(std::to_string(enemies[i].hp) + "/" + std::to_string(enemies[i].hpMax));

		//Collision with window
		if (enemies[i].shape.getPosition().x < 0) {
			enemies.erase(enemies.begin() + i);
		}
	}
}

void Enemy::render(std::vector<Enemy> &enemies, sf::RenderTarget * target)
{
	for (size_t i = 0; i < enemies.size(); i++) {
		target->draw(enemies[i].shape);//Drawing Enemy 
		target->draw(enemies[i].hpText);//Enemy Health Point
	}
}
