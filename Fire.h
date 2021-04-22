#ifndef FIRE_H
#define FIRE_H
#include <SFML/Graphics.hpp>

class Fire {
private:
	int health = 20;
	int maxHealth = 20;
	sf::Vector2f position;
public:
	Fire() {}
	sf::Vector2f getPosition() {
		return position;
	}
	void setPosition(sf::Vector2f newPosition) {
		position = newPosition;
	}
	void takeDamage(int value ) {
		health -= value;
			
	}
	int getHealth() {
		return health;
	}
	void setHealth() {
		health = 20;
	}

};







#endif 
//index = 54