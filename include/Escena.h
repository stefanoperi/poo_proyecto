#ifndef SCENE_H
#define SCENE_H

#include <SFML/Graphics/RenderWindow.hpp> 
#include <SFML/Window/Event.hpp> 

class Juego; // Declaración adelantada de la clase Juego

class Escena {
public:
	Escena() = default; 
	virtual ~Escena(){}
	
	virtual void Actualizar(Juego &j) = 0;
	virtual void Dibujar(sf::RenderWindow &ventana) = 0;
	virtual void ProcesarEventos(Juego &j, sf::Event &e) = 0;

};
#endif
