#include "Agil.h"
#include <SFML/Window/Keyboard.hpp>
#include "GestorRecursos.h"
using namespace sf;

Agil::Agil(float x, float y) {
	m_posicion = Vector2f(x, y);
	m_velocidad = Vector2f(0.0f, 0.0f);
	
	m_textura = GestorRecursos::ObtenerTextura("recursos/texturas/reposo.png");
	m_sprite.setTexture(m_textura);
	// Inicialización de la Caja de Colisión con el tamaño de cuando esta parado el personaje
	sf::Vector2u tamano_de_pie = m_textura.getSize();
	m_cajaColision = FloatRect(m_posicion.x, m_posicion.y, tamano_de_pie.x, tamano_de_pie.y);
}

void Agil::ProcesarEntrada() {
	m_velocidad = Vector2f(0.0f, 0.0f);
	
	// Izquierda / Derecha
	if (Keyboard::isKeyPressed(Keyboard::A)) m_velocidad.x = -VELOCIDAD_MAXIMA;
	if (Keyboard::isKeyPressed(Keyboard::D)) m_velocidad.x = VELOCIDAD_MAXIMA;
	
	//  Arriba / Abajo 
	if (Keyboard::isKeyPressed(Keyboard::W)) m_velocidad.y = -VELOCIDAD_MAXIMA;
	if (Keyboard::isKeyPressed(Keyboard::S)) m_velocidad.y = VELOCIDAD_MAXIMA;
}

void Agil::Actualizar() {
	// Por cada frame (Cada iteracion de actualizar) se ajusta la posicion segun la velocidad
	m_posicion += m_velocidad;
	
	// Actualizar la posición del Sprite y la Caja de Colisión
	m_sprite.setPosition(m_posicion);
	
	m_cajaColision.left = m_posicion.x;
	m_cajaColision.top = m_posicion.y;
}


void Agil::Dibujar(RenderWindow &ventana) {
	ventana.draw(m_sprite);
}
