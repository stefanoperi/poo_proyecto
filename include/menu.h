#ifndef MENU_H
#define MENU_H
#include "Escena.h" 
#include <SFML/Graphics.hpp>

class Menu : public Escena {
public:
	Menu();
	void Actualizar(Juego &j) override;
	void Dibujar(sf::RenderWindow &ventana) override;
	void ProcesarEventos(Juego &j, sf::Event &e) override;
	
private:
	sf::Font m_fuente;
	sf::Text m_titulo; 
	sf::Text m_txtJugar;    
	sf::Text m_txtPuntajes; 
	int m_opcionSeleccionada; 
};

#endif
