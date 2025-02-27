#include "powerup.h"
#include "vidas.h"
#include "game.h"

#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

using namespace sf;
using namespace std;

PowerUp::PowerUp() {
	if (!textura_up.loadFromFile("resources/powerup/powerup.png")) { 
		cerr << "Error al cargar la textura de powerup." << endl;
	}
	sprite_up.setTexture(textura_up);
	sprite_up.setScale(0.5f, 0.5f);
}

void PowerUp::GenerarPowerUp(vector<FloatRect>& paredes) {
	if (!hay_uno) { 
		int random = rand() % 5; 
		
		if (random == 1) {
			FloatRect powerupPosicion;
			bool posicionValida = false;
			
			while (!posicionValida) { 
				int x = rand() % 1024; 
				int y = rand() % 768;  
				
				powerupPosicion = FloatRect(x, y, 100, 100);
				
				if (!hayColision(powerupPosicion, paredes)) {
					posicionValida = true;
				}
			}
			
			sprite_up.setPosition(powerupPosicion.left, powerupPosicion.top);
			hay_uno = true;
		}
	}
}

void PowerUp::AddVida(Vidas &vida) {
	vida.CargarVidas(vida.verCantVidas() + 1);
}

bool PowerUp::verificarColision(const FloatRect& jugadorBounds, Vidas& vida, Personaje& jugador) {
	if (hay_uno && sprite_up.getGlobalBounds().intersects(jugadorBounds)) {
		int efecto = rand() % 3; // 66,6% de cambiar skin 33,3% de agregar vida.
		
		if (efecto == 0 or efecto == 1) {
			jugador.cambiarSkinAleatoria(); 
		} else {
			AddVida(vida); 
		}
		
		hay_uno = false;
		return true;
	}
	return false;
}

void PowerUp::Dibujar(RenderWindow& ventana) {
	if (hay_uno) { 
		ventana.draw(sprite_up);
	}
}
