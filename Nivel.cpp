#include "Nivel.h"
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "Agil.h"
#include "Pesado.h"


using namespace sf;   
Nivel::Nivel(): ALTURA_SUELO(400.0f) {
	m_agil = new Agil(200,100);
	m_pesado = new Pesado(55,50);
	
}

Nivel::~Nivel() {
	delete m_agil; 
	delete m_pesado; 
}

void Nivel::Actualizar(Juego &j) {
	// Actualizan sus variables de VELOCIDAD segun lo que ingrese el jugador
	m_agil->ProcesarEntrada();
	m_pesado->ProcesarEntrada();
	
	// Aplica esas velocidades y gravedad para calcular la POSICIÓN
	m_agil->Actualizar(); 
	m_pesado->Actualizar(); 
	
	// Colisión del personaje ágil
	if (m_agil->ObtenerAlturaPies() >= ALTURA_SUELO) {
		m_agil->TocoElSuelo(ALTURA_SUELO); 
	}
	
	// Colisión del personaje pesado
	if (m_pesado->ObtenerAlturaPies() >= ALTURA_SUELO) {
		m_pesado->TocoElSuelo(ALTURA_SUELO); 
	}
	
}

void Nivel::Dibujar(RenderWindow &ventana) {
	// Usamos un color celeste oscuro ({50, 50, 80}) para diferenciarlo del menú negro.
	ventana.clear({50, 50, 80}); 
	
	// Dibuja el "Piso" 
	RectangleShape piso({(float)ventana.getSize().x, 5.0f});
	piso.setFillColor({50, 200, 50}); // Verde
	piso.setPosition(0, ALTURA_SUELO);  
	ventana.draw(piso);
	
	// Delegamos el dibujo al propio objeto personaje.
	m_agil->Dibujar(ventana);
	m_pesado->Dibujar(ventana);
	
	// Mostrar todo 
	ventana.display();
}

void Nivel::ProcesarEventos(Juego &j, Event &e) {
	if(e.type == Event::KeyPressed) {
		if (e.key.code == Keyboard::Escape) {
			/// IMPLEMENTAR MENU DE PAUSA
			/// j.PonerEscena(new Pausa()); 
		}
	}
}
