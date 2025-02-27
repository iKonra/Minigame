#ifndef VIDAS_H
#define VIDAS_H

#include <SFML/Graphics.hpp>
#include <vector>
#include "game.h"
#include <iostream>
#include <string>

using namespace std;
using namespace sf;

class Vidas {
private:                
	vector<Sprite> vidas;     
	Texture textura;          // Textura del corazon
	float separacion = 50.0f; 
	RenderWindow win;
	
public:
	Vidas(int opcion);                 
	void CargarVidas(int opcion);         
	bool ActualizarVida(bool agregar,RenderWindow& w,Personaje& jugador);    
	void Dibujar(RenderWindow& w);
	int verCantVidas();
};

#endif
