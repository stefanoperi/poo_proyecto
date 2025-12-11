
#include <SFML/Graphics/RenderWindow.hpp>
#include "Juego.h"
#include "Menu.h"
#include <iostream>
using namespace sf;
Juego::Juego()
	: m_ventana(VideoMode(1920,1080),"CALACA SLAYER", sf::Style::Fullscreen)
{
	m_ventana.setFramerateLimit(60);
	m_escena = new Menu();
}

void Juego::Jugar(){
	while(m_ventana.isOpen()) {
		ProcesarEventos();
		Actualizar();
		Dibujar();
		if (m_nueva_escena) {
			delete m_escena;
			m_escena = m_nueva_escena;
			m_nueva_escena = nullptr;
		}
	}
}

void Juego::ProcesarEventos(){
	Event e;
	
	// Bucle de polling de SFML que obtiene todos los eventos ocurridos desde el último frame
	while(m_ventana.pollEvent(e)) { 
		
		// El evento de cerrar ventana siempre se maneja en el objeto Juego
		if(e.type == sf::Event::Closed){
			m_ventana.close();	
		}
		
		// DELEGACIÓN: Pasa el evento al método ProcesarEventos de la escena activa
		m_escena->ProcesarEventos(*this, e); 
	}
}
void Juego::Actualizar(){
	m_escena->Actualizar(*this);
}
void Juego::Dibujar(){
	m_escena->Dibujar(m_ventana);
}
void Juego::PonerEscena(Escena *nueva_escena){
	m_nueva_escena = nueva_escena;
}
