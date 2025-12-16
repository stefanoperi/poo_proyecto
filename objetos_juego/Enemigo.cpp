#include "Enemigo.h"
#include <SFML/Window/Keyboard.hpp>
#include "GestorRecursos.h"
#include <cmath>
#include <iostream>
using namespace std;
using namespace sf;

Enemigo::Enemigo(float x, float y, Personaje* objetivo, float escala) {
	m_posicion = Vector2f(x, y);
	m_velocidad = Vector2f(0.0f, 0.0f);
	m_posAnterior = m_posicion;
	m_tiempoDesvio = 0;
	
	m_listoParaBorrar = false;
	
	// Si son mas grandes tienen mas vida
	m_vida = 2 * escala;
	m_timerInvulnerabilidad = 0; 
	m_objetivo = objetivo;
	m_frameAtaque = 0;
	m_timerAnimacion = 0;
	m_estaAtacando = false;
	
	m_frameMuerte = 0; 
	m_timerMuerte = 0;
	m_texturaMuerte = GestorRecursos::ObtenerTextura("recursos/texturas/Skeleton/Death/Death_F.png");
	m_textura = GestorRecursos::ObtenerTextura("recursos/texturas/Skeleton/Idle/Idle_F.png");
	m_sprite.setTexture(m_textura);
	m_sprite.setScale(escala, escala);
		
	sf::Vector2u tamanoTextura = m_textura.getSize();
	m_anchoFrame = tamanoTextura.x / 8;  // Divide en 8 columnas 
	m_altoFrame = tamanoTextura.y;    // 1 sola fila
	
	// Configura el rect de textura para mostrar al principio el primer frame
	m_sprite.setTextureRect(IntRect(0, 0, m_anchoFrame, m_altoFrame));
	float anchoFrameEscalado = m_anchoFrame * escala;
	float altoFrameEscalado = m_altoFrame * escala;
	
	// Ajusta el tamano de la caja
	m_anchoCaja = m_anchoFrame * 0.32;
	m_altoCaja = m_altoFrame * 0.45;
	
	
	// Centra la caja calculando el espacio libre
	m_offsetX =  (anchoFrameEscalado - m_anchoCaja) /2; 
	m_offsetY = (altoFrameEscalado - m_altoCaja) /2;
	m_cajaColision = FloatRect(m_posicion.x + m_offsetX, m_posicion.y + m_offsetY, m_anchoCaja, m_altoCaja);
}

void Enemigo::ProcesarEntrada() {}

bool Enemigo::CercaDeJugador() {
	// Obtiene la posición del centro de la caja del jugador
	auto cajaObjetivo = m_objetivo->ObtenerCaja();
	float centroJugadorX = cajaObjetivo.left + (cajaObjetivo.width / 2.0f);
	float centroJugadorY = cajaObjetivo.top + (cajaObjetivo.height / 2.0f);
	
	float centroX = m_cajaColision.left + (m_cajaColision.width / 2.0f);
	float centroY = m_cajaColision.top + (m_cajaColision.height / 2.0f);
	
	float deltaX = centroX - centroJugadorX;
	float deltaY = centroY - centroJugadorY;
	
	// Aplica teorema de pitagoras
	float distancia = std::sqrt((deltaX * deltaX) + (deltaY* deltaY));
	return distancia < 40.0f; 
}
void Enemigo::Perseguir() {
	if (m_estaAtacando) {
		m_estaAtacando = false; 
		
		// Carga de nuevo la textura del enemigo parado
		m_textura = GestorRecursos::ObtenerTextura("recursos/texturas/Skeleton/Idle/Idle_F.png");
		m_sprite.setTexture(m_textura);
		auto tamano = m_textura.getSize();
		m_anchoFrame = tamano.x / 8; 
		m_sprite.setTextureRect(IntRect(0, 0, m_anchoFrame, m_altoFrame));
	}
	auto cajaObjetivo = m_objetivo->ObtenerCaja();
	float centroJugadorX = cajaObjetivo.left + (cajaObjetivo.width / 2.0f);
	float centroJugadorY = cajaObjetivo.top + (cajaObjetivo.height / 2.0f);
	float centroX = m_cajaColision.left + (m_cajaColision.width / 2.0f);
	float centroY = m_cajaColision.top + (m_cajaColision.height / 2.0f);
	
	// Logica de persecucion
	// Si esta cerca evita sobrecorregir la direccion, ademas solo corrige cuando el objetivo esta a su izq o arriba
	m_velocidad = Vector2f(VELOCIDAD_MAXIMA, VELOCIDAD_MAXIMA);
	
	float deltaX = fabs(centroJugadorX - centroX);
	if (deltaX < m_velocidad.x){
		m_velocidad.x = 0;
	}else if (centroX > centroJugadorX){
		m_velocidad.x = -1 * m_velocidad.x;
	}
	
	float deltaY = fabs(centroJugadorY - centroY);
	if (deltaY < m_velocidad.y){
		m_velocidad.y = 0;
	}else if (centroY > centroJugadorY){
		m_velocidad.y = -1 * m_velocidad.y;
	}
	bool atascadoX = std::abs(m_posicion.x - m_posAnterior.x) < 0.1f;
	bool atascadoY = std::abs(m_posicion.y - m_posAnterior.y) < 0.1f;
	
	// Corrige hacia un lado si quedo atascado
	if (atascadoX && atascadoY) {
		m_tiempoDesvio++;
		if (m_tiempoDesvio > 30) { 
			m_tiempoDesvio = 0;
			m_velocidad = Vector2f(VELOCIDAD_MAXIMA * 7, 0);
		}
	} else { 
		m_tiempoDesvio = 0; 
	}

	m_posAnterior = m_posicion;
	m_posicion += m_velocidad;
	m_sprite.setPosition(m_posicion);
	
	// Actualiza la caja de colisión
	m_cajaColision.left = m_posicion.x + m_offsetX;
	m_cajaColision.top = m_posicion.y + m_offsetY;
}
void Enemigo::RecibirAtaque(int cantidad) {
	if (m_timerInvulnerabilidad > 0 || m_estaMuriendo) return; // Si ya se está muriendo, ignorar
	
	// Recibir daño
	m_vida -= cantidad;
	m_timerInvulnerabilidad = 30;
	m_sprite.setColor(sf::Color::Red);
	
	// Animacion al morir
	if (m_vida <= 0) {
		m_estaMuriendo = true; // Activa el estado de muerte
		m_golpeConectado = true; // Evita que siga haciendo daño si estaba atacando
		m_listoParaBorrar = true;
		m_sprite.setTexture(m_texturaMuerte);
		m_sprite.setTextureRect(sf::IntRect(0, 0, m_anchoFrame, m_altoFrame));
		m_sprite.setColor(sf::Color::White);
		
		// Desactiva la caja de colision
		m_cajaColision.width = 0;
		m_cajaColision.height = 0;
	}
}

