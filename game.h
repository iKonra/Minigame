#ifndef GAME_H
#define GAME_H
#include <SFML/Graphics.hpp>
#include <vector>
#include <SFML/Audio/Music.hpp>

using namespace sf;
using namespace std;

class Personaje {
private:
	vector<Texture> textura_derecha; // Textura para mirar a la derecha
	vector<Texture> textura_izquierda; // Textura para mirar a la izquierda
	bool skin_cambiada = false;
	int indice_skin_actual = 0;
	bool mirandoDerecha = true;
	Sprite skin_actual; // Sprite actual del personaje
	int skin_numero_actual; 
	int puntaje = 0;
	Music musica_game;
	int Puntaje;
	
public:
	Personaje();
	Sprite mostrarSkin();
	void moverPersonita(float x, float y, const vector<FloatRect>& paredes);
	int verActual();
	Vector2f getPosition() const;
	void reproducirMusica();
	void pararMusica();
	void ModificarPuntaje(int puntaje);
	int VerPuntaje();
	void cambiarSkinAleatoria();
	
};

bool hayColision(const FloatRect& area, const vector<FloatRect>& paredes);
void Empezar(RenderWindow& ventana);

#endif
