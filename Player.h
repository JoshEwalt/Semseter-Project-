#ifndef PLAYER_H
#define PLAYER_H
#include <SFML/Graphics.hpp>

class Player {
private:
	int health = 3;
	int maxHealth = 3;
	sf::Vector2f position;
public:
	int getHealth() {
		return health;
	}
	Player() {}
	sf::Vector2f getPosition() {
		return position;
	
	}
	void setPosition(sf::Vector2f newPosititon) {
		position = newPosititon;

	}
	void addToX(float Value) {
		position.x += Value;

	}
	void addToY(float Value) {
		position.y += Value;
	}
	void setX(float Value) {
		position.x = Value;
	}
	void setY(float Value) {
		position.y = Value;
	}

	int getDamage() {
		return 1;
	}
	void takeDamage(int amount ) {
		if (health > 0) {
			health--;
		}
		
	}
	bool isDead() {
		return health <= 0;
	}
	void setHealth() {
		health = maxHealth;
	}
};







#endif 
//index = 4990
//heart = 1970