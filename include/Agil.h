
#ifndef AGIL_H
#define AGIL_H

#include "Personaje.h"
#include <SFML/Graphics.hpp>


class Agil : public Personaje{
public:
	Agil(float x, float y);
	~Agil() override {};
	
	void ProcesarEntrada() override;
	void Actualizar() override;
	void Dibujar(sf::RenderWindow &ventana) override;
	
private:
	// Constantes de juego especificas de Agil
	const float VELOCIDAD_MAXIMA = 10.0f;
};
#endif // AGIL_H
