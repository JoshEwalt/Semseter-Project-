#ifndef TEXTURE_H
#define TEXTURE_H
#include "Image.h"
#include <SFML/Graphics.hpp>

class Texture {
public:
	Image* image;
	Texture(Image* newImage) {
		image = newImage;
	}
	Texture() {


	}




};






#endif 