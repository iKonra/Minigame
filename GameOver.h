#ifndef GAMEOVER_H
#define GAMEOVER_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

using namespace sf;
using namespace std;

class GameOverScreen {
private:
	vector<sf::Texture> frames;    
	Sprite sprite;                 
	RectangleShape overlay;      
	Clock clock;                  
	float duracion_frame;              
	size_t actual_frame;       
	
public:
	GameOverScreen(float duracion = 100.0f);
	bool cargarFrames();
	void show(RenderWindow& window,int puntaje);
};

#endif 
