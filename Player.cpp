#include "Player.h"

#define MS 10.f //Movment Speed of Player
#define HPM 10; //Player's Max Health Point 10

//Private Functions
void Player::initVariables()
{
	this->movementSpeed = MS;
	this->hpMax = HPM;
	this->hp = hpMax;
}

void Player::initTextures()
{
	if (!this->texture.loadFromFile("Textures/player.png")) {
		throw "Could not Open Textures / player.png";
	}
}

void Player::initShape(sf::RenderTarget *target)
{
	this->shape.setTexture(this->texture);
	this->shape.setScale(0.4f, 0.4f);
	this->shape.setPosition(this->shape.getGlobalBounds().width, this->shape.getGlobalBounds().height + target->getSize().y / 2.5f);
	this->shape.rotate(180.f);
}

void Player::initText(sf::Font *font)
{
	this->hpText.setFont(*font);
	this->hpText.setFillColor(sf::Color::White);
	this->hpText.setCharacterSize(20);
}


//PUBLIC
//Constructure && Destructor
Player::Player(sf::Font *font, sf::RenderTarget *target)
{
	this->initVariables();
	this->initTextures();
	this->initShape(target);
	this->initText(font);
}

Player::~Player()
{
}

//Accessories
const sf::Sprite & Player::getShape() const
{
	// TODO: insert return statement here
	return this->shape;
}

const int & Player::getHp() const
{
	// TODO: insert return statement here
	return this->hp;
}

const int & Player::getHpMax() const
{
	// TODO: insert return statement here
	return this->hpMax;
}

//Functions
void Player::dicrementHp()
{
	this->hp--;
}

void Player::update(sf::RenderTarget * target)
{
	//Moving Player
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && this->shape.getPosition().x > this->shape.getGlobalBounds().width)
		this->shape.move(0.f - this->movementSpeed, 0.f);	//leftward
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && this->shape.getPosition().x < target->getSize().x)
		this->shape.move(this->movementSpeed, 0.f);			//rightward
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && this->shape.getPosition().y > this->shape.getGlobalBounds().height)
		this->shape.move(0.f, 0.f - this->movementSpeed);	//upward
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && this->shape.getPosition().y < target->getSize().y)
		this->shape.move(0.f, this->movementSpeed);			//downward
	
	//UI of Health Point  
	this->hpText.setPosition(this->shape.getPosition().x - this->shape.getGlobalBounds().width,
		this->shape.getPosition().y - this->shape.getGlobalBounds().height - 20.f);
	this->hpText.setString("hp: " + std::to_string(this->hp) + "/" + std::to_string(this->hpMax));
}

void Player::render(sf::RenderTarget * target)
{
	target->draw(this->shape); //Player
	target->draw(this->hpText); //PLayer's Health Point
}