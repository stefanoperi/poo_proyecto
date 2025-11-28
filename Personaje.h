#ifndef PERSONAJE_H
#define PERSONAJE_H

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

class Personaje {
public:
	
	virtual ~Personaje(){}; 
	
	// Lógica del juego
	virtual void ProcesarEntrada() = 0; 
	virtual void Actualizar() = 0; 
	
	// Colisiones y Propiedades
	virtual float ObtenerAlturaPies() const = 0; 
	virtual void TocoElSuelo(const float ALTURA_SUELO) = 0;
	
	// Renderizado
	virtual void Dibujar(sf::RenderWindow &ventana) = 0; 
	
protected:
	sf::Vector2f m_posicion;
	sf::Vector2f m_velocidad;
	sf::Sprite m_sprite;
	sf::Texture m_textura;
	sf::FloatRect m_cajaColision; 
	
	bool m_enElSuelo;
};

#endif // PERSONAJE_H
