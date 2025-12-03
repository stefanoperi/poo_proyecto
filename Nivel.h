#ifndef LEVELSCENE_H
#define LEVELSCENE_H

#include "Escena.h"
#include "Personaje.h"
#include <vector>
#include <string>

// Asegúrate de incluir tu definición de TILE_VACIO, TILE_TIERRA, etc.
// O defínelos aquí si no tienes un archivo separado:
// #define TILE_VACIO 0
// #define TILE_TIERRA 1
// #define TILE_PLATAFORMA 2

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
	// Eliminadas las constantes de suelo que daban error
	
public:
	Nivel();
	~Nivel() override;
	
	bool HayColision(const sf::FloatRect& caja);
	void Actualizar(Juego &j) override;
	void Dibujar(sf::RenderWindow &ventana) override;
	void ProcesarEventos(Juego &j, sf::Event &e) override;
};

#endif
