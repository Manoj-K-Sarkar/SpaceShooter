#include "Bullet.h"

#define ST 15 //Spawn Timer
#define MS 15.f //Movment Speed

//Private Functions
void Bullet::initVariables()
{
	this->movementSpeed = MS;
	this->spawnTimer = ST;
}

void Bullet::initTextures()
{
	if (!this->texture.loadFromFile("Textures/bullet.png")) {
		throw "Could Not Open Textures / bullet.png";
	}
}

void Bullet::initShape()
{
	this->shape.setTexture(this->texture);

	this->shape.setScale(0.04f, 0.04f);
}

//PUblic Functions
//Constructors & Destructors
Bullet::Bullet()
{
	this->initVariables();
	this->initTextures();
	this->initShape();
}

Bullet::~Bullet()
{
}

const sf::Sprite & Bullet::getShape() const
{
	// TODO: insert return statement here
	return this->shape;
}

//Accessors


void Bullet::update(std::vector<Bullet> &bullets, sf::Vector2f startingPoint, sf::RenderTarget * target)
{

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && this->spawnTimer <= 0) {
		this->shape.setPosition(startingPoint);
		bullets.push_back(Bullet(*this));

		spawnTimer = ST;
	}
	else {
		spawnTimer--;
	}

	for (size_t i = 0; i < bullets.size(); i++) {
		bullets[i].shape.move(this->movementSpeed, 0.f);

		//Collision with window
		if (bullets[i].shape.getPosition().x > target->getSize().x)
			bullets.erase(bullets.begin() + i);
	}
}

void Bullet::render(std::vector<Bullet> &bullets, sf::RenderTarget * target)
{
	for (size_t i = 0; i < bullets.size(); i++) {
		target->draw(bullets[i].shape);
	}
}
