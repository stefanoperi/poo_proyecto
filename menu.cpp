#include <SFML/Graphics/RenderWindow.hpp>
#include "Menu.h"
#include "Juego.h"
#include "GestorRecursos.h"
#include <iostream>
using namespace sf;
#include "Nivel.h" 

Menu::Menu(){
	m_fuente = GestorRecursos::ObtenerFuente("text_fonts/ScienceGothic.ttf");
	m_t1.setFont(m_fuente);
	m_t2.setFont(m_fuente);
	
	m_t1.setString("Gordo y agil, el juego");
	
	/// IMPORTANTE: HAY Q SACAR LOS NUMEROS Y USAR VARIABLES PARA LAS POSICIONES!!
	m_t1.setPosition(90,150);
	m_t1.setCharacterSize(50);
	
	m_t2.setString("<presione Enter para comenzar a jugar>");
	m_t2.setFillColor({150,150,150});
	m_t2.setPosition(100,350);
	m_t2.setCharacterSize(20);
}
void Menu::Actualizar(Juego &j) {
	static float tamanio_actual = 20;
	static float dir = 0.4;
	
	const int minTam = 15;
	const int maxTam = 45;
	
	tamanio_actual += dir;
	
	if (tamanio_actual >= maxTam) dir = -0.4;
	if (tamanio_actual <= minTam) dir = 0.4;
	
	m_t1.setCharacterSize(tamanio_actual);
}


void Menu::ProcesarEventos(Juego &j, sf::Event &e) {

	if (e.type == sf::Event::KeyPressed) {
		
		// 2. Revisamos si la tecla presionada es 'Enter'
		if (e.key.code == sf::Keyboard::Return) {
			j.PonerEscena(new Nivel()); 
			
		}
	}
	
	// Aquí puedes añadir manejo de otros eventos si los necesitas
}
void Menu::Dibujar(RenderWindow &ventana){
	ventana.clear({0,0,0});
	ventana.draw(m_t1);
	ventana.draw(m_t2);
	ventana.display();
}
