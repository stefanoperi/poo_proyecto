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
	
	// Getters útiles
	virtual sf::Vector2f ObtenerPosicion() const { return m_posicion; }
	virtual sf::FloatRect ObtenerCaja() const { return m_cajaColision; }
	
protected:
		// Variables accesibles por Agil y Pesado
		sf::Vector2f m_posicion;
		sf::Vector2f m_velocidad;
		sf::Sprite m_sprite;
		sf::Texture m_textura; // Nota: Idealmente usarías punteros, pero esto funciona por ahora
		sf::FloatRect m_cajaColision; 
};

#endif // PERSONAJE_H
