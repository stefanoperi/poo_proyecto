#include "GestorRecursos.h"
#include <iostream>
///Como la clase no debe tener constructor, defino las variables estaticas 
std::map<std::string, sf::Texture> GestorRecursos::s_texturas;
std::map<std::string, sf::Font> GestorRecursos::s_fuentes;
std::map<std::string, sf::SoundBuffer> GestorRecursos::s_sonidos;

sf::Texture& GestorRecursos::ObtenerTextura(const std::string& archivo){
	auto it = s_texturas.find(archivo);

	if (it != s_texturas.end()){
		// Si la encuentra, devuelve la textura
		return it->second; 
	}
	
	// Obtiene una referencia al espacio vacio para la nueva textura
	sf::Texture& referencia_permanente = s_texturas[archivo];
	
	//Intenta cargar la textura o la textura de error:
	if (!referencia_permanente.loadFromFile(archivo)){
		std::cerr<< "ERROR: No se pudo cargar la textura: "<<archivo<<std::endl;
		if (!referencia_permanente.loadFromFile("recursos/texturas/error.png")) {
			std::cerr<<"ERROR FATAL: No se pudo cargar ni siquiera 'error.png'!"<<std::endl;
		}
	}
	return referencia_permanente;
}


sf::Font& GestorRecursos::ObtenerFuente(const std::string& archivo) {
	// Ver si la fuente ya está cargada
	auto it = s_fuentes.find(archivo);
	if (it != s_fuentes.end()) {
		return it->second;
	}
	
	// Obtiene una referencia al espacio vacio para la nueva fuente
	sf::Font& referencia_permanente = s_fuentes[archivo];
	
	// 3 Intentar cargar la fuente
	if (!referencia_permanente.loadFromFile(archivo)) {
		std::cerr << "ERROR: No se pudo cargar la fuente: " << archivo << std::endl;
		
		// Intentar cargar una fuente de emergencia
		if (!referencia_permanente.loadFromFile("error.ttf")) {
			std::cerr << "ERROR FATAL: No se pudo cargar ni siquiera 'error.ttf'!" << std::endl;
		}
	}
	
	return referencia_permanente;
}



