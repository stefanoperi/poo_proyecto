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
	srand(time(0));
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
	while(m_ventana.pollEvent(e)) { 
		if(e.type == sf::Event::Closed){
			m_ventana.close();	
		}
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
