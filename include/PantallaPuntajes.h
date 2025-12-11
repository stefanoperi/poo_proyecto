#ifndef PANTALLAPUNTAJES_H
#define PANTALLAPUNTAJES_H

#include "Escena.h" 
#include <SFML/Graphics.hpp>
#include <vector>

class PantallaPuntajes : public Escena { 
public:
	PantallaPuntajes();
	void Actualizar(Juego &j) override;
	void Dibujar(sf::RenderWindow &ventana) override;
	void ProcesarEventos(Juego &j, sf::Event &e) override;
	
private:
	sf::Font m_fuente;
	sf::Text m_titulo;
	sf::Text m_txtVolver;
	
	// Vector de textos para dibujar las líneas de puntaje
	std::vector<sf::Text> m_textosPuntajes;
};

#endif
