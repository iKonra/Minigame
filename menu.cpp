#include "menu.h"
#include "game.h"
#include <iostream>
#include <SFML/Graphics/Rect.hpp>
#include <fstream>
#include <string>
#include <cmath>
#include <algorithm>
#include <SFML/Audio/SoundBuffer.hpp>
#include <SFML/Audio/Sound.hpp>
#include <SFML/Audio/Music.hpp>


using namespace std;
using namespace sf;

Menu::Menu(RenderWindow &ventana) : ventana(ventana) {
	ventana.setFramerateLimit(60);
	
	if (!musica_menu.openFromFile("resources/sounds/menu.wav")) {
		std::cerr << "No se pudo cargar el archivo de audio\n";
	}
	musica_menu.setLoop(true); musica_menu.setVolume(15); 
	
	efecto_temp.loadFromFile("resources/sounds/test.wav");
	efecto_eleccion.setVolume(20);
	efecto_eleccion.setBuffer(efecto_temp);
	
	
	if (!textura.loadFromFile("resources/background/scoreboard.jpg")) {
		std::cerr << "Error loading texture" << std::endl;
	}
	fondo_menu.setTexture(textura);
	
	font.loadFromFile("fonts/Monocraft.ttf");
	font_top.loadFromFile("fonts/Michelin Bold.ttf");
	texto_menu_play.setFont(font);
	texto_menu_leaderboard.setFont(font);
	texto_menu.setFont(font_top);

	
	texto_menu.setString("Menu Principal");
	texto_menu.setCharacterSize(110);
	texto_menu.setFillColor(Color::White);
	texto_menu.setPosition(130, 20);
	texto_menu.setOutlineColor(sf::Color(0,0,0,255));
	texto_menu.setOutlineThickness(3.5);
	
	texto_menu_play.setString("Play");
	texto_menu_play.setCharacterSize(40);
	texto_menu_play.setStyle(sf::Text::Bold);
	texto_menu_play.setOutlineColor(Color(0,0,0,180));
	texto_menu_play.setOutlineThickness(2);
	texto_menu_play.setFillColor(Color::White);
	texto_menu_play.setPosition(430, 200);
	
	texto_menu_leaderboard.setString("Leaderboard");
	texto_menu_leaderboard.setCharacterSize(40);
	texto_menu_leaderboard.setStyle(Text::Regular);
	texto_menu_leaderboard.setFillColor(Color::White);
	texto_menu_leaderboard.setPosition(350, 300);
	
	fondo_menu.setScale(0.8f, 0.8f);
	
	

}
void Menu::MostrarMenuPrincipal() {
	
	if (musica_menu.getStatus() != Music::Playing) {
		musica_menu.play();
	}
	
	float tiempo_acumulado = 0.0f;
	Text ayuda;
	ayuda.setFont(font);
	
	ayuda.setString("Presiona espacio para elegir la opcion");
	ayuda.setCharacterSize(20);
	ayuda.setStyle(sf::Text::Italic);
	ayuda.setFillColor(Color::White);
	ayuda.setOutlineColor(sf::Color(0,0,0,100));
	ayuda.setOutlineThickness(1);
	ayuda.setPosition(250, 500);
	
	SoundBuffer buffer;
	buffer.loadFromFile("resources/sounds/eleccion.wav");
	
	sf::Sound sound;
	sound.setVolume(20);
	sound.setBuffer(buffer);
	
	
	
	
	while (ventana.isOpen()) {
		Event evt;
		while (ventana.pollEvent(evt)) {
			if (evt.type == Event::Closed) {
				ventana.close();
			}
			
			if (evt.type == Event::KeyPressed) {
				if (evt.key.code == Keyboard::Down) {
						if(Opcion_actual != 1) { 
							sound.play(); 
						Opcion_actual = 1;
						texto_menu_play.setStyle(sf::Text::Regular); texto_menu_play.setOutlineThickness(0); texto_menu_leaderboard.setStyle(sf::Text::Bold); texto_menu_leaderboard.setOutlineThickness(2); texto_menu_leaderboard.setOutlineColor(sf::Color(0,0,0,180));
						}
					
				} else if (evt.key.code == Keyboard::Up) {
					if(Opcion_actual != 0) { 
						sound.play(); 
						Opcion_actual = 0;
						texto_menu_play.setStyle(sf::Text::Bold);texto_menu_leaderboard.setStyle(sf::Text::Regular); texto_menu_leaderboard.setOutlineThickness(0); texto_menu_play.setOutlineThickness(2);
					}

				} else if (evt.key.code == Keyboard::Space) {
					if (Opcion_actual == 0) {
						efecto_eleccion.play();
						
						musica_menu.stop();
							
						
						Empezar(ventana); 
					} else if (Opcion_actual == 1) {
						efecto_eleccion.play();
						Leaderboard lb(ventana);
						lb.AbrirLeaderboard(ventana, *this); 
					}
				}
			}
		}
		
		tiempo_acumulado += 0.025f; 
		
		
		
		ventana.clear();
		ventana.draw(fondo_menu);
		ventana.draw(texto_menu);
		ventana.draw(texto_menu_play);
		ventana.draw(texto_menu_leaderboard);
		
		// Valores random que quedaban bien para el efecto como que titila
		if (tiempo_acumulado > 1) { 
			ventana.draw(ayuda);
		}
		if(tiempo_acumulado > 2.75) {
			tiempo_acumulado = 0.0f;
		}
		// ***************************************************************
		ventana.display();
	}
}


