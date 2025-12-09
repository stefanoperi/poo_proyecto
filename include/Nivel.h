#ifndef LEVELSCENE_H
#define LEVELSCENE_H

#include "Escena.h"
#include "Personaje.h"
#include <vector>
#include <string>


class Nivel : public Escena {
private:
	Personaje* m_agil;
	std::vector<Personaje*> m_enemigos;
	int m_contadorTiempo;
	std::vector<std::vector<int>> m_matrizDatos;
	std::string m_rutaDelFondo = "recursos/texturas/fondo_nivel_1.png";
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
