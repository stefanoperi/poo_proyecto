#include "Personaje.h"
#include <iostream>
#include "GestorRecursos.h"
using namespace sf;

// 1. CONSTRUCTOR: Inicialización
Personaje::Personaje(float posX, float posY) 
	// Inicializamos el estado del personaje: no está en el suelo, y velocidad (x, y) en cero.
	: m_ensuelo(false), m_velocidad({0.0f, 0.0f}) 
{
	// Cargar la textura a través del Gestor de Recursos (¡eficiente!)
	try {
		// Obtenemos una REFERENCIA a la textura cargada permanentemente.
		Texture& tex = GestorRecursos::ObtenerTextura("sprites/player_placeholder.png"); 
		m_sprite.setTexture(tex);
	} catch (const std::exception& e) {
		std::cerr << "Error: No se pudo cargar textura del personaje." << std::endl;
	}
	
	// Establecer la posición inicial del sprite
	m_sprite.setPosition(posX, posY);
}

// 2. PROCESAR ENTRADA: Manejo del teclado (Movimiento y Salto)
void Personaje::ProcesarEntrada() {
	// Movimiento Horizontal (Solo aplica si la tecla está presionada)
	if (Keyboard::isKeyPressed(Keyboard::Left)) {
		m_velocidad.x = -VELOCIDAD_MOVIMIENTO;
	} else if (Keyboard::isKeyPressed(Keyboard::Right)) {
		m_velocidad.x = VELOCIDAD_MOVIMIENTO;
	} else {
		m_velocidad.x = 0.0f; // Si no hay input, no hay movimiento horizontal
	}
	
	// Salto
	// Solo permite saltar si el personaje está actualmente en el suelo.
	if (Keyboard::isKeyPressed(Keyboard::Space) && m_ensuelo) {
		m_velocidad.y = VELOCIDAD_SALTO_FRAME; // La velocidad vertical se vuelve negativa (hacia arriba)
		m_ensuelo = false; 
	}
}


// 3. ACTUALIZAR: Lógica de la Física (Dependiente de FPS)
void Personaje::Actualizar() {
	
	// Aplicar la gravedad
	if (!m_ensuelo) {
		// Aumentamos la velocidad vertical en cada frame.
		m_velocidad.y += VELOCIDAD_CAIDA_FRAME; 
	}
	
	// Mover el sprite
	// move(offsetX, offsetY) desplaza el sprite la cantidad de píxeles
	// que indican m_velocidad.x y m_velocidad.y.
	m_sprite.move(m_velocidad.x, m_velocidad.y); 
}

// 4. DIBUJAR: Renderizado
void Personaje::Dibujar(RenderWindow &ventana) {
	ventana.draw(m_sprite);
}

// 5. TOCAR SUELO: Corrección de Colisión
void Personaje::TocarSuelo(float alturaSuelo) {
	// Corregir la posición vertical del sprite
	// Mueve el sprite para que su base (altura) quede justo sobre el suelo.
	m_sprite.setPosition(m_sprite.getPosition().x, alturaSuelo - m_sprite.getGlobalBounds().height);
	
	// Resetear el estado de la física
	m_ensuelo = true;
	m_velocidad.y = 0.0f; // Detiene la caída
}
