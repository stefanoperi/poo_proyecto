#include "Menu.h"
#include "Juego.h"
#include "GestorRecursos.h"
#include "Niveles.h"
#include <iostream>
#include "PantallaPuntajes.h"
#include "NivelBase.h"

using namespace sf;

Menu::Menu() {
	m_fuente = GestorRecursos::ObtenerFuente("recursos/fuentes_texto/ScienceGothic.ttf");
	
	// Empezamos parados en la opción 0 (Jugar)
	m_opcionSeleccionada = 0;

	m_titulo.setFont(m_fuente);
	m_titulo.setString("CALACA SLAYER");
	m_titulo.setFillColor(Color::White);
	
	m_txtJugar.setFont(m_fuente);
	m_txtJugar.setString("JUGAR"); 
	
	m_txtPuntajes.setFont(m_fuente);
	m_txtPuntajes.setString("VER MEJORES PUNTAJES");
}

void Menu::Actualizar(Juego &j) {
	//  Animación del Título  
	static float tamanioTitulo = 50;
	static float dir = 0.4;
	
	tamanioTitulo += dir;
	if (tamanioTitulo >= 55) dir = -0.4;
	if (tamanioTitulo <= 45) dir = 0.4;
	m_titulo.setCharacterSize((unsigned int)tamanioTitulo);

	// Pone ambas opciones en estado "No Seleccionado" (Gris y chicas)
	m_txtJugar.setFillColor({150, 150, 150});
	m_txtJugar.setCharacterSize(30);
	m_txtPuntajes.setFillColor({150, 150, 150});
	m_txtPuntajes.setCharacterSize(30);
	
	
	// Iluminamos solo la que coincida con m_opcionSeleccionada
	if (m_opcionSeleccionada == 0) {
		m_txtJugar.setFillColor(Color::Yellow); 
		m_txtJugar.setCharacterSize(40);        
	} 
	else if (m_opcionSeleccionada == 1) {
		m_txtPuntajes.setFillColor(Color::Yellow);
		m_txtPuntajes.setCharacterSize(40);
	}
}

void Menu::ProcesarEventos(Juego &j, sf::Event &e) {
	if (e.type == sf::Event::KeyPressed) {
		// Navegacion
		if (e.key.code == sf::Keyboard::Down) {
			m_opcionSeleccionada++; // Bajamos
			if (m_opcionSeleccionada > 1) m_opcionSeleccionada = 0; // Si pasa la última, volvemos a la primera 
		}
		
		if (e.key.code == sf::Keyboard::Up) {
			m_opcionSeleccionada--; // Subimos
			if (m_opcionSeleccionada < 0) m_opcionSeleccionada = 1; // Si subE de la primera, vamos a la última
		}
		
		if (e.key.code == sf::Keyboard::Return) {
			if (m_opcionSeleccionada == 0) {
				// Opción Jugar
				j.PonerEscena(new Nivel4);
			}
			if (m_opcionSeleccionada == 1) {
				// Opción Puntajes
				j.PonerEscena(new PantallaPuntajes());
			}
		}
	}
}
	

void Menu::Dibujar(RenderWindow &ventana){
	ventana.clear(sf::Color::Black);
	float ancho = (float)ventana.getSize().x;
	float alto = (float)ventana.getSize().y; 
	
	//  Título
	FloatRect rTitulo = m_titulo.getGlobalBounds();
	m_titulo.setPosition((ancho - rTitulo.width)/2.0f, alto * 0.35f);
	ventana.draw(m_titulo);
	
	// Opción Jugar 
	FloatRect rJugar = m_txtJugar.getGlobalBounds();
	m_txtJugar.setPosition((ancho - rJugar.width)/2.0f, alto * 0.5f); 
	ventana.draw(m_txtJugar);
	
	// Opción Puntajes 
	FloatRect rPuntajes = m_txtPuntajes.getGlobalBounds();
	m_txtPuntajes.setPosition((ancho - rPuntajes.width)/2.0f, alto * 0.65f); 
	ventana.draw(m_txtPuntajes);
	ventana.display();
}
