#include "gameover.h"
#include "game.h"
#include "leaderboard.h"
#include "menu.h"
#include <iostream>
#include "vidas.h"
#include <SFML/Window/Keyboard.hpp>

using namespace std;
using namespace sf;

GameOverScreen::GameOverScreen(float duracion) : duracion_frame(duracion), actual_frame(0) {
	overlay.setSize(Vector2f(1024, 768)); // Tamaño de la pantalla
	overlay.setFillColor(Color(0, 0, 0, 180)); // Fondo de Game Over
	cargarFrames();
}

bool GameOverScreen::cargarFrames() {
	for (int i = 1; i <= 20; ++i) {
		Texture frame;
		if (!frame.loadFromFile("resources/gameover/frame-" + to_string(i) + ".png")) {
			cout << "Error al cargar frame: " << i << endl;
			return false;
		}
		frames.push_back(frame);
	}
	return true;
}

void GameOverScreen::show(RenderWindow& window, int puntaje) {
	clock.restart();
	actual_frame = 0;
	
	// Cargar la fuente
	Font font;
	if (!font.loadFromFile("fonts/Monocraft.ttf")) {
		cout << "Error al cargar la fuente" << endl;
		return;
	}
	
	// Configurar textos
	Text texto_puntaje("Puntaje: " + to_string(puntaje), font, 30);
	texto_puntaje.setFillColor(Color::White);
	texto_puntaje.setPosition((window.getSize().x - texto_puntaje.getLocalBounds().width) / 2.0f, 400); 
	
	Text texto_extra("", font, 20);
	texto_extra.setFillColor(Color::Yellow);
	
	String nombreJugador;
	Text texto_nombre("Tu nombre: ", font, 20);
	texto_nombre.setFillColor(Color::White);
	
	Text mensaje_confirmar("", font, 20);
	mensaje_confirmar.setFillColor(Color::White);
	
	Menu menu(window);

	Leaderboard lb(window);
	int peorPuntaje = lb.verPeorPuntaje();
	
	bool nuevo_record = puntaje > peorPuntaje;
	if (nuevo_record) {
		texto_extra.setString("¡Nuevo récord!");
		texto_extra.setPosition((window.getSize().x - texto_extra.getLocalBounds().width) / 2.0f, 450);
		
		texto_nombre.setPosition((window.getSize().x - texto_nombre.getLocalBounds().width) / 2.0f, 500);
		mensaje_confirmar.setString("Presiona LShift para confirmar");
	} else {
		mensaje_confirmar.setString("Presiona Space para continuar");
	}
	mensaje_confirmar.setPosition((window.getSize().x - mensaje_confirmar.getLocalBounds().width) / 2.0f, 550);
	
	while (window.isOpen()) {
		Event event;
		while (window.pollEvent(event)) {
			if (event.type == Event::Closed) {
				window.close();
				return;
			}
			
			// Manejo de entrada de texto
			if (nuevo_record) {
				if (event.type == Event::TextEntered) {
					if (event.text.unicode == '\b' && !nombreJugador.isEmpty()) {
						nombreJugador = nombreJugador.substring(0, nombreJugador.getSize() - 1); // Si usan un espacio se lo saco
					} else if (event.text.unicode >= 32 && event.text.unicode < 127) {
						nombreJugador += event.text.unicode;
						
					}
					texto_nombre.setString("Tu nombre: " + nombreJugador);
					texto_nombre.setPosition((window.getSize().x - texto_nombre.getLocalBounds().width) / 2.0f, 500);
					
				} else if (event.type == Event::KeyPressed && event.key.code == Keyboard::LShift) {
					if (!nombreJugador.isEmpty()) {
						lb.ActualizarLeaderboard(nombreJugador.toAnsiString(), puntaje);
						Empezar(window);
						return;
					} else {
						texto_extra.setString("¡Escribe tu nombre!");
						texto_extra.setPosition((window.getSize().x - texto_extra.getLocalBounds().width) / 2.0f, 450);
					}
				}
			} else if (event.type == Event::KeyPressed && event.key.code == Keyboard::Space) {
				Empezar(window);
				return;
			}
		}
		
		// Animacion gif
		if (clock.getElapsedTime().asMilliseconds() > duracion_frame) {
			actual_frame = (actual_frame + 1) % frames.size();
			sprite.setTexture(frames[actual_frame]);
			clock.restart();
		}
		
		// Gif GameOver posicion
		FloatRect tamanio_gif = sprite.getGlobalBounds();
		sprite.setPosition((window.getSize().x - tamanio_gif.width) / 2,(window.getSize().y - tamanio_gif.height) / 2 - 200);
		
		
		// Dibujar
		window.clear();
		window.draw(overlay);
		window.draw(sprite);
		window.draw(texto_puntaje);
		if (nuevo_record) {
			window.draw(texto_extra);
			window.draw(texto_nombre);
		}
		window.draw(mensaje_confirmar);
		window.display();
	}
}
