#ifndef SCENE_H
#define SCENE_H
#include <SFML/Graphics/RenderWindow.hpp>
class Juego;
using namespace sf;

class Escena{
public:
	Escena(){};
	virtual ~Escena(){}
	virtual void Actualizar(Juego &j) = 0;
	virtual void Dibujar(RenderWindow &ventana) = 0;
	virtual void ProcesarEventos(Juego &j, Event &e) = 0;
private:
};
#endif
