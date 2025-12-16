#ifndef LEVELSCENE_H
#define LEVELSCENE_H
#include <SFML/Audio.hpp>
#include "Escena.h"
#include "Personaje.h"
#include "Agil.h"
#include <vector>
#include <string>


class NivelBase : public Escena {
protected:
	virtual void GenerarMapa() = 0;
	std::vector<std::vector<int>> m_matrizDatos;
	const int FILAS;
	const int COLUMNAS;
private:
	Agil* m_agil;
	std::vector<Personaje*> m_enemigos;
	int m_contadorTiempo;
	
	const int TAMANO_TILE;
	
	int m_idNivel; 
	static int m_nivelesJugados;
	int m_enemigosEliminados; 
	int m_metaEnemigos; 
	
	sf::Text m_textoTiempo;     
	sf::Clock m_relojFrame;    
	static float m_tiempoJuego;
	
	sf::Music m_musicaFondo;
	
	sf::Text m_textoEnemigosRestantes;
	
	bool m_estaPausado;            
	bool m_escPresionadoPrevio;    
	sf::RectangleShape m_fondoPausa; 
	sf::Text m_textoTituloPausa;
	sf::Text m_textoOpciones;
	
	bool m_juegoTerminado;      
	sf::Text m_textoFin;   
	sf::Text m_textoOpcionesFin;
	sf::Text m_textoIngresarNombre; 
	sf::Text m_textoNombreUsuario;  
	std::string m_nombreJugador;    
	bool m_yaGuardo;
	
	void ActualizarUI(float dt);
	void GenerarEnemigos();
	void ActualizarFisicas();
	void ProcesarCombate();
	void VerificarEstadoJuego(Juego &j);
public:
	NivelBase(int id);
	~NivelBase() override;
	
	bool HayColision(const sf::FloatRect& caja);
	void Actualizar(Juego &j) override;
	void Dibujar(sf::RenderWindow &ventana) override;
	void ProcesarEventos(Juego &j, sf::Event &e) override;
};

#endif
