#include "menu.h"

int main() {
	
	RenderWindow ventana(VideoMode(1024, 768), "Proyecto Final POO");
	ventana.setFramerateLimit(60);
	
	Menu menu(ventana);
	menu.MostrarMenuPrincipal();
	
	return 0;
}
