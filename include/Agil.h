#ifndef AGIL_H
#define AGIL_H

#include "Personaje.h"
#include <SFML/Graphics.hpp>

class Agil : public Personaje {
public:
	Agil(float x, float y);
	~Agil() override {};
	
	void ProcesarEntrada() override;
	void Actualizar() override;
	void Dibujar(sf::RenderWindow &ventana) override;
	void RecibirAtaque(int cantidad) override;
	
	// Métodos de combate
	sf::FloatRect ObtenerCajaAtaque();
	void Atacar();
	int ObtenerVida();
	std::vector<BolaEnergia>* ObtenerBolas();
private:
	const float VELOCIDAD_MAXIMA = 5.0f; 
	int m_timerCooldown;
	// Variables de estado
	bool m_atacando;
	bool m_enMovimiento;
	int m_direccion;      // 0: Abajo, 1: Izq, 2: Der, 3: Arriba
	
	// Variables de animación
	int m_frameAtaque;
	int m_timerAnimacion;
	int m_frameCaminar;  
	
	// Texturas
	sf::Texture m_texturaCorrer;
	sf::Texture m_texturaAtacar;
	sf::Texture m_texturaIdle;
	
	sf::Texture m_texturaBola; 
	std::vector<BolaEnergia> m_bolas;
};

#endif // AGIL_H
