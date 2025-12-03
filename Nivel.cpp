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
	// Carga Fondo
	m_spriteFondo.setTexture(GestorRecursos::ObtenerTextura(m_rutaDelFondo));
	
	// Inicializa Matriz del mapa con fondo de pasto
	m_matrizDatos.resize(FILAS, std::vector<int>(COLUMNAS, TILE_PASTO));
	
	// Crea bordes del mapa
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
bool Nivel::HayColision(const sf::FloatRect& caja) {
	// Calcula qué tiles ocupa el personaje usando las posiciones de su caja
	int tileIzq = static_cast<int>(caja.left / TAMANO_TILE);
	int tileDer = static_cast<int>((caja.left + caja.width) / TAMANO_TILE);
	int tileArr = static_cast<int>(caja.top / TAMANO_TILE);
	int tileAbj = static_cast<int>((caja.top + caja.height) / TAMANO_TILE);
	
	// Verifica que no nos salgamos de la matriz
	if (tileIzq < 0 || tileDer >= COLUMNAS || tileArr < 0 || tileAbj >= FILAS) {
		return true; 
	}
	
	// Revisa todos los tiles que ocupa el personaje para ver si alguno toca una pared
	for (int y = tileArr; y <= tileAbj; y++){
		for (int x = tileIzq; x <= tileDer; x++){
			if (m_matrizDatos[y][x] == TILE_PARED){
				return true; // Hay una pared
			}
		}
	}
	
	return false; // No hay colisión
}

void Nivel::Actualizar(Juego &j) {
	m_agil->ProcesarEntrada();
	m_pesado->ProcesarEntrada();
	
	m_agil->GuardarPosicion();
	m_pesado->GuardarPosicion();
	
	m_agil->Actualizar();
	m_pesado->Actualizar();
	
	// Verifica colisiones y corrije si es necesario
	if (HayColision(m_agil->ObtenerCaja())) {
		m_agil->RestaurarPosicion();
	}
	
	if (HayColision(m_pesado->ObtenerCaja())) {
		m_pesado->RestaurarPosicion();
	}
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
