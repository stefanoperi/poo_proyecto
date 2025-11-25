#ifndef JUEGO_H
#define JUEGO_H
#include <SFML/Graphics.hpp>
#include  "Escena.h"
using namespace sf;
class Juego{
public:
	Juego();
	void Jugar();
	void ProcesarEventos();
	void Actualizar();
	void Dibujar();
	void PonerEscena(Escena *nueva_escena);
	
private:
	RenderWindow m_ventana;
	Escena *m_escena;
	Escena *m_nueva_escena = nullptr;
};
#endif
