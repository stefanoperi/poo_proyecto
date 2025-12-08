#ifndef ENEMIGO_H
#define ENEMIGO_H

#include "Personaje.h"
#include <SFML/Graphics.hpp>


class Enemigo : public Personaje {
public:
	Enemigo(float x, float y, Personaje* objetivo);
	~Enemigo() override {};
	
	void ProcesarEntrada() override;
	void Actualizar() override;
	void Dibujar(sf::RenderWindow &ventana) override;
	
	bool CercaDeJugador();
	void Atacar();
	void Perseguir();
private:
	const float VELOCIDAD_MAXIMA = 2.0f;
	int m_frameAtaque;    // Qué dibujito de la tira estamos mostrando (0 al 4)
	int m_timerAnimacion; // Un contador para que la animación no vaya ultra rápida
	bool m_estaAtacando; // Para saber si tenemos que cambiar la textura
	Personaje* m_objetivo;
};

#endif 
