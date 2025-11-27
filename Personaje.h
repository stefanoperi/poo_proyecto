#ifndef PERSONAJE_H
#define PERSONAJE_H

#include <SFML/Graphics.hpp>
// #include "GestorRecursos.h" // <-- A veces ayuda incluirlo aquí, o solo en el cpp

class Personaje {
protected:
	sf::Sprite m_sprite;
	
	// CAMBIO CLAVE: Antes era float, ahora es Vector2f (X e Y)
	sf::Vector2f m_velocidad; 
	
	bool m_ensuelo;
	
	// CONSTANTES NUEVAS (Que el compilador te reclamaba que faltaban)
	const float VELOCIDAD_MOVIMIENTO = 3.0f; 
	const float VELOCIDAD_CAIDA_FRAME = 0.5f; 
	const float VELOCIDAD_SALTO_FRAME = -10.0f;
	
public:
	Personaje(float posX, float posY); 
	
	// MÉTODOS NUEVOS (Que el compilador decía que no existían)
	void ProcesarEntrada(); 
	
	void Actualizar();      
	void Dibujar(sf::RenderWindow &ventana); 
	
	sf::FloatRect ObtenerLimites() const { return m_sprite.getGlobalBounds(); } 
	void TocarSuelo(float alturaSuelo);
};

#endif
