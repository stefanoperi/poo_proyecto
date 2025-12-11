#include "PantallaPuntajes.h"
#include "ManejadorPuntajes.h"
#include "GestorRecursos.h"
#include "Menu.h" // Para volver al menu
#include "Juego.h"
#include "ManejadorPuntajes.h"

PantallaPuntajes::PantallaPuntajes() {
	m_fuente = GestorRecursos::ObtenerFuente("recursos/fuentes_texto/ScienceGothic.ttf");
	
	// Configura el Titulo
	m_titulo.setFont(m_fuente);
	m_titulo.setString("MEJORES JUGADORES");
	m_titulo.setCharacterSize(40);
	m_titulo.setFillColor(sf::Color::Yellow);
	
	// Configura el Texto de Volver
	m_txtVolver.setFont(m_fuente);
	m_txtVolver.setString("Presiona <ESC> para volver");
	m_txtVolver.setCharacterSize(20);
	
	std::vector<EntradaPuntaje> records = ManejadorPuntajes::ObtenerMejoresPuntajes();
	
	// Crea textos para cada record
	for (size_t i = 0; i < records.size(); i++) {
		sf::Text texto;
		texto.setFont(m_fuente);
		
		// Formato: "1. Pepe ...... 120 seg"
		std::string linea = std::to_string(i + 1) + ". " + records[i].nombre +
			" ...... " + std::to_string(records[i].tiempo) + " segundos";
		
		texto.setString(linea);
		texto.setCharacterSize(30);
		texto.setFillColor(sf::Color::White);
		
		m_textosPuntajes.push_back(texto);
	}
	
	if (records.empty()) {
		sf::Text texto;
		texto.setFont(m_fuente);
		texto.setString("Aun no hay puntajes guardados.");
		texto.setCharacterSize(30);
		texto.setFillColor(sf::Color::White);
		m_textosPuntajes.push_back(texto);
	}
}

void PantallaPuntajes::Actualizar(Juego &j) {}

void PantallaPuntajes::ProcesarEventos(Juego &j, sf::Event &e) {
	if (e.type == sf::Event::KeyPressed) {
		if (e.key.code == sf::Keyboard::Escape) {
			// Volver al Menu Principal
			j.PonerEscena(new Menu());
		}
	}
}

void PantallaPuntajes::Dibujar(sf::RenderWindow &ventana) {
	ventana.clear(sf::Color::Black);
	float ancho = (float)ventana.getSize().x;
	float alto = (float)ventana.getSize().y;
	
	sf::FloatRect rTitulo = m_titulo.getGlobalBounds();
	m_titulo.setPosition((ancho - rTitulo.width) / 2.0f, alto * 0.15f); 
	ventana.draw(m_titulo);

	// Dibuja la lista de puntajes centradas
	float alturaInicial = alto * 0.3f; 
	for (size_t i = 0; i < m_textosPuntajes.size(); i++) {
		sf::FloatRect rTexto = m_textosPuntajes[i].getGlobalBounds();
		
		// Centrado horizontal 
		float x = (ancho - rTexto.width) / 2.0f;
		// Posición vertical: Altura inicial + (40 pixeles por cada renglón)
		float y = alturaInicial + (i * 50.0f); 
		
		m_textosPuntajes[i].setPosition(x, y);
		ventana.draw(m_textosPuntajes[i]);
	}
	
	// Dibuja el texto para volver, centrado
	sf::FloatRect rVolver = m_txtVolver.getGlobalBounds();
	m_txtVolver.setPosition((ancho - rVolver.width) / 2.0f, alto * 0.9f); 
	ventana.draw(m_txtVolver);
	
	ventana.display();
}
