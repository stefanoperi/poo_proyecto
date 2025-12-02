#include "Agil.h"
#include <SFML/Window/Keyboard.hpp>
#include "GestorRecursos.h"
using namespace sf;

Agil::Agil(float x, float y) {
	m_posicion = Vector2f(x, y);
	m_velocidad = Vector2f(0.0f, 0.0f);
	
	m_textura = GestorRecursos::ObtenerTextura("assets/reposo.png");
	m_sprite.setTexture(m_textura);
	m_sprite.setTextureRect(IntRect(0, 0, 96, 80)); // Tu recorte de frame
	
	// --- CAMBIO CRÍTICO: CAJA DE PIES ---
	// Definimos una caja pequeña solo para los pies
	float anchoPies = 30.0f;
	float altoPies = 15.0f; 
	
	m_cajaColision = FloatRect(m_posicion.x, m_posicion.y, anchoPies, altoPies);
	
	// BORRAR inicializaciones de m_enElSuelo, m_puedeDobleSalto, etc.
}


void Agil::ProcesarEntrada() {
	m_velocidad = Vector2f(0.0f, 0.0f);
	
	// X: Izquierda / Derecha
	if (Keyboard::isKeyPressed(Keyboard::A)) m_velocidad.x = -VELOCIDAD_MAXIMA;
	if (Keyboard::isKeyPressed(Keyboard::D)) m_velocidad.x = VELOCIDAD_MAXIMA;
	
	// Y: Arriba / Abajo (Ya no es salto)
	if (Keyboard::isKeyPressed(Keyboard::W)) m_velocidad.y = -VELOCIDAD_MAXIMA;
	if (Keyboard::isKeyPressed(Keyboard::S)) m_velocidad.y = VELOCIDAD_MAXIMA;
}

void Agil::Actualizar() {
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


void Agil::Dibujar(RenderWindow &ventana) {
	ventana.draw(m_sprite);
}
