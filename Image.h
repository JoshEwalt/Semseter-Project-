#ifndef IMAGE_H
#define IMAGE_H
#include <SFML/Graphics.hpp>

class Image {
public:

	sf::Sprite image;
	const int columns = 64;
	const int rows = 95;
	Image(string newName, sf::Texture& texture, int index, float newSize) {


		int down = floor(index / columns);
		image = sf::Sprite(texture, sf::IntRect(32 * (index - columns * down), down * 32, 32, 32));
		sf::Vector2f size = sf::Vector2f(newSize / 32, newSize / 32);
		image.setScale(size);

	}
	void draw(sf::RenderWindow& window, sf::Vector2f position) {
		image.setPosition(position);
		window.draw(image);
	}
	Image(){}
};





#endif 