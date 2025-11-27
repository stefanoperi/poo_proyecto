#ifndef LEVELSCENE_H
#define LEVELSCENE_H

#include "Escena.h"    // Necesario porque heredamos de Escena
#include "Personaje.h" // Necesario porque vamos a usar un Personaje

// Heredamos de Escena para cumplir el contrato (Actualizar/Dibujar)
class LevelScene : public Escena {
private:
	// ATRIBUTO: Un puntero al protagonista de este nivel.
	// Usamos puntero (*) porque lo vamos a crear con 'new' en el constructor.
	Personaje* m_hero; 
	
public:
	LevelScene();      // Constructor: Aquí nace el nivel
	~LevelScene();     // Destructor: Aquí muere (limpiamos memoria)
	
	// MÉTODOS SOBREESCRITOS (OVERRIDE):
	// Solo ponemos el punto y coma ';' porque la lógica va en el .cpp
	void Actualizar(Juego &j) override;
	void Dibujar(sf::RenderWindow &ventana) override;
	void ProcesarEventos(Juego &j, sf::Event &e) override;
};

#endif
