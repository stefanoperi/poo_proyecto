#ifndef PERSONAJE_H
#define PERSONAJE_H

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

class Personaje {
public:
	virtual ~Personaje(){}; 
	
	// Metodos obligatorios para los hijos
	virtual void ProcesarEntrada() = 0; 
	virtual void Actualizar() = 0;	
	virtual void Dibujar(sf::RenderWindow &ventana) = 0; 
	virtual void RecibirAtaque(int cantidad) = 0;
	
	sf::FloatRect ObtenerCaja();
	void GuardarPosicion();
	void RestaurarPosicion();
	bool EstaVivo();

	bool ResolverColision(Personaje &otro);

protected:
	sf::Vector2f m_posicion;
	sf::Vector2f m_posicionAnterior;
	sf::Vector2f m_velocidad;
	sf::Sprite m_sprite;
	sf::Texture m_textura; 
	sf::FloatRect m_cajaColision; 
	int m_vida;
	int m_timerInvulnerabilidad; //Para que no reciba daño en cada frame consecutivo
	
	// Tamano de cada estado del personaje
	float m_anchoFrame, m_altoFrame, m_altoCaja, m_anchoCaja;
	float m_offsetX = 0;
	float m_offsetY = 0;
};

#endif // PERSONAJE_H
