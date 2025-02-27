#ifndef MENU_H
#define MENU_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "leaderboard.h" // Incluir leaderboard.h para usar Puntajes
#include <vector>
using namespace std;
using namespace sf;

class Menu {
private:
	int Opcion_actual = 0;
	RenderWindow &ventana;
	Texture textura;
	Sprite fondo_menu;
	Text texto_menu;
	Text texto_menu_play;
	Text texto_menu_leaderboard;
	Font font;
	Font font_top;
	Music musica_menu;
	SoundBuffer efecto_temp;
	Sound efecto_eleccion;
	
public:
	Menu(RenderWindow &ventana);
	void MostrarMenuPrincipal();
};

#endif
