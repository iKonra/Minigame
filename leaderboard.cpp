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


#include <cstring>
using namespace std;
using namespace sf;

Leaderboard::Leaderboard(RenderWindow &ventana) : ventana(ventana) {
	ventana.setFramerateLimit(60);
	
	if (!textura.loadFromFile("resources/background/scoreboard.jpg")) {
		cerr << "Error loading texture" << endl;
	}
	fondo_menu.setTexture(textura);
	
	texto_leaderboard.setFont(font);
	texto_leaderboard.setString("Scoreboard");
	texto_leaderboard.setCharacterSize(110);
	texto_leaderboard.setFillColor(Color::White);
	texto_leaderboard.setPosition(140, 20);
	texto_leaderboard.setOutlineColor(Color(0,0,0,255));
	texto_leaderboard.setOutlineThickness(3.5);
	
	fondo_menu.setScale(0.8f, 0.8f);
	
	CargarLeaderboard();
	
	leaderboard.resize(aux_leaderboard.size());
	posiciones_y.resize(aux_leaderboard.size(), 800.0f);
	
	font.loadFromFile("fonts/Monocraft.ttf");
	
	for (size_t i = 0; i < leaderboard.size(); i++) {
		leaderboard[i].setFont(font);
		leaderboard[i].setString(to_string(i + 1) + ". " + aux_leaderboard[i].j_nombre + " - " + to_string(aux_leaderboard[i].j_puntaje) + " puntos");
		leaderboard[i].setCharacterSize(30);
		leaderboard[i].setPosition(270, posiciones_y[i]);
	}
}

void Leaderboard::AbrirLeaderboard(RenderWindow &ventana, Menu &menu) {
	float tiempo_acumulado = 0.0f; // Variable para manejar los tiempos de cada entrada
	
	while (ventana.isOpen()) {
		Event evt;
		while (ventana.pollEvent(evt)) {
			if (evt.type == Event::Closed) {
				ventana.close();
			}
		}
		
		tiempo_acumulado += 0.015f;
		
		for (size_t i = 0; i < leaderboard.size(); i++) {
			if (tiempo_acumulado > i * 0.6f) {
				if (posiciones_y[i] > 170 + i * 50) { // Si no llego a la pos final, se sigue moviendo
					posiciones_y[i] -= 30; // Cada iteracion hay una diferencia de 30 pixeles de la pos anterior
					if (posiciones_y[i] < 170 + i * 50) posiciones_y[i] = 170 + i * 50;
				}
				leaderboard[i].setOutlineColor(Color(0,0,0,150));
				leaderboard[i].setOutlineThickness(2);
				leaderboard[i].setPosition(270, posiciones_y[i]);
			}
		}
		
		if (Keyboard::isKeyPressed(Keyboard::Escape)) {
			menu.MostrarMenuPrincipal();
		}
		
		ventana.clear();
		ventana.draw(fondo_menu);
		ventana.draw(texto_leaderboard);
		for (const auto &puntaje : leaderboard) {
			ventana.draw(puntaje);
		}
		ventana.display();
	}
}

void Leaderboard::GuardarLeaderboard() {
	ofstream salida("datos/leaderboard.dat", ios::binary);
	if (!salida) {
		throw runtime_error("No se pudo abrir el archivo para guardar.");
	}
	
	size_t cantidad = aux_leaderboard.size();
	salida.write(reinterpret_cast<char*>(&cantidad), sizeof(cantidad));
	
	for (auto& p : aux_leaderboard) {
		salida.write(reinterpret_cast<char*>(&p), sizeof(Puntajes));
	}
	
	salida.close();
}

void Leaderboard::CargarLeaderboard() {
	ifstream entrada("datos/leaderboard.dat", ios::binary);
	if (!entrada) {
		cerr << "No se encontró leaderboard.dat, se creará nuevo archivo." << endl;
		return;
	}
	
	aux_leaderboard.clear();
	size_t cantidad;
	entrada.read(reinterpret_cast<char*>(&cantidad), sizeof(cantidad));
	
	for (size_t i = 0; i < cantidad; i++) {
		Puntajes p;
		entrada.read(reinterpret_cast<char*>(&p), sizeof(Puntajes));
		aux_leaderboard.push_back(p);
	}
	
	entrada.close();
	sort(aux_leaderboard.begin(), aux_leaderboard.end());
	
	leaderboard.resize(aux_leaderboard.size());
	posiciones_y.resize(aux_leaderboard.size(), 800.0f);
	
	for (size_t i = 0; i < aux_leaderboard.size(); i++) {
		leaderboard[i].setFont(font);
		leaderboard[i].setString(to_string(i + 1) + ". " + aux_leaderboard[i].j_nombre + " - " +
								 to_string(aux_leaderboard[i].j_puntaje) + " puntos");
		leaderboard[i].setCharacterSize(30);
		leaderboard[i].setPosition(270, posiciones_y[i]);
	}
}

void Leaderboard::ActualizarLeaderboard(string nombre, int puntaje) {
	Puntajes aux;
	strncpy(aux.j_nombre, nombre.c_str(), sizeof(aux.j_nombre) - 1);
	aux.j_nombre[sizeof(aux.j_nombre) - 1] = '\0';
	aux.j_puntaje = puntaje;
	
	aux_leaderboard.push_back(aux);
	sort(aux_leaderboard.begin(), aux_leaderboard.end());
	
	if (aux_leaderboard.size() > 10) {
		aux_leaderboard.pop_back();
	}
	
	GuardarLeaderboard();
	CargarLeaderboard();
}

int Leaderboard::verPeorPuntaje() {
	if (aux_leaderboard.empty()) {
		return -1;
	}
	return aux_leaderboard.back().j_puntaje;
}
