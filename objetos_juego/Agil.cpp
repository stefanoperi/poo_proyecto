#include "Agil.h"
#include <SFML/Window/Keyboard.hpp>
#include "GestorRecursos.h"
#include <iostream> 

using namespace sf;

//  La imagen tiene espacio para 19 muñecos
const int COLUMNAS_TOTALES_GRILLA = 19; 

Agil::Agil(float x, float y) {
	m_listoParaBorrar = false;
	m_vida = 5;                  
	m_timerInvulnerabilidad = 0; 
	
	m_posicion = Vector2f(x, y);
	m_velocidad = Vector2f(0.0f, 0.0f);
	m_direccion = 0;       
	m_enMovimiento = false;
	m_atacando = false;
	m_frameAtaque = 0;
	m_frameCaminar = 0;
	m_timerAnimacion = 0;
	m_timerCooldown = 100; 
	
	m_texturaCorrer = GestorRecursos::ObtenerTextura("recursos/texturas/Fighter/run.png");
	m_texturaAtacar = GestorRecursos::ObtenerTextura("recursos/texturas/Fighter/jab.png");
	m_texturaIdle   = GestorRecursos::ObtenerTextura("recursos/texturas/Fighter/idle.png");
	m_texturaBola = GestorRecursos::ObtenerTextura("recursos/texturas/Fighter/ball.png");
	
	
	// Arranca con la textura del personaje parado (idle)
	m_sprite.setTexture(m_texturaIdle);
	sf::Vector2u tamano = m_texturaIdle.getSize();
	m_anchoFrame = tamano.x / COLUMNAS_TOTALES_GRILLA; 
	m_altoFrame = tamano.y / 4;  
	m_sprite.setTextureRect(IntRect(0, 0, m_anchoFrame, m_altoFrame));
	
	// Caja de colision 
	m_anchoCaja = m_anchoFrame * 0.30;
	m_altoCaja = m_altoFrame * 0.40;
	m_offsetX = (m_anchoFrame - m_anchoCaja) / 2;
	m_offsetY = (m_altoFrame - m_altoCaja) / 2;
	
	m_cajaColision = FloatRect(m_posicion.x + m_offsetX, m_posicion.y + m_offsetY, m_anchoCaja, m_altoCaja);
}

void Agil::ProcesarEntrada() {
	m_velocidad = Vector2f(0.0f, 0.0f);
	m_enMovimiento = false;
	
	if (m_atacando) return;
	
	// Movimiento
	if (Keyboard::isKeyPressed(Keyboard::A)) {
		m_velocidad.x = -VELOCIDAD_MAXIMA;
		m_direccion = 1; 
		m_enMovimiento = true;
	}
	else if (Keyboard::isKeyPressed(Keyboard::D)) {
		m_velocidad.x = VELOCIDAD_MAXIMA;
		m_direccion = 2; 
		m_enMovimiento = true;
	}
	else if (Keyboard::isKeyPressed(Keyboard::W)) {
		m_velocidad.y = -VELOCIDAD_MAXIMA;
		m_direccion = 3; 
		m_enMovimiento = true;
	}
	else if (Keyboard::isKeyPressed(Keyboard::S)) {
		m_velocidad.y = VELOCIDAD_MAXIMA;
		m_direccion = 0; 
		m_enMovimiento = true;
	}
	
	if (Keyboard::isKeyPressed(Keyboard::Space)  and m_timerCooldown > 30) {
		m_atacando = true;
		m_frameAtaque = 0;    
		m_timerAnimacion = 0; 
		m_timerCooldown = 0; 
		BolaEnergia nuevaBola;
		nuevaBola.sprite.setTexture(m_texturaBola);
		
		// Centra la bola en el personaje
		float centroX = m_posicion.x + (m_anchoFrame / 2);
		float centroY = m_posicion.y + (m_altoFrame / 2);
		

		float velocidadBola = 6.0f; 
		// Calcula la dirección según a dónde mira el personaje
		switch (m_direccion) {
		case 0: // Abajo
			nuevaBola.sprite.setPosition(centroX - 25, centroY);
			nuevaBola.velocidad = Vector2f(0, velocidadBola);
			break;
		case 1: // Izquierda
			nuevaBola.sprite.setPosition(centroX - 55 , centroY - 25);
			nuevaBola.velocidad = Vector2f(-velocidadBola, 0);
			break;
		case 2: // Derecha
			nuevaBola.sprite.setPosition(centroX, centroY - 25);
			nuevaBola.velocidad = Vector2f(velocidadBola, 0);
			break;
		case 3: // Arriba
			nuevaBola.sprite.setPosition(centroX - 25, centroY - 40);
			nuevaBola.velocidad = Vector2f(0, -velocidadBola);
			break;
		}
		m_bolas.push_back(nuevaBola);
	}
}

