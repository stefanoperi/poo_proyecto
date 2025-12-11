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
	void RecibirAtaque(int cantidad) override;
	
	bool CercaDeJugador();
	void Atacar();
	void Perseguir();
private:
	const float VELOCIDAD_MAXIMA = 2.0f;
	int m_frameAtaque;    
	int m_timerAnimacion; 
	bool m_estaAtacando; 
	Personaje* m_objetivo;
	bool m_golpeConectado;
	sf::Texture m_texturaMuerte; 
	bool m_estaMuriendo;         
	int m_frameMuerte;         
	float m_timerMuerte;      
};

#endif 
