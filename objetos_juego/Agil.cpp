#include "Agil.h"
#include <SFML/Window/Keyboard.hpp>
#include "GestorRecursos.h"
using namespace sf;

Agil::Agil(float x, float y) {
	m_posicion = Vector2f(x, y);
	m_velocidad = Vector2f(0.0f, 0.0f);
	
	m_textura = GestorRecursos::ObtenerTextura("recursos/texturas/Fighter/idle.png");
	m_sprite.setTexture(m_textura);
	
	sf::Vector2u tamanoTextura = m_textura.getSize();
	m_anchoFrame = tamanoTextura.x / 19;  // Divide por 19 columnas 
	m_altoFrame = tamanoTextura.y / 4;    // Divide por 4 filas
	
	// Configura el rect de textura para mostrar al principio el primer frame
	m_sprite.setTextureRect(IntRect(0, 0, m_anchoFrame, m_altoFrame));
	
	// Ajusta el tamano de la caja
	m_anchoCaja = m_anchoFrame * 0.32;
	m_altoCaja = m_altoFrame * 0.45;
	
	// Centra la caja calculando el espacio libre
	m_offsetX = (m_anchoFrame - m_anchoCaja) /2; 
	m_offsetY = (m_altoFrame - m_altoCaja) /2;
	m_cajaColision = FloatRect(m_posicion.x + m_offsetX, m_posicion.y + m_offsetY, m_anchoCaja, m_altoCaja);
}

void Agil::ProcesarEntrada() {
	m_velocidad = Vector2f(0.0f, 0.0f);
	
	// Movimiento y cambio de sprite
	if (Keyboard::isKeyPressed(Keyboard::A)){ 
		m_velocidad.x = -VELOCIDAD_MAXIMA;
		m_sprite.setTextureRect(IntRect(0, m_altoFrame * 3, m_anchoFrame, m_altoFrame));
	}
	if (Keyboard::isKeyPressed(Keyboard::S)) {
		m_velocidad.y = VELOCIDAD_MAXIMA;
		m_sprite.setTextureRect(IntRect(0, m_altoFrame * 2, m_anchoFrame, m_altoFrame));
	}
	if (Keyboard::isKeyPressed(Keyboard::D)){
		m_velocidad.x = VELOCIDAD_MAXIMA;
		m_sprite.setTextureRect(IntRect(0, m_altoFrame, m_anchoFrame, m_altoFrame));
	}
	
	if (Keyboard::isKeyPressed(Keyboard::W)) {
		m_velocidad.y = -VELOCIDAD_MAXIMA;
		m_sprite.setTextureRect(IntRect(0, 0, m_anchoFrame, m_altoFrame));
	}
	
}

void Agil::Actualizar() {
	// Por cada frame (Cada iteracion de actualizar) se ajusta la posicion segun la velocidad
	m_posicion += m_velocidad;
	
	// Actualiza la posición del Sprite 
	m_sprite.setPosition(m_posicion);
	
	// Actualiza la posicion de la caja manteniendo el desplazamiento para que siga centrada
	m_cajaColision.left = m_posicion.x + m_offsetX;
	m_cajaColision.top = m_posicion.y + m_offsetY;
}


void Agil::Dibujar(RenderWindow &ventana) {
	ventana.draw(m_sprite);
}
