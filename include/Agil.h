
#ifndef AGIL_H
#define AGIL_H

#include "Personaje.h"
#include <SFML/Graphics.hpp>

using namespace sf;
class Agil : public Personaje{
public:
	Agil(float x, float y);
	~Agil() override {};
	
	void ProcesarEntrada() override;
	void Actualizar() override;
	void Dibujar(RenderWindow &ventana) override;

private:
	// Constantes de juego específicas de Agil
	const float VELOCIDAD_MAXIMA = 15.0f;
};
#endif // AGIL_H
