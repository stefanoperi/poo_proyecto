#ifndef LEVELSCENE_H
#define LEVELSCENE_H

#include "Escena.h" 
#include "Personaje.h" 


class Nivel : public Escena {
private:
	Personaje* m_agil; 
	Personaje* m_pesado; 
	const float ALTURA_SUELO;
	
public:
	Nivel();     
	~Nivel();      
	void Actualizar(Juego &j) override;
	void Dibujar(sf::RenderWindow &ventana) override; 
	void ProcesarEventos(Juego &j, sf::Event &e) override;
};

#endif
