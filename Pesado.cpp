#include "Pesado.h"
#include <SFML/Window/Keyboard.hpp>
#include "GestorRecursos.h"

using namespace sf;

Pesado::Pesado(float x, float y) {
	m_posicion = Vector2f(x, y);
	m_velocidad = Vector2f(0.0f, 0.0f);
	m_enElSuelo = false;
	m_saltoPresionadoAntes = false;
	
	m_textura = GestorRecursos::ObtenerTextura("assets/pesado_sprite.png");
	m_sprite.setTexture(m_textura);
	m_sprite.setPosition(m_posicion);
	
	// Caja de colisión basada en el tamaño de la textura
	sf::Vector2u tamano = m_textura.getSize();
	m_cajaColision = FloatRect(m_posicion.x, m_posicion.y, 
							   tamano.x, tamano.y);
}

void Pesado::ProcesarEntrada() {
	m_velocidad.x = 0.0f;
	
	// Controles con Flechitas
	if (Keyboard::isKeyPressed(Keyboard::Left)) {
		m_velocidad.x = -VELOCIDAD_MAXIMA;
	}
	if (Keyboard::isKeyPressed(Keyboard::Right)) {
		m_velocidad.x = VELOCIDAD_MAXIMA;
	}
	
	bool teclaArriba = Keyboard::isKeyPressed(Keyboard::Up);
	
	// Salto simple, verifica si salto antes para evitar el efecto rebote 
	// ya que se procesa mas rapido de lo q el usuario suelta el dedo
	if (teclaArriba and m_saltoPresionadoAntes == false) {
		if (m_enElSuelo) {
			m_velocidad.y = FUERZA_SALTO;
			m_enElSuelo = false;
		}
	}
	m_saltoPresionadoAntes = teclaArriba;
}

void Pesado::Actualizar() {
	if (m_enElSuelo == false) {
		m_velocidad.y += GRAVEDAD;
	}
	
	m_posicion += m_velocidad;
	
	m_sprite.setPosition(m_posicion);
	m_cajaColision.left = m_posicion.x;
	m_cajaColision.top = m_posicion.y;
}

float Pesado::ObtenerAlturaPies() const {
	return m_cajaColision.top + m_cajaColision.height;
}

void Pesado::TocoElSuelo(const float ALTURA_SUELO) {
	m_posicion.y = ALTURA_SUELO - m_cajaColision.height;
	m_velocidad.y = 0.0f;
	m_enElSuelo = true;
}

void Pesado::Dibujar(RenderWindow &ventana) {
	ventana.draw(m_sprite);
}
