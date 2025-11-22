
#include <SFML/Graphics/RenderWindow.hpp>
#include "Juego.h"
#include <iostream>
using namespace sf;
Juego::Juego()
	: m_ventana(VideoMode(640,480),"Gordo y agil, el juego")
{
	m_ventana.setFramerateLimit(60);
	// m_escena = new Menu();
}

void Juego::Jugar(){
	while(m_ventana.isOpen()) {
		/*
		ProcesarEventos();
		Actualizar();
		Dibujar();
		if (m_nueva_escena) {
			delete m_escena;
			m_escena = m_nueva_escena;
			m_nueva_escena = nullptr;
		}
		*/
		m_ventana.clear(sf::Color(rand(),rand(),rand()));
		m_ventana.display();
	}
}

///Falta hacer:
void Juego::ProcesarEventos(){}
void Juego::Actualizar(){}
void Juego::Dibujar(){}
void Juego::PonerEscena(Escena *nueva_escena){}
