#ifndef PERSONAJE_H
#define PERSONAJE_H

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

class Personaje {
public:
	virtual ~Personaje(){}; 
	
	// Métodos obligatorios para los hijos
	virtual void ProcesarEntrada() = 0; 
	virtual void Actualizar() = 0; 
	virtual void Dibujar(sf::RenderWindow &ventana) = 0; 
	
	// Metodos virtuales no puros
	virtual sf::FloatRect ObtenerCaja();
	virtual void GuardarPosicion();
	virtual void RestaurarPosicion();
	
protected:
		sf::Vector2f m_posicion;
		sf::Vector2f m_posicionAnterior;
		sf::Vector2f m_velocidad;
		sf::Sprite m_sprite;
		sf::Texture m_textura; 
		sf::FloatRect m_cajaColision; 
};

#endif // PERSONAJE_H
