#include "vidas.h"
#include "GameOver.h"
#include <iostream>

using namespace sf;
using namespace std;


Vidas::Vidas(int opcion) {
	if (!textura.loadFromFile("resources/life/corazon.png")) { 
		cerr << "Error al cargar la textura de los corazones." << endl;
	} else {
		CargarVidas(opcion);
	}
}

void Vidas::CargarVidas(int opcion) {
	vidas.clear();
	for (int i = 0; i < opcion; i++) {
		Sprite corazon(textura);       
		corazon.setPosition(separacion * i, 6.0f); 
		corazon.setScale(0.05f,0.05f);
		vidas.push_back(corazon); 
	}
}

bool Vidas::ActualizarVida(bool agregar, RenderWindow& w, Personaje& jugador) {
	if (agregar) {
		Sprite corazon(textura);
		corazon.setPosition(separacion * vidas.size(), 6.0f);
		corazon.setScale(0.05f, 0.05f);
		vidas.push_back(corazon);
		return true;
	} else {
		vidas.pop_back();
		if (vidas.empty()) {
			jugador.pararMusica();
			GameOverScreen GO;
			int puntaje = jugador.VerPuntaje();
			GO.show(w,puntaje);
			return false;
		}
		return true;
	}
}

void Vidas::Dibujar(RenderWindow& w) {
	int maxVidas = 5; // Cantidad Maxima de vidas que se muestran en pantalla
	int cont = 0;
	
	for (auto& corazon : vidas) {
		if (cont < maxVidas) {
			if (vidas.size() == 1) {
				corazon.setScale(0.046f + static_cast<float>(rand()) / (RAND_MAX / (0.05f - 0.046f)),0.046f + static_cast<float>(rand()) / (RAND_MAX / (0.05f - 0.046f)));
			} 
			w.draw(corazon);
			cont++;
		}
	}
	
	if (vidas.size() > maxVidas) {
		for (int i = 0; i < maxVidas; i++) {
			w.draw(vidas[i]);
		}
		
		Text texto;
		Font font;
		
		font.loadFromFile("fonts/Monocraft.ttf");
		texto.setFont(font);
		texto.setCharacterSize(24);
		texto.setFillColor(Color::White);
		texto.setString("+" + to_string(vidas.size() - maxVidas)); 
		texto.setPosition(separacion * (maxVidas + 0.1f), 10.0f);
		
		w.draw(texto);
	}
}
int Vidas::verCantVidas() {
	return vidas.size();
}
