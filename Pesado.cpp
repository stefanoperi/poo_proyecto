#include "Pesado.h"
#include <SFML/Window/Keyboard.hpp>
#include "GestorRecursos.h"

using namespace sf;

Pesado::Pesado(float x, float y) {
	m_posicion = Vector2f(x, y);
	m_velocidad = Vector2f(0.0f, 0.0f);
	
	m_textura = GestorRecursos::ObtenerTextura("assets/pesado_sprite.png");
	m_sprite.setTexture(m_textura);
	m_sprite.setPosition(m_posicion);
	
	// Caja de colisión basada en el tamaño de la textura
	sf::Vector2u tamano = m_textura.getSize();
	m_cajaColision = FloatRect(m_posicion.x, m_posicion.y,tamano.x, tamano.y);
}

void Pesado::ProcesarEntrada() {
	m_velocidad = Vector2f(0.0f, 0.0f);
	
	if (Keyboard::isKeyPressed(Keyboard::Left)) m_velocidad.x = -VELOCIDAD_MAXIMA;
	if (Keyboard::isKeyPressed(Keyboard::Right)) m_velocidad.x = VELOCIDAD_MAXIMA;
	
	if (Keyboard::isKeyPressed(Keyboard::Up)) m_velocidad.y = -VELOCIDAD_MAXIMA;
	if (Keyboard::isKeyPressed(Keyboard::Down)) m_velocidad.y = VELOCIDAD_MAXIMA;
}
void Pesado::Actualizar() {
	// 1. Movemos la posición lógica (La caja de colisión)
	m_posicion += m_velocidad;
	
	// 2. Sincronizamos la caja
	m_cajaColision.left = m_posicion.x;
	m_cajaColision.top = m_posicion.y;
	
	// 3. Ajuste Visual (OFFSET)
	// El sprite es 96x80, la caja es 30x15. Centramos y subimos el dibujo.
	float offsetX = 33.0f; // (96 - 30) / 2
	float offsetY = 65.0f; // (80 - 15)
	
	m_sprite.setPosition(m_posicion.x - offsetX, m_posicion.y - offsetY);
}



void Pesado::Dibujar(RenderWindow &ventana) {
	ventana.draw(m_sprite);
}
