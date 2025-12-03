#ifndef PESADO_H
#define PESADO_H

#include "Personaje.h"
#include <SFML/Graphics.hpp>

using namespace sf;

class Pesado : public Personaje {
public:
	Pesado(float x, float y);
	~Pesado() override {};
	
	void ProcesarEntrada() override;
	void Actualizar() override;

	void Dibujar(RenderWindow &ventana) override;
	
private:
	const float VELOCIDAD_MAXIMA = 15.0f; 
};

#endif // PESADO_H
