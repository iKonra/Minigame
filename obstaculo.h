#ifndef OBSTACULO_H
#define OBSTACULO_H

#include <SFML/Graphics.hpp>
#include <vector>

using namespace std;
using namespace sf;

struct Objeto {
	Sprite sprite;       
	Vector2f velocidad; 
	float tiempoVida;    
	bool especial;      
};

class Obstaculo {
private:
	vector<Texture> texturaLibro;
	vector<Objeto> objetos;
	float tiempoSpawn;
	float intervaloSpawn;
	float velocidadBase;
	float dificultad; 
public:
	Obstaculo();
	void spawn(Vector2f posicionInicial, Vector2f velocidad, bool especial = false);
	void actualizar(float dt, Vector2f limiteVentana);
	void dibujar(RenderWindow& ventana);
	bool verificarColision(const FloatRect& jugadorBounds);
	
};

#endif // OBSTACULO_H
