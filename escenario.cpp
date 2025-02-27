#include "escenario.h"
#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>

using namespace sf;

Escenario::Escenario(int num_archivo) {
	if (!textureFondo.loadFromFile("resources/background/scene" + std::to_string(num_archivo) + ".jpg")) {
		std::cerr << "Error: No se pudo cargar la textura del fondo." << std::endl;
		
	}
	background.setTexture(textureFondo);
	background.setPosition(-10.0f,-50.0f);
	background.setScale(1.3,1.3f);
	
	globo_t.loadFromFile("resources/background/globo.png");
	globo.setTexture(globo_t);
	globo.setPosition(515,108);
	globo.setScale(4.3f,4.3f);
	
	silla_t.loadFromFile("resources/background/silla.png");
	silla.setTexture(silla_t);
	silla.setPosition(415,154);
	silla.setScale(4.1f,4.1f);
	
}
const Sprite& Escenario::getBackground() const {
	return background;
}
const Sprite& Escenario::getGlobo() const {
	return globo;
}
const Sprite& Escenario::getSilla() const {
	return silla;
}
