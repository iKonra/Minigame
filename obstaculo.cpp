#include "obstaculo.h"
#include <cstdlib>
#include <ctime>
#include <cmath> 
#include <iostream>
using namespace std;

Obstaculo::Obstaculo() : tiempoSpawn(0), intervaloSpawn(1.0f), velocidadBase(80.0f), dificultad(1.0f) {
	srand(static_cast<unsigned>(time(0))); // Inicializa el generador 
	
	texturaLibro.resize(3); // Reserva espacio para los 3 tipos de textura
	for (int i = 1; i <= 3; i++) {
		if (!texturaLibro[i-1].loadFromFile("resources/enemys/enemy" + to_string(i) + ".png")) {
			cerr << "Error cargando la textura: resources/enemys/enemy" + to_string(i) + ".png" << endl;
		}
	}
}


void Obstaculo::spawn(Vector2f posicionInicial, Vector2f velocidad, bool especial) {
	
	int num_aleatorio = rand()%3;
	Objeto nuevoObjeto {
		.sprite = Sprite(texturaLibro[num_aleatorio]),
			.velocidad = velocidad,
			.tiempoVida = 0.0f,
			.especial = especial
	};
	float escala = 1 * (rand() % 3); // Tamaño aleatorio entre 0.1 y 0.5
	nuevoObjeto.sprite.setPosition(posicionInicial);
	nuevoObjeto.sprite.setScale(escala, escala);
	objetos.push_back(nuevoObjeto);
}

void Obstaculo::actualizar(float dt, Vector2f limiteVentana) {
	tiempoSpawn += dt;
	
	// Generar obstaculos por todos los lados
	if (tiempoSpawn >= intervaloSpawn) {
		int lado = rand() % 4;
		Vector2f posicionInicial, velocidad;
		
		switch (lado) {
		case 0: // Desde arriba
			posicionInicial = {static_cast<float>(rand() % static_cast<int>(limiteVentana.x)), -50};
			velocidad = {0, velocidadBase};
			break;
		case 1: // Desde abajo
			posicionInicial = {static_cast<float>(rand() % static_cast<int>(limiteVentana.x)), limiteVentana.y + 50};
			velocidad = {0, -velocidadBase};
			break;
		case 2: // Desde la izquierda
			posicionInicial = {-50, static_cast<float>(rand() % static_cast<int>(limiteVentana.y))};
			velocidad = {velocidadBase, 0};
			break;
		case 3: // Desde la derecha
			posicionInicial = {limiteVentana.x + 50, static_cast<float>(rand() % static_cast<int>(limiteVentana.y))};
			velocidad = {-velocidadBase, 0};
			break;
		}
		
		// 20% de probabilidades de que se genere con movimiento especial
		bool especial = (rand() % 100 < 20);
		spawn(posicionInicial, velocidad, especial);
		tiempoSpawn = 0;
		
		// Se generan mas rapido y mas rapido segun el tiempo de juego
		intervaloSpawn = max(0.3f, intervaloSpawn - 0.01f * dificultad);
		velocidadBase += 0.5f * dificultad;
		dificultad += 0.01f; 
	}
	

	for (auto& obj : objetos) {
		obj.tiempoVida += dt;
		
		// movimiento atraves de funcion sen
		if (obj.especial) {
			float desplazamiento = 20.0f * sin(obj.tiempoVida * 8.0f); 
			obj.sprite.move(obj.velocidad * dt + Vector2f(desplazamiento * dt, 0));
		} else {
			obj.sprite.move(obj.velocidad * dt);
		}
		
		// Cambiar dirección aleatoriamente
		if (!obj.especial && rand() % 100 < 5) {
			obj.velocidad.x += (rand() % 3 - 1) * 20.0f; 
		}
	}
	
	// Borrar obstaculos si se salen de la pantalla
	objetos.erase(remove_if(objetos.begin(), objetos.end(),[&limiteVentana](const Objeto& obj) {
	Vector2f pos = obj.sprite.getPosition();
				return (pos.x < -100 || pos.x > limiteVentana.x + 100 ||pos.y < -100 || pos.y > limiteVentana.y + 100);
							}),
				  objetos.end());
}

void Obstaculo::dibujar(RenderWindow& ventana) {
	for (const auto& obj : objetos) {
		ventana.draw(obj.sprite);
	}
}

bool Obstaculo::verificarColision(const FloatRect& jugadorBounds) {
	auto it = find_if(objetos.begin(), objetos.end(),[&jugadorBounds](const Objeto& obj) {
		return obj.sprite.getGlobalBounds().intersects(jugadorBounds);
					  });
	if (it != objetos.end()) {
		objetos.erase(it);
		return true;
	}
	return false;
}
