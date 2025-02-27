#ifndef LEADERBOARD_H
#define LEADERBOARD_H

#include <SFML/Graphics.hpp>
#include "menu.h"
#include <vector>
#include <string>
using namespace std;
using namespace sf;

class Menu; // Como menu necesita de leaderboard y leaderboard de menu, esta es una forma de que se ejecute sin ver cual se creo primero

struct Puntajes {
	char j_nombre[30];
	int j_puntaje;
	
	bool operator<(const Puntajes& otro) const {
		return j_puntaje > otro.j_puntaje;
	}
};

class Leaderboard {
private:
	RenderWindow &ventana;
	vector<Text> leaderboard;
	vector<Puntajes> aux_leaderboard;
	vector<float> posiciones_y;
	Texture textura;
	Sprite fondo_menu;
	Font font;
	Font font_top;
	Text texto_leaderboard;
	
public:
	Leaderboard(RenderWindow &ventana);
	void AbrirLeaderboard(RenderWindow &ventana,Menu &menu);
	void GuardarLeaderboard();
	void ActualizarLeaderboard(string nombre, int puntaje);
	int verPeorPuntaje();
	void CargarLeaderboard();
};

#endif
