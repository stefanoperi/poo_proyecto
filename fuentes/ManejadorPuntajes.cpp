#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm> 
#include "ManejadorPuntajes.h"
using namespace std;

bool ManejadorPuntajes::CompararPuntajes(const EntradaPuntaje& a, const EntradaPuntaje& b) {
	return a.tiempo > b.tiempo; 
}

// Función para guardar un nuevo record
void ManejadorPuntajes::GuardarPuntaje(std::string nombre, int tiempo) {
	std::ofstream archivo("puntajes.txt", std::ios::app);
	if (archivo.is_open()) {
		archivo << nombre << " " << tiempo << "\n";
		archivo.close();
	} else{ 
		cerr<<"No se pudo abrir el archivo de puntajes"<<std::endl;
	}
}

// Función para leer y devolver los mejores
std::vector<EntradaPuntaje> ManejadorPuntajes::ObtenerMejoresPuntajes() {
	std::vector<EntradaPuntaje> lista;
	std::ifstream archivo("puntajes.txt");
	
	std::string nombreTemp;
	int tiempoTemp;
	
	// Lee palabra por palabra mientras haya datos
	while (archivo >> nombreTemp >> tiempoTemp) {
		EntradaPuntaje e;
		e.nombre = nombreTemp;
		e.tiempo = tiempoTemp;
		lista.push_back(e);
	}
	archivo.close();
	std::sort(lista.begin(), lista.end(), CompararPuntajes);	
	
	if (lista.size() > 5) {
		lista.resize(5);
	}
	return lista;
}

