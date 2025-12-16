#include "Personaje.h"
#include <cmath>

sf::FloatRect Personaje::ObtenerCaja(){
	return m_cajaColision;
}

void Personaje::GuardarPosicion() {
	m_posicionAnterior = m_posicion;
}

void Personaje::RestaurarPosicion() {
	m_posicion = m_posicionAnterior;
	m_sprite.setPosition(m_posicion);
	m_cajaColision.left = m_posicion.x + m_offsetX;
	m_cajaColision.top = m_posicion.y + m_offsetY; 
}
bool Personaje::EstaVivo() {
	return m_vida>0;
}
bool Personaje::ResolverColision(Personaje &otro) {
	sf::FloatRect r1 = this->ObtenerCaja();
	sf::FloatRect r2 = otro.ObtenerCaja();

	if (r1.intersects(r2) == false) {
		return false; 
	}
	
	// Centros de los rectángulos
	float r1CentroX = r1.left + r1.width / 2.0f;
	float r1CentroY = r1.top + r1.height / 2.0f;
	float r2CentroX = r2.left + r2.width / 2.0f;
	float r2CentroY = r2.top + r2.height / 2.0f;
	
	// Distancia entre los centros
	float deltaX = r1CentroX - r2CentroX;
	float deltaY = r1CentroY - r2CentroY;
	
	// Distancia mínima sin colisión
	float minDistX = (r1.width / 2.0f) + (r2.width / 2.0f);
	float minDistY = (r1.height / 2.0f) + (r2.height / 2.0f);
	
	// Cantidad de interseccion (cuánto se metió uno dentro del otro)
	float interseccX = minDistX - std::abs(deltaX);
	float interseccY = minDistY - std::abs(deltaY);
	 
	// Empuja en el eje donde haya menos intersección 
	if (interseccX < interseccY) {
		// El choque es horizontal 
		if (deltaX > 0.0f) {
			m_posicion.x += interseccX;
		} else {
			m_posicion.x -= interseccX;
		}
	} else {
		// El choque es vertical 
		if (deltaY > 0.0f) {
			m_posicion.y += interseccY;
		} else {
			m_posicion.y -= interseccY;
		}
	}
	
	// Actualiza caja y posicion
	m_sprite.setPosition(m_posicion);
	m_cajaColision.left = m_posicion.x + m_offsetX;
	m_cajaColision.top = m_posicion.y + m_offsetY;
	
	return true; // Hubo choque y se resolvió
}

