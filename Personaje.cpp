#include "Personaje.h"

sf::FloatRect Personaje::ObtenerCaja(){
	return m_cajaColision;
}
void Personaje::GuardarPosicion() {
	m_posicionAnterior = m_posicion;
}

void Personaje::RestaurarPosicion() {
	m_posicion = m_posicionAnterior;
	m_sprite.setPosition(m_posicion);
	m_cajaColision.left = m_posicion.x;
	m_cajaColision.top = m_posicion.y;
}
