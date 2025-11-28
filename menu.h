#ifndef MENU_H
#define MENU_H
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Font.hpp>
#include "Escena.h"


class Menu : public Escena{
public:
	Menu();
	void Actualizar(Juego &j) override;
	void Dibujar(sf::RenderWindow &ventana) override;
	void ProcesarEventos(Juego &j, sf::Event &e) override;
	
private:
	sf::Font m_fuente;
	sf::Text m_t1, m_t2;
};
#endif
