#ifndef PERSONAJE_H
#define PERSONAJE_H
#include <SFML/Graphics.hpp>
class Personaje{
protected:
	sf::Sprite m_sprite;
	sf::Texture m_textura;
	float m_velocidad;
	float m_velocidadsalto;
	bool m_ensuelo;
	const float GRAVEDAD = 0.5f; 
	const float FUERZA_SALTO = -10.0f;// Negativo porque Y aumenta hacia abajo
public:
	Personaje(float posX, float posY); 
	
	// MÉTODOS DEL MOTOR	
	void Actualizar(); // Aplica físicas y movimiento (llamado por Juego::Actualizar)
	void Dibujar(sf::RenderWindow &ventana); // Dibuja el sprite (llamado por Juego::Dibujar)
	
	// Devuelve el área rectangular del personaje para chequear colisiones 
	sf::FloatRect ObtenerLimites() { return m_sprite.getGlobalBounds(); } 
	
	// Corrige la posición del personaje si choca desde arriba con el suelo
	void TocarSuelo(float alturaSuelo);
};
#endif
