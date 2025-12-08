#include "Enemigo.h"
#include <SFML/Window/Keyboard.hpp>
#include "GestorRecursos.h"
#include <cmath>
using namespace sf;

Enemigo::Enemigo(float x, float y, Personaje* objetivo) {
	m_posicion = Vector2f(x, y);
	m_velocidad = Vector2f(0.0f, 0.0f);
	m_objetivo = objetivo;
	
	m_textura = GestorRecursos::ObtenerTextura("recursos/texturas/Skeleton/Idle/Idle_F.png");
	m_sprite.setTexture(m_textura);
	
	sf::Vector2u tamanoTextura = m_textura.getSize();
	m_anchoFrame = tamanoTextura.x / 8;  // Divide por 8 columnas 
	m_altoFrame = tamanoTextura.y;    // 1 sola fila
	
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

void Enemigo::ProcesarEntrada() {
}

void Enemigo::Actualizar() {
	auto cajaObjetivo = m_objetivo->ObtenerCaja();
	// Obtiene la posición de la esquina superior izquierda 
	float centroX = cajaObjetivo.left;
	float centroY = cajaObjetivo.top;
	
	// Suma la mitad del ancho y alto para encontrar el punto central
	centroX += cajaObjetivo.width / 2.0f;
	centroY += cajaObjetivo.height / 2.0f;
	Vector2f posicionObjetivo = {centroX, centroY};
	
	m_velocidad = Vector2f(2.0f, 2.0f);
	float deltaX = fabs(centroX - m_posicion.x);
	// Si esta cerca evita sobrecorregir y solo corrije cuando esta a la izquierda o arriba
	if (deltaX < m_velocidad.x){
		m_velocidad.x = 0;
	}else if (m_posicion.x > centroX){
		m_velocidad.x = -1 * m_velocidad.x;
	}
	
	float deltaY = fabs(centroY - m_posicion.y);
	if (deltaY < m_velocidad.y){
		m_velocidad.y = 0;
	}else if (m_posicion.y > centroY){
		m_velocidad.y = -1 * m_velocidad.y;
	}
	
	
	m_posicion += m_velocidad;
	m_sprite.setPosition(m_posicion);
	
	// Actualizar caja de colisión
	m_cajaColision.left = m_posicion.x + m_offsetX;
	m_cajaColision.top = m_posicion.y + m_offsetY;
}


void Enemigo::Dibujar(RenderWindow &ventana) {
	ventana.draw(m_sprite);
	
	
}
