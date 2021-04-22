#ifndef ZOMBIE_H
#define ZOMBIE_H
#include <SFML/Graphics.hpp>

using namespace std;


class Zombie {
private:
	int health = 5;
	int maxHealth = 5;
	sf::Vector2f position;
	float timer = 0;
	float hitTime = 0.5;
	
public:
	bool active;
	Zombie(sf::Vector2f newPosition){
		position = newPosition;
		health = 5;
	}
	Zombie(){
		health = 5;
	}
	sf::Vector2f getPosition(){
		return position;
	}
	void setPosition(sf::Vector2f newPosition) { position = newPosition; }

	bool move(sf::Vector2f target, float speed, float deltaTime) {
		bool xWorks = false, yWorks = false;
		if (abs(target.x - position.x) > 64) {
			xWorks = true;
			if (target.x < position.x) {
				position.x -= speed;
				if (position.x < target.x)
					position.x = target.x;

			}
			if (target.x > position.x) {
				position.x += speed;
				if (position.x > target.x)
					position.x = target.x;

			}
		}
		if (abs(target.y - position.y) > 64) {
			yWorks = true;
			if (target.y < position.y) {
				position.y -= speed;
				if (position.y < target.y)
					position.y = target.y;

			}

			if (target.y > position.y) {
				position.y += speed;
				if (position.y > target.y)
					position.y = target.y;

			}
		}
		if (!xWorks && !yWorks) {
			timer += deltaTime;
			if (timer >= hitTime) {
				timer = 0;
				return true;
			}
		}
		else {
			timer = 0;
		}
		return false;
	}
	void takeDamage(int amount) {
		health -= amount;
		if (health <= 0) {
			health = 0;
			active = false;
		}
	}
	void init(sf::Vector2f newPosition) {
		position = newPosition;
		active = true;
		timer = 0;

	}





};






#endif
//index = 4999
