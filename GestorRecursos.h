#ifndef GESTORDERECURSOS_H
#define GESTORDERECURSOS_H #ifndef GESTOR_RECURSOS_H
#define GESTOR_RECURSOS_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <map>
#include <string>


/// El gestor de recursos al ser una clase estatica permite que las texturas (imagenes) vivan todo el programa
/// Esto evita bugs ya que impide que los sprites apunten a texturas borradas accidentalmente
class GestorRecursos {
public:
	// Devuelve una textura cargada, cargándola si aún no existe
	static sf::Texture& ObtenerTextura(const std::string& archivo);
	
	///Faltan implementar estas en el .cpp: 
	// Devuelve una fuente cargada
	static sf::Font& ObtenerFuente(const std::string& archivo);
	
	// Devuelve un buffer de sonido cargado
	static sf::SoundBuffer& ObtenerSonido(const std::string& archivo);
	
	// Limpia todos los recursos cargados (opcional, para cuando cambias de nivel)
	static void Limpiar();
	
private:
	/// Al poner el constructor en private impide que se construya (no es instanciable) asi no hay q pasarlo siempre como parametro
	GestorRecursos(){} 
	static std::map<std::string, sf::Texture> s_texturas;
	static std::map<std::string, sf::Font> s_fuentes;
	static std::map<std::string, sf::SoundBuffer> s_sonidos;
};

#endif

