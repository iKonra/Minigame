#include "game.h"
#include "vidas.h"
#include "menu.h"
#include "gameover.h"
#include "escenario.h"
#include "powerup.h"
#include "obstaculo.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>

#include <iomanip>
using namespace sf;
using namespace std;

Personaje::Personaje() {
	
	
	vector<string> rutas_derecha = {
			"resources/jugador/player1.png"
	};
	
	vector<string> rutas_izquierda = {
			"resources/jugador/player2.png"
	};
	for(int i=1;i<7;i++) { 
		rutas_derecha.push_back("resources/jugador/player1_variation" + to_string(i) + ".png");
		rutas_izquierda.push_back("resources/jugador/player2_variation" + to_string(i) + ".png");
	}
	
	for (const auto& ruta : rutas_derecha) {
		Texture tex;
		if (tex.loadFromFile(ruta)) {
			textura_derecha.push_back(tex);
		} else {
			cerr << "No se encontro la ruta:"  << ruta << endl;
		}
	}
	
	for (const auto& ruta : rutas_izquierda) {
		Texture tex;
		if (tex.loadFromFile(ruta)) {
			textura_izquierda.push_back(tex);
		} else {
			cerr << "No se encontro la ruta:" << ruta << endl;
		}
	}
	
		skin_actual.setTexture(textura_derecha[0]); // Arranco con la textura default
		skin_actual.setScale(0.1f, 0.1f);
		skin_actual.setPosition(520, 350);
	
	if (!musica_game.openFromFile("resources/sounds/game.wav")) {
		cerr << "No se pudo cargar el archivo de audio\n";
	}
	musica_game.setLoop(true); musica_game.setVolume(5);
}

Sprite Personaje::mostrarSkin() {
	return skin_actual;
}

void Personaje::moverPersonita(float x, float y, const vector<FloatRect>& paredes) {
	
	Vector2f nuevaPosicion = skin_actual.getPosition() + Vector2f(x, y);
	FloatRect areaNueva = skin_actual.getGlobalBounds();
	areaNueva.left = nuevaPosicion.x;
	areaNueva.top = nuevaPosicion.y;
	
	if (!hayColision(areaNueva, paredes)) {
		// Actualizar dirección siempre
		if (x > 0) {
			mirandoDerecha = true;
		} else if (x < 0) {
			mirandoDerecha = false;
		}
		
		// Cambio la textura del personaje segun si ve a la derecha o izquierda
		if (mirandoDerecha) {
			skin_actual.setTexture(textura_derecha[indice_skin_actual]); 
		} else {
			skin_actual.setTexture(textura_izquierda[indice_skin_actual]); 
		}
		
		skin_actual.move(x, y);
	}
}

void Personaje::cambiarSkinAleatoria() {
	if (textura_derecha.size() < 2 || textura_izquierda.size() < 2) return; 
	
	int nuevo_indice = rand() % textura_derecha.size(); 
	indice_skin_actual = nuevo_indice; 
	
	// Aplica la skin correcta según la dirección
	if (mirandoDerecha) {
		skin_actual.setTexture(textura_derecha[indice_skin_actual]);
	} else {
		skin_actual.setTexture(textura_izquierda[indice_skin_actual]);
	}
}



Vector2f Personaje::getPosition() const {
	return skin_actual.getPosition();
}
void Personaje::reproducirMusica() {
	if (musica_game.getStatus() != Music::Playing) {
		musica_game.play();
	}
}
void Personaje::pararMusica() {
	musica_game.stop();
};
void Personaje::ModificarPuntaje(int puntaje) {
	Puntaje = puntaje;
}
int Personaje::VerPuntaje() {
	return Puntaje;
}
bool hayColision(const FloatRect& area, const vector<FloatRect>& paredes) {
	for (const auto& pared : paredes) {
		if (area.intersects(pared)) {
			return true; // se choca contra una pared
		}
	}
	return false; 
}


