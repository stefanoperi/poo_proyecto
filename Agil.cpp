#include "Agil.h"
#include <SFML/Window/Keyboard.hpp>
#include "GestorRecursos.h"
using namespace sf;

Agil::Agil(float x, float y) : m_puedeDobleSalto(true) {
	m_posicion = Vector2f(x, y);
	m_velocidad = Vector2f(0.0f, 0.0f);
	m_enElSuelo = false; 
	m_saltoPresionadoAntes = false;
	m_puedeDobleSalto = true; 
	
	m_textura = GestorRecursos::ObtenerTextura("assets/agil_sprite.png");
	m_sprite.setTexture(m_textura);
	m_sprite.setPosition(m_posicion);
	
	// Inicialización de la Caja de Colisión con el tamaño de cuando esta parado el personaje
	sf::Vector2u tamano_de_pie = m_textura.getSize();
	m_cajaColision = FloatRect(m_posicion.x, m_posicion.y, 
							   tamano_de_pie.x, tamano_de_pie.y);
}


void Agil::ProcesarEntrada() {
	m_velocidad.x = 0.0f;
	
	// Movimiento Horizontal
	if (Keyboard::isKeyPressed(Keyboard::A)) {
		m_velocidad.x = -VELOCIDAD_MAXIMA;
	}
	if (Keyboard::isKeyPressed(Keyboard::D)) {
		m_velocidad.x = VELOCIDAD_MAXIMA;
	}
	
	bool espacioPresionado = Keyboard::isKeyPressed(Keyboard::Space);
	
	if (espacioPresionado and m_saltoPresionadoAntes== false) { 
		// Salto Inicial 
		if (m_enElSuelo) {
			m_velocidad.y = FUERZA_SALTO;
			m_enElSuelo = false;
			m_puedeDobleSalto = true; 
		} 
		// Doble Salto (Solo si está habilitado y en el aire)
		else if (m_puedeDobleSalto) {
			m_velocidad.y = FUERZA_SALTO * 0.7f; // Salto menor
			m_puedeDobleSalto = false; // Consume el doble salto
		}
	}
	// Esto obliga al jugador a soltar la tecla para volver a ejecutar el 'if' principal.
	m_saltoPresionadoAntes = espacioPresionado;
}


void Agil::Actualizar() { 
	// Aplicar Gravedad
	if (m_enElSuelo == false) {
		m_velocidad.y += GRAVEDAD;
	}
	
	// Por cada frame (Cada iteracion de actualizar) se ajusta la posicion segun la velocidad
	m_posicion += m_velocidad;
	
	// Actualizar la posición del Sprite y la Caja de Colisión
	m_sprite.setPosition(m_posicion);
	m_cajaColision.left = m_posicion.x;
	m_cajaColision.top = m_posicion.y;
}

float Agil::ObtenerAlturaPies() const {	
	// Suma la posicion de la esquina superior y la altura total para obtener la posicion de la esquina inferior 
	return m_cajaColision.top + m_cajaColision.height;
}

void Agil::TocoElSuelo(const float ALTURA_SUELO) {
	// Corrección de posición
	m_posicion.y = ALTURA_SUELO - m_cajaColision.height;
	
	// Frenado y reset de estados
	m_velocidad.y = 0.0f;
	m_enElSuelo = true;
	m_puedeDobleSalto = false;
}

void Agil::Dibujar(RenderWindow &ventana) {
	ventana.draw(m_sprite);
}