void Enemigo::Atacar(){
	float xJugador = m_objetivo->ObtenerCaja().left;
	float yJugador = m_objetivo->ObtenerCaja().top;
	// Solo considera que esta arriba si ademas estan cerca las coordenadas x
	float deltaX = std::abs(xJugador - m_posicion.x);
	bool esArriba = (yJugador < m_posicion.y) && (deltaX < 20.0f);
	bool esIzquierda = (xJugador < m_posicion.x) and esArriba == false ;
	
	// Selección de Textura segun direccion
	if (m_estaAtacando == false) {
		m_estaAtacando = true;
		m_golpeConectado = false;
	
		if (esArriba) {
			m_textura = GestorRecursos::ObtenerTextura("recursos/texturas/Skeleton/Attack_Sword/Attack_Sword_Up.png");
		} 
		else if (esIzquierda) {
			m_textura = GestorRecursos::ObtenerTextura("recursos/texturas/Skeleton/Attack_Sword/Attack_Sword_Left.png");
		} 
		else {
			m_textura = GestorRecursos::ObtenerTextura("recursos/texturas/Skeleton/Attack_Sword/Attack_Sword_Right.png");
		}
		m_sprite.setTexture(m_textura);
		// Reinicia la animación 
		m_frameAtaque = 0;
		m_timerAnimacion = 0;
	}
	
	// Animacion del ataque
	m_timerAnimacion++;
	if (m_timerAnimacion > 7) { 
		m_frameAtaque++; 
		if (m_frameAtaque >= 5) { 
			m_estaAtacando = false; 
			m_frameAtaque = 0;
			m_golpeConectado = false; 
			return;
		}
		m_timerAnimacion = 0; 
	}
	
	// Aplica el daño, solo durante los frames 2 y 3
	if (m_frameAtaque >= 2 and m_frameAtaque <= 3) {
		if (m_golpeConectado == false) {
			sf::FloatRect cajaEspada = this->ObtenerCaja(); 
			float alcance = 40.0f; 
			
			// Define el tamaño de la caja de ataque segun direccion
			if (esArriba) {
				cajaEspada.top -= alcance;    
				cajaEspada.height += alcance; 
			} else if (esIzquierda) {
				cajaEspada.left -= alcance;   
				cajaEspada.width += alcance;
			} else { 
				cajaEspada.width += alcance;  
			}
			
			if (cajaEspada.intersects(m_objetivo->ObtenerCaja())) {
				m_objetivo->RecibirAtaque(1);
				m_golpeConectado = true; 
			}
		}
	}
	auto tamanoTextura = m_textura.getSize();
	int anchoFrameAtaque = tamanoTextura.x / 5; 
	int frameActual = m_frameAtaque;
	
	// Invierte el orden si esta a la izquierda debido a la imagen del ataque izquierdo
	if (esIzquierda) {
		frameActual = 4 - m_frameAtaque;
	}
	m_sprite.setTextureRect(IntRect(frameActual * anchoFrameAtaque, 0, anchoFrameAtaque, tamanoTextura.y));
}
void Enemigo::Actualizar() {
	if (m_estaMuriendo) {
		m_timerMuerte++;
		// Cada 8 frames del juego, avanza 1 frame de animación
		if (m_timerMuerte > 8) {
			m_timerMuerte = 0;
			m_frameMuerte++;
			
			// Al frame 7, la animación terminó
			if (m_frameMuerte >= 7) {
				m_listoParaBorrar = true; 
				return; 
			}
			m_sprite.setTextureRect(sf::IntRect(m_frameMuerte * m_anchoFrame, 0, m_anchoFrame, m_altoFrame));
		}
		return; // Si se está muriendo, no ejecuta Perseguir() ni Atacar()
	}
	if (m_timerInvulnerabilidad > 0) {
		m_timerInvulnerabilidad--;
		if (m_timerInvulnerabilidad == 0) {
			m_sprite.setColor(sf::Color::White); // Vuelve a su color original
		} 
	}
	if (EstaVivo() == false) return;
	
	if (CercaDeJugador()){
		Atacar();
	}else{
		Perseguir();
	}
}

void Enemigo::Dibujar(RenderWindow &ventana) {
	ventana.draw(m_sprite);
}