void Empezar(RenderWindow& ventana) {
	Escenario escenario(1); 
	Personaje jugador;
	Vidas vida(3);     
	bool gameOver = false;
	
	
	PowerUp powerUp; 
	Clock relojPowerUp;
	jugador.reproducirMusica();
	
	Obstaculo obstaculos;
	
	// Lista de hitboxes
	vector<FloatRect> paredes = {
		FloatRect(0, 0, 1024, 155),  // Pared superior
			FloatRect(20, 0, 90, 768),   // Pared izquierda
			FloatRect(100, 165, 70, 50), // Esquina izquierda superior
			FloatRect(100, 580, 70, 80), // Esquina izquierda inferior
			FloatRect(255, 135, 100, 55), // Mueble parte izquierda
			FloatRect(0, 640, 1024, 180),// Pared inferior
			FloatRect(930, 0, 100, 768),  // Pared derecha
			FloatRect(868, 110, 100, 100), // Esquina derecha superior
			FloatRect(625, 145, 270, 50),// Muebles esquina superior
			FloatRect(875, 580, 80, 80), // Esquina inferior derecha
			FloatRect(435, 285, 175, 25), // Mesa
			FloatRect(250,410,110,28), // Silla 1
			FloatRect(250,450,35,1), // Silla de la silla 1 (confuso pero bueno)
			FloatRect(435,410,45,28), // Silla 2
			FloatRect(440,450,30,1), // Silla de la silla 2 (confuso pero bueno)
			FloatRect(560,410,45,28), // Silla 3
			FloatRect(570,450,30,1), // Silla de la silla 3 (confuso pero bueno) Si... voy a hacer copypaste para todos los textos
			FloatRect(683,410,110,28), // Silla 4
			FloatRect(690,450,35,0.5), // Silla de la silla 4 (confuso pero bueno)
			FloatRect(310,530,110,29), // Silla 5
			FloatRect(380,575,25,0.5), // Silla de la silla 5 (confuso pero bueno)
			FloatRect(500,530,45,29), // Silla 6
			FloatRect(510,575,25,0.5), // Silla de la silla 6 (confuso pero bueno)
			FloatRect(620,530,110,29), // Silla 7
			FloatRect(635,575,25,0.5), // Silla de la silla 7 (confuso pero bueno)
	};
	
	Clock reloj;
	float velocidad = 250.0f; // Velocidad del jugador
	
	Clock puntaje_reloj; Text puntaje_t;
	Font font; font.loadFromFile("fonts/Monocraft.ttf");
	puntaje_t.setFont(font);
	puntaje_t.setPosition(890, 10);
	puntaje_t.setCharacterSize(35);
	
	while (ventana.isOpen()) {
		float deltaTime = reloj.restart().asSeconds(); // Deltatime se usa para no depender de la cantidad de frames
		// La velocidad es de 250 pixeles por segundo
		
		Event evento;
		while (ventana.pollEvent(evento)) {
			if (evento.type == Event::Closed) {
				ventana.close();
			}
		}

		if (!gameOver) {
			if (Keyboard::isKeyPressed(Keyboard::Escape)) {
				jugador.pararMusica();
				Menu menu(ventana);
				menu.MostrarMenuPrincipal();
			}
			Vector2f desplazamiento(0.0f, 0.0f);
			if (Keyboard::isKeyPressed(Keyboard::A)) {
				desplazamiento.x -= velocidad * deltaTime;
			}
			if (Keyboard::isKeyPressed(Keyboard::D)) {
				desplazamiento.x += velocidad * deltaTime;
			}
			if (Keyboard::isKeyPressed(Keyboard::W)) {
				desplazamiento.y -= velocidad * deltaTime;
			}
			if (Keyboard::isKeyPressed(Keyboard::S)) {
				desplazamiento.y += velocidad * deltaTime;
			}
			jugador.moverPersonita(desplazamiento.x, desplazamiento.y, paredes);
			
			obstaculos.actualizar(deltaTime, Vector2f(1024, 768));
			
			if (obstaculos.verificarColision(jugador.mostrarSkin().getGlobalBounds())) {
				vida.ActualizarVida(false, ventana,jugador); 
			}
			
			if (relojPowerUp.getElapsedTime().asSeconds() >= 1.0f) {
				powerUp.GenerarPowerUp(paredes);
				relojPowerUp.restart(); 
			}
			
			powerUp.verificarColision(jugador.mostrarSkin().getGlobalBounds(), vida,jugador);
			
		}
		
		Time puntaje_tiempo = puntaje_reloj.getElapsedTime();
		int minutos = puntaje_tiempo.asSeconds() / 60; 
		int segundos = static_cast<int>(puntaje_tiempo.asSeconds()) % 60;
		jugador.ModificarPuntaje(minutos*60+segundos);
		std::stringstream ss; 
		ss << setw(2) << setfill('0') << minutos << ":" << std::setw(2) << setfill('0') << segundos;
		puntaje_t.setString(ss.str());
		
		
		ventana.clear();
		ventana.draw(escenario.getBackground());
		powerUp.Dibujar(ventana);
		ventana.draw(jugador.mostrarSkin());
		ventana.draw(puntaje_t);
		ventana.draw(escenario.getGlobo());
		ventana.draw(escenario.getSilla());
		obstaculos.dibujar(ventana); 
		vida.Dibujar(ventana);
		ventana.display();
	}
}

