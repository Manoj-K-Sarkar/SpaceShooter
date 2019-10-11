#pragma once
#include <SFML/Graphics.hpp>

class Enemy
{
private:
	sf::Sprite shape;
	sf::Texture texture;

	int hp;
	int hpMax;
	int spawnTimer;
	float movementSpeed;

	sf::Text hpText;


	void initVariables();
	void initTexture();
	void initShape();
	void initText(sf::Font *font);

public:
	Enemy();
	virtual ~Enemy();

	const sf::Sprite& getShape() const;
	const int& getHp() const;
	const int& getHpMAx() const;

	void dicrementHp();
	void update(sf::Font *font, std::vector<Enemy> &enemies, sf::RenderTarget *target);
	void render(std::vector<Enemy> &enemies, sf::RenderTarget *target);
};

