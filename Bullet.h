#pragma once
#include <SFML/Graphics.hpp>

class Bullet
{
private:
	sf::Sprite shape;
	sf::Texture texture;

	float movementSpeed;
	int spawnTimer;

	void initVariables();
	void initTextures();
	void initShape();
public:
	Bullet();
	virtual ~Bullet();

	//Accessors
	const sf::Sprite& getShape() const;

	//Functions
	void update(std::vector<Bullet> &bullets, sf::Vector2f startingPoint, sf::RenderTarget *target);
	void render(std::vector<Bullet> &bullets, sf::RenderTarget *target);
};