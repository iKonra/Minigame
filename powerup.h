#ifndef POWERUP_H
#define POWERUP_H

#include "vidas.h"
#include <SFML/Graphics.hpp>
#include <vector>

using namespace std;
using namespace sf;

class PowerUp {
private:
	Sprite sprite_up;
	Texture textura_up; 
	bool hay_uno = false;
public:
	PowerUp();
	void GenerarPowerUp(vector<FloatRect>& paredes);
	void AddVida(Vidas &vida);
	bool verificarColision(const FloatRect& jugadorBounds, Vidas& vida,Personaje& jugador);
	void Dibujar(RenderWindow& ventana);
	
	
};

#endif
