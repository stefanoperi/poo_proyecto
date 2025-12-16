#include "Niveles.h"
#include "TiposDeTile.h"
#include <cstdlib>

void LlenarBordes(std::vector<std::vector<int>>& matriz, int filas, int cols) {
	for (int y = 0; y < filas; y++) {
		for (int x = 0; x < cols; x++) {
			if (y == 0 || y == filas - 1 || x == 0 || x == cols - 1) {
				matriz[y][x] = TILE_PARED;
			}
		}
	}
}


void Nivel1::GenerarMapa() {
	m_matrizDatos.resize(FILAS, std::vector<int>(COLUMNAS, 0));
	LlenarBordes(m_matrizDatos, FILAS, COLUMNAS);
	
	for (int x = 20; x < COLUMNAS - 20; x++) {
		m_matrizDatos[15][x] = TILE_PARED;
		m_matrizDatos[40][x] = TILE_PARED;
	}
}

void Nivel2::GenerarMapa() {
	m_matrizDatos.resize(FILAS, std::vector<int>(COLUMNAS, 0));
	LlenarBordes(m_matrizDatos, FILAS, COLUMNAS);
	
	for (int x = 5; x < 15; x++) m_matrizDatos[10][x] = TILE_PARED;
	for (int x = 20; x <30; x++) m_matrizDatos[20][x] = TILE_PARED;
	for (int x = 35; x <50; x++) m_matrizDatos[30][x] = TILE_PARED;
	
	for (int x = 50; x <65; x++) m_matrizDatos[30][x] = TILE_PARED;
	for (int x = 65; x <80; x++) m_matrizDatos[20][x] = TILE_PARED;
	for (int x = 80; x <95; x++) m_matrizDatos[10][x] = TILE_PARED;
}


void Nivel3::GenerarMapa() {
	m_matrizDatos.resize(FILAS, std::vector<int>(COLUMNAS, 0));
	LlenarBordes(m_matrizDatos, FILAS, COLUMNAS);
	
	// Fila 8
	for (int x = 5; x < 35; x++) m_matrizDatos[8][x] = TILE_PARED;
	for (int x = 50; x < 90; x++) m_matrizDatos[8][x] = TILE_PARED;
	
	// Fila 16
	for (int x = 5; x < 25; x++) m_matrizDatos[16][x] = TILE_PARED;
	for (int x = 55; x < 95; x++) m_matrizDatos[16][x] = TILE_PARED;
	
	// Fila 26
	for (int x = 10; x < 30; x++) m_matrizDatos[26][x] = TILE_PARED;
	for (int x = 40; x < 60; x++) m_matrizDatos[26][x] = TILE_PARED;
	for (int x = 70; x < 90; x++) m_matrizDatos[26][x] = TILE_PARED;
	
	// Fila 40
	for (int x = 15; x < 45; x++) m_matrizDatos[40][x] = TILE_PARED;
	for (int x = 55; x < 85; x++) m_matrizDatos[40][x] = TILE_PARED;
	
	// Fila 52
	for (int x = 5; x < 100; x++) m_matrizDatos[52][x] = TILE_PARED;
}

void Nivel4::GenerarMapa() {
	m_matrizDatos.resize(FILAS, std::vector<int>(COLUMNAS, 0));
	LlenarBordes(m_matrizDatos, FILAS, COLUMNAS);
	
	// Techo
	for (int x = 25; x < 55; x++) m_matrizDatos[10][x] = TILE_PARED;
	
	// Piso
	for (int x = 20; x < 60; x++) m_matrizDatos[22][x] = TILE_PARED;
	
	// Barreras superiores
	for (int x = 5; x < 20; x++) m_matrizDatos[5][x] = TILE_PARED;
	for (int x = 80; x < 100; x++) m_matrizDatos[5][x] = TILE_PARED;
	
	// Barreras medias-bajas
	for (int x = 5; x < 30; x++) m_matrizDatos[35][x] = TILE_PARED;
	for (int x = 70; x < 100; x++) m_matrizDatos[35][x] = TILE_PARED;
	
	// Barrera baja central
	for (int x = 30; x < 70; x++) m_matrizDatos[45][x] = TILE_PARED;
	
	// Barrera final
	for (int x = 10; x < 90; x++) m_matrizDatos[55][x] = TILE_PARED;
}