int ObtenerFilaReal(int direccionIntencion) {
	// Transforma el numero intencionado en el valor real de la direccion
	switch (direccionIntencion) {
	case 0: return 2; 
	case 1: return 3; 
	case 2: return 1;
	case 3: return 0; 
	default: return 0;
	}
}
int Agil::ObtenerVida() { return m_vida; }
void Agil::Atacar() {
	m_timerAnimacion++;
	// Animacion de ataque ajustada por un timer para que sea mas lenta
	if (m_timerAnimacion > 4) { 
		m_timerAnimacion = 0;
		m_frameAtaque++;
		if (m_frameAtaque >= 4) {
			m_atacando = false; 
			m_frameAtaque = 0;
		}
	}
}
std::vector<BolaEnergia>* Agil::ObtenerBolas(){ return &m_bolas; }

void Agil::Actualizar() {
	if (m_timerInvulnerabilidad > 0) {
		m_timerInvulnerabilidad--;
	}
	if (EstaVivo() == false) {
		m_sprite.setColor(sf::Color(100, 100, 100)); // Gris oscuro (Muerto)
		return;
	}
	if (m_timerInvulnerabilidad == 0) {
		float progreso = 1.0f - (float)m_vida / 5.0f;
		int verdeAzul = 255 - (progreso * 200);
		if (verdeAzul < 0) verdeAzul = 0;
		m_sprite.setColor(sf::Color(255, verdeAzul, verdeAzul));
	}
	
	if (m_timerCooldown < 1000) m_timerCooldown++;
	
	m_posicion += m_velocidad;
	m_sprite.setPosition(m_posicion);
	
	m_cajaColision.left = m_posicion.x + m_offsetX;
	m_cajaColision.top = m_posicion.y + m_offsetY;
	
	// Mover bolas de energia existentes
	for (size_t i = 0; i < m_bolas.size(); i++) {
		m_bolas[i].sprite.move(m_bolas[i].velocidad);
	}
	int filaReal = ObtenerFilaReal(m_direccion);
	
	if (m_atacando) {
		m_sprite.setTexture(m_texturaAtacar);
		int anchoLocal = m_texturaAtacar.getSize().x / COLUMNAS_TOTALES_GRILLA;
		int altoLocal = m_texturaAtacar.getSize().y / 4;
		Atacar(); 
		
		m_sprite.setTextureRect(IntRect(m_frameAtaque * anchoLocal,filaReal * altoLocal,   anchoLocal, altoLocal	));
		
		// Guarda medidas correctas
		m_anchoFrame = anchoLocal;
		m_altoFrame = altoLocal;
	}
	else if (m_enMovimiento) {
		m_sprite.setTexture(m_texturaCorrer);
		int anchoLocal = m_texturaCorrer.getSize().x / COLUMNAS_TOTALES_GRILLA; 
		int altoLocal = m_texturaCorrer.getSize().y / 4;
	
		m_timerAnimacion++;
		if (m_timerAnimacion > 3) {
			m_timerAnimacion = 0;
			m_frameCaminar++;
			// Solo llegamos hasta el 12, aunque la imagen tenga 19 huecos
			if (m_frameCaminar >= 12) m_frameCaminar = 0; 
		}
		// Recorta el sprite
		m_sprite.setTextureRect(IntRect(m_frameCaminar * anchoLocal, filaReal * altoLocal,   anchoLocal, altoLocal));
		
		m_anchoFrame = anchoLocal;
		m_altoFrame = altoLocal;
	}
	else {
		// Estado quieto (Idle)
		m_sprite.setTexture(m_texturaIdle);
		int anchoLocal = m_texturaIdle.getSize().x / COLUMNAS_TOTALES_GRILLA; 
		int altoLocal = m_texturaIdle.getSize().y / 4;
		m_sprite.setTextureRect(IntRect(0, filaReal * altoLocal,  anchoLocal, altoLocal));
		m_anchoFrame = anchoLocal;
		m_altoFrame = altoLocal;
	}
}

void Agil::RecibirAtaque(int cantidad) {
	if (m_timerInvulnerabilidad > 0) return;
	
	m_vida -= cantidad;
	
	// Activa invulnerabilidad (60 frames = 1 segundo aprox)
	m_timerInvulnerabilidad = 60;
	if (m_vida <= 0) {
		m_listoParaBorrar = true;
	}
}
void Agil::Dibujar(RenderWindow &ventana) {
	
	// Dibuja las bolas de energia
	for (size_t i = 0; i < m_bolas.size(); i++) {
		ventana.draw(m_bolas[i].sprite);
	}
	ventana.draw(m_sprite);
	
}
