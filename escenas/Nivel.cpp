#include "Nivel.h"
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Agil.h"
#include "Pesado.h"
#include "GestorRecursos.h"
#include "TiposDeTile.h"
using namespace sf;

Nivel::Nivel(): 
	TAMANO_TILE(18), 
	FILAS(60), 
	COLUMNAS(107)
{
	m_spriteFondo.setTexture(GestorRecursos::ObtenerTextura(m_rutaDelFondo));
	GenerarMapa();

	m_agil = new Agil(700.0f, 300.0f);
	m_pesado = new Pesado(700.0f, 300.0f);
}

Nivel::~Nivel() {
	delete m_agil;
	delete m_pesado;
}
void Nivel::GenerarMapa(){
	m_matrizDatos.resize(FILAS, std::vector<int>(COLUMNAS));
	
	// Bordes del mapa
	for (int y = 0; y < FILAS; y++) {
		for (int x = 0; x < COLUMNAS; x++) {
			if (y == 0 || y == FILAS - 1 || x == 0 || x == COLUMNAS - 1) {
				m_matrizDatos[y][x] = TILE_PARED;
			}
		}
	}
	// Pilares en las 4 esquinas (de 3x3)
	for (int movY = 0; movY < 3; movY++) {
		for (int movX = 0; movX < 3; movX++) {
			m_matrizDatos[5 + movY][5 + movX] = TILE_PARED;                    // Arriba izq
			m_matrizDatos[5 + movY][COLUMNAS - 8 + movX] = TILE_PARED;         // Arriba der
			m_matrizDatos[FILAS - 8 + movY][5 + movX] = TILE_PARED;            // Abajo izq
			m_matrizDatos[FILAS - 8 + movY][COLUMNAS - 8 + movX] = TILE_PARED; // Abajo der
		}
	}
	
	// Algunos muros 
	for (int x = 20; x < 35; x++) {
		m_matrizDatos[20][x] = TILE_PARED;  // Muro horizontal arriba
	}
	for (int x = COLUMNAS - 35; x < COLUMNAS - 20; x++) {
		m_matrizDatos[FILAS - 21][x] = TILE_PARED;  // Muro horizontal abajo
	}
}

bool Nivel::HayColision(const sf::FloatRect& caja) {
	int tileIzq = static_cast<int>(caja.left / TAMANO_TILE);
	int tileDer = static_cast<int>((caja.left + caja.width) / TAMANO_TILE);
	int tileArr = static_cast<int>(caja.top / TAMANO_TILE);
	int tileAbj = static_cast<int>((caja.top + caja.height) / TAMANO_TILE);
	
	// Verificar límites del mapa
	if (tileIzq < 0 || tileDer >= COLUMNAS || tileArr < 0 || tileAbj >= FILAS) {
		return true;
	}
	
	// Revisar si hay paredes
	for (int y = tileArr; y <= tileAbj; y++) {
		for (int x = tileIzq; x <= tileDer; x++) {
			if (m_matrizDatos[y][x] == TILE_PARED) {
				return true;
			}
		}
	}
	
	return false;
}

void Nivel::Actualizar(Juego &j) {
	// Procesar inputs
	m_agil->ProcesarEntrada();
	m_pesado->ProcesarEntrada();
	
	// Guardar posiciones antes de mover
	m_agil->GuardarPosicion();
	m_pesado->GuardarPosicion();
	
	// Mover personajes
	m_agil->Actualizar();
	m_pesado->Actualizar();
	
	// Corregir si chocan con paredes
	if (HayColision(m_agil->ObtenerCaja())) {
		m_agil->RestaurarPosicion();
	}
	
	if (HayColision(m_pesado->ObtenerCaja())) {
		m_pesado->RestaurarPosicion();
	}
}

void Nivel::Dibujar(RenderWindow &ventana) {
	ventana.clear(Color(70, 125, 0));  // Verde pasto
	
	// Solo dibujar paredes
	for (int y = 0; y < m_matrizDatos.size(); y++) {
		for (int x = 0; x < m_matrizDatos[y].size(); x++) {
			if (m_matrizDatos[y][x] == TILE_PARED) {
				Sprite s;
				s.setTexture(GestorRecursos::ObtenerTextura("recursos/texturas/Tiles/tile_0126.png"));
				s.setPosition(x * TAMANO_TILE, y * TAMANO_TILE);
				ventana.draw(s);
			}
		}
	}
	m_agil->Dibujar(ventana);
	m_pesado->Dibujar(ventana);
	ventana.display();
}
void Nivel::ProcesarEventos(Juego &j, Event &e) {
	if(e.type == Event::KeyPressed && e.key.code == Keyboard::Escape) {
		// Pausa
	}
}
