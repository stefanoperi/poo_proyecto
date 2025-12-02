#include "Nivel.h"
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "Agil.h"
#include "Pesado.h"
#include "GestorRecursos.h"

using namespace sf;  
/* calculamos exactamente cuántos tiles entran en cada dimensión (considerando una pantalla de 1920*1080)
y considerando q los tiles  miden 18x18px
Columnas (Ancho): 1920/18=106.66... redondeamos a 107
Filas (Alto): Filas=1080/18=60
*/
Nivel::Nivel(): 
	TAMANO_TILE(18), 
	FILAS(60), 
	COLUMNAS(107), 
	ALTO_VENTANA(1080),
	ANCHO_VENTANA(1920),
	FILA_INICIO_SUELO(FILAS - 2), 
	ALTURA_SUELO(static_cast<float>(FILA_INICIO_SUELO * TAMANO_TILE))
{
	m_spriteFondo.setTexture(GestorRecursos::ObtenerTextura(m_rutaDelFondo));
	
	/// Inicializa la matriz de tiles en 0
	m_matrizDatos.resize(FILAS, std::vector<int>(COLUMNAS, TILE_VACIO)); 
	
	/// Define el suelo como un valor de 1 en las filas 58 y 59
	for (int x = 0; x < COLUMNAS; x++) {
		m_matrizDatos[FILA_INICIO_SUELO][x] = TILE_TIERRA;      
		m_matrizDatos[FILA_INICIO_SUELO + 1][x] = TILE_TIERRA; 
	}
	
	m_agil = new Agil(200, ALTURA_SUELO - 100.0f); 
	m_pesado = new Pesado(55, ALTURA_SUELO - 50.0f); 
	
	// Plataformas flotantes  (tipo 2)
	m_matrizDatos[55][40] = TILE_PLATAFORMA;
	m_matrizDatos[55][41] = TILE_PLATAFORMA;
	m_matrizDatos[55][42] = TILE_PLATAFORMA;
	m_matrizDatos[55][43] = TILE_PLATAFORMA;
}


Nivel::~Nivel() {
	delete m_agil; 
	delete m_pesado; 
}

void Nivel::Actualizar(Juego &j) {
	// Actualizan sus variables de VELOCIDAD segun lo que ingrese el jugador
	m_agil->ProcesarEntrada();
	m_pesado->ProcesarEntrada();
	
	// Aplica esas velocidades y gravedad para calcular la POSICIÓN
	m_agil->Actualizar(); 
	m_pesado->Actualizar(); 
	
	// Colisión del personaje ágil
	if (m_agil->ObtenerAlturaPies() >= ALTURA_SUELO) {
		m_agil->TocoElSuelo(ALTURA_SUELO); 
	}
	
	// Colisión del personaje pesado
	if (m_pesado->ObtenerAlturaPies() >= ALTURA_SUELO) {
		m_pesado->TocoElSuelo(ALTURA_SUELO); 
	}
	
}

void Nivel::Dibujar(RenderWindow &ventana) {
	ventana.clear(sf::Color::Black); //Fondo celeste
	ventana.draw(m_spriteFondo);
	
	for (int y = 0; y < m_matrizDatos.size(); y++) {
		for (int x = 0; x < m_matrizDatos[y].size(); x++) {
			int tipoTile = m_matrizDatos[y][x];
		
			if (tipoTile != TILE_VACIO) {
				std::string nombreTextura;
				if (tipoTile == TILE_TIERRA) { 
					nombreTextura = "assets/Tiles/tile_0034.png";
				} 
				else if (tipoTile == TILE_PLATAFORMA) { 
					nombreTextura = "assets/Tiles/tile_0025.png"; 
				}
				sf::Sprite sprite;
				sprite.setTexture(GestorRecursos::ObtenerTextura(nombreTextura));
				sprite.setPosition((float)(x * TAMANO_TILE), (float)(y * TAMANO_TILE));
				ventana.draw(sprite);
			}
		}
	}
	
	m_agil->Dibujar(ventana);
	m_pesado->Dibujar(ventana);
	ventana.display();
}

void Nivel::ProcesarEventos(Juego &j, Event &e) {
	if(e.type == Event::KeyPressed) {
		if (e.key.code == Keyboard::Escape) {
			/// IMPLEMENTAR MENU DE PAUSA
			/// j.PonerEscena(new Pausa()); 
		}
	}
}
