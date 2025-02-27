#ifndef ESCENARIO_H
#define ESCENARIO_H

#include <SFML/Graphics.hpp>

using namespace sf;

class Escenario {
private:
	Texture textureFondo; 
	Sprite background;   
	Sprite globo; Texture globo_t;
	Sprite silla; Texture silla_t;
	
public:
	Escenario(int num_archivo);                 
	const Sprite& getBackground() const;
	const Sprite& getGlobo() const;
	const Sprite& getSilla() const;
};

#endif 
