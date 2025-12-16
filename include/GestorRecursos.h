#ifndef GESTORDERECURSOS_H
#define GESTORDERECURSOS_H #ifndef GESTOR_RECURSOS_H
#define GESTOR_RECURSOS_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <map>
#include <string>


class GestorRecursos {
public:
	// Devuelve una textura cargada, cargándola si aún no existe
	static sf::Texture& ObtenerTextura(const std::string& archivo);
	
	// Devuelve una fuente cargada
	static sf::Font& ObtenerFuente(const std::string& archivo);
private:
	GestorRecursos(){} // No es instanciable
	static std::map<std::string, sf::Texture> s_texturas;
	static std::map<std::string, sf::Font> s_fuentes;
	static std::map<std::string, sf::SoundBuffer> s_sonidos;
};

#endif

