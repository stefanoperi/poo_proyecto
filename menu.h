#ifndef MENU_H
#define MENU_H
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Font.hpp>
#include "Escena.h"

using namespace sf;
class Menu : public Escena{
public:
	Menu();
	void Actualizar(Juego &j) override;
	void Dibujar(RenderWindow &ventana) override;
	void ProcesarEventos(Juego &j, sf::Event &e) override;
private:
	Font m_fuente;
	Text m_t1, m_t2;
};
#endif
