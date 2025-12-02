#include "Nivel.h"
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Agil.h"
#include "Pesado.h"
#include "GestorRecursos.h"
#include "TiposDeTile.h" // Incluye esto si tienes los defines aquí

using namespace sf;

Nivel::Nivel(): 
	TAMANO_TILE(18), 
	FILAS(60), 
	COLUMNAS(107)
{
	// Cargar Fondo
	m_spriteFondo.setTexture(GestorRecursos::ObtenerTextura(m_rutaDelFondo));
	
	// Inicializar Matriz del mapa con fondo de pasto
	m_matrizDatos.resize(FILAS, std::vector<int>(COLUMNAS, TILE_PASTO));
	
	// Crear bordes del mapa
	for (int y = 0; y < FILAS; y++) {
		for (int x = 0; x < COLUMNAS; x++) {
			if (y == 0 || y == FILAS - 1 || x == 0 || x == COLUMNAS - 1){
				m_matrizDatos[y][x] = TILE_PARED; // Pared
			}
		}
	}
	
	m_agil = new Agil(200.0f, 200.0f);
	m_pesado = new Pesado(300.0f, 200.0f);
}

Nivel::~Nivel() {
	delete m_agil;
	delete m_pesado;
}

void Nivel::Actualizar(Juego &j) {
	// 1. Inputs
	m_agil->ProcesarEntrada();
	m_pesado->ProcesarEntrada();
	
	m_agil->Actualizar();
	m_pesado->Actualizar();
	
}

void Nivel::Dibujar(RenderWindow &ventana) {
	ventana.clear(Color::Black);
	ventana.draw(m_spriteFondo);
	
	// Dibujar Mapa
	for (int y = 0; y < m_matrizDatos.size(); y++) {
		for (int x = 0; x < m_matrizDatos[y].size(); x++) {
			Sprite s;
			if (m_matrizDatos[y][x] == TILE_PARED){
				s.setTexture(GestorRecursos::ObtenerTextura("assets/Tiles/tile_0126.png"));
			} else if (m_matrizDatos[y][x] == TILE_PASTO){
				s.setTexture(GestorRecursos::ObtenerTextura("assets/Tiles/tile_0000.png"));
			};
			s.setPosition(x * TAMANO_TILE, y * TAMANO_TILE);
			ventana.draw(s);
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
