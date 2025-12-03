#ifndef LEVELSCENE_H
#define LEVELSCENE_H

#include "Escena.h"
#include "Personaje.h"
#include <vector>
#include <string>


using namespace std;

class Nivel : public Escena {
private:
	Personaje* m_agil;
	Personaje* m_pesado;
	
	std::vector<std::vector<int>> m_matrizDatos;
	string m_rutaDelFondo = "recursos/texturas/fondo_nivel_1.png";
	sf::Sprite m_spriteFondo;
	
	const int TAMANO_TILE;
	const int FILAS;
	const int COLUMNAS;
	void GenerarMapa();
public:
	Nivel();
	~Nivel() override;
	
	bool HayColision(const sf::FloatRect& caja);
	void Actualizar(Juego &j) override;
	void Dibujar(sf::RenderWindow &ventana) override;
	void ProcesarEventos(Juego &j, sf::Event &e) override;
};

#endif
