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
		if (!referencia_permanente.loadFromFile("error.png")) {
			std::cerr<<"ERROR FATAL: No se pudo cargar ni siquiera 'error.png'!"<<std::endl;
		}
	}
	return referencia_permanente;
}



///FALTAN HACER ESTOS: 
// Devuelve una fuente cargada
sf::Font& ObtenerFuente(const std::string& archivo);

// Devuelve un buffer de sonido cargado
sf::SoundBuffer& ObtenerSonido(const std::string& archivo);

// Limpia todos los recursos cargados (opcional, para cuando cambias de nivel)
void Limpiar();
