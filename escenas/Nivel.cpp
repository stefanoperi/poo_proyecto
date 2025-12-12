#include "Nivel.h"
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Agil.h"
#include "Enemigo.h"
#include "GestorRecursos.h"
#include "TiposDeTile.h"
#include <sstream>
#include "ManejadorPuntajes.h"
#include "Juego.h"
#include "Menu.h"
using namespace sf;

Nivel::Nivel(): 
	TAMANO_TILE(18), 
	FILAS(60), 
	COLUMNAS(107),
	m_contadorTiempo(0)
{
	// Semilla aleatoria basada en la hora actual
	srand(time(0));
	m_tiempoJuego = 0.0f; // Empezamos en 0
	m_textoTiempo.setFont(GestorRecursos::ObtenerFuente("recursos/fuentes_texto/ScienceGothic.ttf"));
	m_textoTiempo.setCharacterSize(30);
	m_textoTiempo.setFillColor(Color::White);
	m_textoTiempo.setPosition(15, 10); // Arriba a la izquierda
	
	// Textos de pausa 
	m_estaPausado = false;
	m_escPresionadoPrevio = false;
	m_fondoPausa.setSize(Vector2f(2000.0f, 2000.0f)); 
	m_fondoPausa.setFillColor(Color(0, 0, 0, 150));
	m_spriteFondo.setTexture(GestorRecursos::ObtenerTextura(m_rutaDelFondo));
	m_textoTituloPausa.setFont(GestorRecursos::ObtenerFuente("recursos/fuentes_texto/ScienceGothic.ttf")); 
	m_textoTituloPausa.setString("PAUSA");
	m_textoTituloPausa.setCharacterSize(50);
	m_textoTituloPausa.setFillColor(Color::White);
	m_textoOpciones.setFont(GestorRecursos::ObtenerFuente("recursos/fuentes_texto/ScienceGothic.ttf"));
	m_textoOpciones.setString("Presiona ESC para Continuar\nPresiona Q para Salir");
	m_textoOpciones.setCharacterSize(20);
	m_textoOpciones.setFillColor(Color::Yellow);
	
	// Textos al finalizar el juego
	m_juegoTerminado = false;
	m_yaGuardo = false;         
	m_nombreJugador = "";
	m_textoFin.setFont(GestorRecursos::ObtenerFuente("recursos/fuentes_texto/ScienceGothic.ttf"));
	m_textoFin.setString("¡HAS MUERTO!");
	m_textoFin.setCharacterSize(60);
	m_textoFin.setFillColor(sf::Color::Red);
	
	m_textoIngresarNombre.setFont(GestorRecursos::ObtenerFuente("recursos/fuentes_texto/ScienceGothic.ttf"));
	m_textoIngresarNombre.setString("Escribe tu nombre y presiona ENTER:");
	m_textoIngresarNombre.setCharacterSize(20);
	m_textoIngresarNombre.setFillColor(sf::Color::Yellow);
	m_textoNombreUsuario.setFont(GestorRecursos::ObtenerFuente("recursos/fuentes_texto/ScienceGothic.ttf"));
	m_textoNombreUsuario.setString("_"); 
	m_textoNombreUsuario.setCharacterSize(30);
	m_textoNombreUsuario.setFillColor(sf::Color::White);
	
	m_textoOpcionesFin.setFont(GestorRecursos::ObtenerFuente("recursos/fuentes_texto/ScienceGothic.ttf"));
	m_textoOpcionesFin.setString("R - Reintentar\nM - Menu Principal\nQ - Salir");
	m_textoOpcionesFin.setCharacterSize(20);
	m_textoOpcionesFin.setFillColor(sf::Color::White);
	
	GenerarMapa();
	m_agil = new Agil(700.0f, 300.0f);
}

Nivel::~Nivel() {
	delete m_agil;
	for (size_t i = 0; i < m_enemigos.size(); i++) {
		delete m_enemigos[i];
	}
	m_enemigos.clear();
}
void Nivel::GenerarMapa(){
	m_matrizDatos.resize(FILAS, std::vector<int>(COLUMNAS));
	
	// Bordes del mapa
	for (int y = 0; y < FILAS; y++) {
		for (int x = 0; x < COLUMNAS; x++) {
			if (y == 0 || y == FILAS - 1 || x == 0 || x == COLUMNAS - 1) {
				m_matrizDatos[y][x] = TILE_PARED;
			}
		}
	}
	// Pilares en las 4 esquinas (de 3x3)
	for (int movY = 0; movY < 3; movY++) {
		for (int movX = 0; movX < 3; movX++) {
			m_matrizDatos[5 + movY][5 + movX] = TILE_PARED;                    // Arriba izq
			m_matrizDatos[5 + movY][COLUMNAS - 8 + movX] = TILE_PARED;         // Arriba der
			m_matrizDatos[FILAS - 8 + movY][5 + movX] = TILE_PARED;            // Abajo izq
			m_matrizDatos[FILAS - 8 + movY][COLUMNAS - 8 + movX] = TILE_PARED; // Abajo der
		}
	}
	
	// Algunos muros 
	for (int x = 20; x < 35; x++) {
		m_matrizDatos[20][x] = TILE_PARED;  // Muro horizontal arriba
	}
	for (int x = COLUMNAS - 35; x < COLUMNAS - 20; x++) {
		m_matrizDatos[FILAS - 21][x] = TILE_PARED;  // Muro horizontal abajo
	}
}

