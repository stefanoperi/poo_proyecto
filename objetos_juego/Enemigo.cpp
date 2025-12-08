#include "Enemigo.h"
#include <SFML/Window/Keyboard.hpp>
#include "GestorRecursos.h"
#include <cmath>
#include <iostream>
using namespace std;
using namespace sf;

Enemigo::Enemigo(float x, float y, Personaje* objetivo) {
	m_posicion = Vector2f(x, y);
	m_velocidad = Vector2f(0.0f, 0.0f);
	m_objetivo = objetivo;
	m_frameAtaque = 0;
	m_timerAnimacion = 0;
	m_estaAtacando = false;
	
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
		m_estaAtacando = false; // Ya no ataca
		
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

	m_posicion += m_velocidad;
	m_sprite.setPosition(m_posicion);
	
	// Actualiza la caja de colisión
	m_cajaColision.left = m_posicion.x + m_offsetX;
	m_cajaColision.top = m_posicion.y + m_offsetY;
}
void Enemigo::Atacar(){
	float xJugador = m_objetivo->ObtenerCaja().left;
	float yJugador = m_objetivo->ObtenerCaja().top;
	// Solo considera que esta arriba si ademas estan cerca las coordenadas x
	float deltaX = std::abs(xJugador - m_posicion.x);
	bool esArriba = (yJugador < m_posicion.y) && (deltaX < 20.0f);
	bool esIzquierda = (xJugador < m_posicion.x) and esArriba == false ;
	
	if (m_estaAtacando == false) {
		m_estaAtacando = true;
		// Selección de Textura
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
	// Cada 7 iteraciones de la funcion cambia de dibujo
	m_timerAnimacion++;
	if (m_timerAnimacion > 7) { 
		m_frameAtaque++; // Pasa al siguiente dibujo
		if (m_frameAtaque >= 5) { 
			m_frameAtaque = 0; 
		}
		m_timerAnimacion = 0; 
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
	if (CercaDeJugador()){
		Atacar();
	}else{
		Perseguir();
	}
}

void Enemigo::Dibujar(RenderWindow &ventana) {
	ventana.draw(m_sprite);
}
