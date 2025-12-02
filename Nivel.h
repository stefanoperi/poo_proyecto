#ifndef LEVELSCENE_H
#define LEVELSCENE_H

#include "Escena.h" 
#include "Personaje.h" 
#include "TiposDeTile.h"
#include <string>

using namespace std;

class Nivel : public Escena {
private:
	Personaje* m_agil; 
	Personaje* m_pesado; 
	std::vector<std::vector<int>> m_matrizDatos;
	string m_rutaDelFondo = "assets/fondo_nivel_1.png";
	sf::Sprite m_spriteFondo;
	const int TAMANO_TILE;
	const int FILAS; 
	const int COLUMNAS;
	const int ALTO_VENTANA;
	const int ANCHO_VENTANA;
	const int FILA_INICIO_SUELO;
	const float ALTURA_SUELO; 
public:
	Nivel();     
	~Nivel();      
	void Actualizar(Juego &j) override;
	void Dibujar(sf::RenderWindow &ventana) override; 
	void ProcesarEventos(Juego &j, sf::Event &e) override;
};

#endif