bool Nivel::HayColision(const sf::FloatRect& caja) {
	int tileIzq = static_cast<int>(caja.left / TAMANO_TILE);
	int tileDer = static_cast<int>((caja.left + caja.width) / TAMANO_TILE);
	int tileArr = static_cast<int>(caja.top / TAMANO_TILE);
	int tileAbj = static_cast<int>((caja.top + caja.height) / TAMANO_TILE);
	
	// Verificar límites del mapa
	if (tileIzq < 0 || tileDer >= COLUMNAS || tileArr < 0 || tileAbj >= FILAS) {
		return true;
	}
	
	// Revisar si hay paredes
	for (int y = tileArr; y <= tileAbj; y++) {
		for (int x = tileIzq; x <= tileDer; x++) {
			if (m_matrizDatos[y][x] == TILE_PARED) {
				return true;
			}
		}
	}
	
	return false;
}

void Nivel::Actualizar(Juego &j) {
	// Obtiene el tiempo desde la ultima vez que se llamo
	float dt = m_relojFrame.restart().asSeconds();
	if (m_estaPausado or m_juegoTerminado) {
		return; 
	}
	if (m_agil->EstaVivo() == false){
		m_juegoTerminado = true;

	}
	m_tiempoJuego += dt;
	std::stringstream ss;
	ss << "Tiempo: " << (int)m_tiempoJuego << "s"; 
	m_textoTiempo.setString(ss.str());
	
	// Si pasaron más de 150 vueltas crea un nuevo enemigo
	m_contadorTiempo++;
	if (m_contadorTiempo > 150) {
		int xRandom = (rand() % (COLUMNAS - 4)) + 2; // Entre columna 2 y antepenúltima
		int yRandom = (rand() % (FILAS - 4)) + 2;    // Entre fila 2 y antepenúltima
		
		// Convertir coordenadas de grilla a pixeles
		float posX = xRandom * TAMANO_TILE;
		float posY = yRandom * TAMANO_TILE;
		
		Enemigo* nuevoEnemigo = new Enemigo(posX, posY, m_agil);
		m_enemigos.push_back(nuevoEnemigo);
		m_contadorTiempo = 0;
	}
	// Actualiza al jugador
	m_agil->ProcesarEntrada();
	m_agil->GuardarPosicion();
	m_agil->Actualizar();
	
	// Corrige si choca con una pared
	if (HayColision(m_agil->ObtenerCaja())) {
		m_agil->RestaurarPosicion();
	}
	// Verifica si los enemigos chocan con una pared
	for (size_t i = 0; i < m_enemigos.size(); i++) {
		m_enemigos[i]->GuardarPosicion();
		m_enemigos[i]->Actualizar();
		if (HayColision(m_enemigos[i]->ObtenerCaja())) {
			m_enemigos[i]->RestaurarPosicion(); 
		}
	}
	// Colisiones entre los enemigos y el jugador
	for (size_t i = 0; i < m_enemigos.size(); i++) {
		if (m_enemigos[i]->EstaVivo()) {
			m_enemigos[i]->ResolverColision(*m_agil);
		}
	}
	// Colisiones entre los enemigos mismos
	for (size_t i = 0; i < m_enemigos.size(); i++) {
		for (size_t j = i + 1; j < m_enemigos.size(); j++) {
			if (m_enemigos[i]->EstaVivo() and m_enemigos[j]->EstaVivo()) {
				m_enemigos[i]->ResolverColision(*m_enemigos[j]);
			}
		}
	}
	
	std::vector<BolaEnergia>* listaBolas = m_agil->ObtenerBolas();
	
	// Recorre todos los enemigos por cada bola y checkea si se interseccionan
	if (listaBolas != nullptr and (listaBolas->empty()) == false) {
		for (int i = listaBolas->size() - 1; i >= 0; i--) {
			bool bolaExploto = false;
			sf::FloatRect cajaBola = (*listaBolas)[i].sprite.getGlobalBounds();
			
			for (int j = m_enemigos.size() - 1; j >= 0; j--) {
				if (m_enemigos[j]->EstaVivo()) {
					if (cajaBola.intersects(m_enemigos[j]->ObtenerCaja())) {
						m_enemigos[j]->RecibirAtaque(1); 
						bolaExploto = true;
						break; 
					}
				}
			}
			// Si explotó, la borra de la lista original
			if (bolaExploto) {
				listaBolas->erase(listaBolas->begin() + i);
			}
		}
	}
}
void Nivel::Dibujar(RenderWindow &ventana) {
	ventana.clear(Color(70, 125, 0));  // Verde pasto
	ventana.draw(m_textoTiempo);
	// Solo dibujar paredes
	for (int y = 0; y < m_matrizDatos.size(); y++) {
		for (int x = 0; x < m_matrizDatos[y].size(); x++) {
			if (m_matrizDatos[y][x] == TILE_PARED) {
				Sprite s;
				s.setTexture(GestorRecursos::ObtenerTextura("recursos/texturas/Tiles/tile_0126.png"));
				s.setPosition(x * TAMANO_TILE, y * TAMANO_TILE);
				ventana.draw(s);
			}
		}
	}
	m_agil->Dibujar(ventana);
	for (size_t i = 0; i < m_enemigos.size(); i++) {
		m_enemigos[i]->Dibujar(ventana);
	}
	
	if (m_estaPausado and m_juegoTerminado == false) {
		// 	Centra y Dibuja el titulo
		Vector2f centro(ventana.getSize().x / 2.0f, ventana.getSize().y / 2.0f);
		ventana.draw(m_fondoPausa); 
		FloatRect b = m_textoTituloPausa.getLocalBounds();
		m_textoTituloPausa.setOrigin(b.width / 2, b.height / 2);
		m_textoTituloPausa.setPosition(centro.x, centro.y - 50);
		ventana.draw(m_textoTituloPausa);
		
		// Centra y Dibuja opciones
		b = m_textoOpciones.getLocalBounds(); 
		m_textoOpciones.setOrigin(b.width / 2, b.height / 2);
		m_textoOpciones.setPosition(centro.x, centro.y + 30);
		ventana.draw(m_textoOpciones);
		
	}
	
	if (m_juegoTerminado) {
		ventana.draw(m_fondoPausa);
		Vector2f centro(ventana.getSize().x / 2.0f, ventana.getSize().y / 2.0f);
		
		// Título "HAS MUERTO"
		FloatRect b = m_textoFin.getLocalBounds();
		m_textoFin.setOrigin(b.width / 2, b.height / 2);
		m_textoFin.setPosition(centro.x, centro.y - 150); // Un poco mas arriba
		ventana.draw(m_textoFin);
		
		// Instrucción
		b = m_textoIngresarNombre.getLocalBounds();
		m_textoIngresarNombre.setOrigin(b.width / 2, b.height / 2);
		m_textoIngresarNombre.setPosition(centro.x, centro.y - 50);
		ventana.draw(m_textoIngresarNombre);
		
		// Nombre que escribe el usuario
		b = m_textoNombreUsuario.getLocalBounds();
		m_textoNombreUsuario.setOrigin(b.width / 2, b.height / 2);
		m_textoNombreUsuario.setPosition(centro.x, centro.y); 
		ventana.draw(m_textoNombreUsuario);
		
		// Opciones (R, M, Q)
		b = m_textoOpcionesFin.getLocalBounds();
		m_textoOpcionesFin.setOrigin(b.width / 2, b.height / 2);
		m_textoOpcionesFin.setPosition(centro.x, centro.y + 100);
		ventana.draw(m_textoOpcionesFin);
	}
	ventana.display();
}
void Nivel::ProcesarEventos(Juego &j, Event &e) {
	if (m_juegoTerminado) {
		// Escritura del nombre
		if (!m_yaGuardo) {
			if (e.type == Event::TextEntered) {
				char caracterIngresado = static_cast<char>(e.text.unicode);
				if (std::isalnum(caracterIngresado) && m_nombreJugador.size() < 10) {
					m_nombreJugador += caracterIngresado;
				}
			}
			if (e.type == Event::KeyPressed) {
				// Borrar caracter
				if (e.key.code == Keyboard::BackSpace && m_nombreJugador.size() > 0) {
					m_nombreJugador.pop_back();
				}
				// Guardar 
				if (e.key.code == Keyboard::Return) {
					if (m_nombreJugador.size() > 0) { 
						ManejadorPuntajes::GuardarPuntaje(m_nombreJugador, (int)m_tiempoJuego);
						m_yaGuardo = true; 
						m_textoIngresarNombre.setString("¡Puntaje Guardado!");
						m_textoIngresarNombre.setFillColor(sf::Color::Green);
					}
				}
			}
			// Mueve el cursor
			m_textoNombreUsuario.setString(m_nombreJugador + "_");
			
		}else if (e.type == Event::KeyPressed) { //Otras opciones
			if (e.key.code == Keyboard::R) j.PonerEscena(new Nivel());
			else if (e.key.code == Keyboard::M) j.PonerEscena(new Menu());
			else if (e.key.code == Keyboard::Q) exit(0);
		}
		return; // Retorna para no procesar pausa
	}
	
	// Logica de pausa
	if (e.type == Event::KeyPressed) {
		if (e.key.code == Keyboard::Escape) {
			m_estaPausado = !m_estaPausado; 
		}
		if (m_estaPausado and e.key.code == Keyboard::Q) {
			exit(0); 
		}
	}
}
