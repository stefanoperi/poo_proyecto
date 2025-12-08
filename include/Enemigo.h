#ifndef ENEMIGO_H
#define ENEMIGO_H

#include "Personaje.h"
#include <SFML/Graphics.hpp>

using namespace sf;

class Enemigo : public Personaje {
public:
	Enemigo(float x, float y, Personaje* objetivo);
	~Enemigo() override {};
	
	void ProcesarEntrada() override;
	void Actualizar() override;
	void Dibujar(RenderWindow &ventana) override;
private:
	const float VELOCIDAD_MAXIMA = 1.0f; 
	Personaje* m_objetivo;
};

#endif 
