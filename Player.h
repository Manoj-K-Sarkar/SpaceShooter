#pragma once
#include <SFML/Graphics.hpp>

class Player
{
private:
	sf::Sprite shape;
	sf::Texture texture;
	
	float movementSpeed;
	int hp;
	int hpMax;
	sf::Text hpText;

	void initVariables();
	void initTextures();
	void initShape(sf::RenderTarget *target);
	void initText(sf::Font *font);

public:
	Player(sf::Font *font, sf::RenderTarget *target);
	virtual ~Player();

	//Accessors
	const sf::Sprite& getShape() const;
	const int& getHp() const;
	const int& getHpMax() const;

	//Functions
	void dicrementHp();
	void update(sf::RenderTarget *target);
	void render(sf::RenderTarget *target);
};

