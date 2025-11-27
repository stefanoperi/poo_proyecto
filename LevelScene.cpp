#include "LevelScene.h"
#include <iostream>
using namespace sf;

// 1. CONSTRUCTOR: Nace la escena
LevelScene::LevelScene() {
	// Creamos al personaje en la memoria dinámica (Heap).
	// Posición inicial (X=100, Y=100) para que empiece cayendo.
	m_hero = new Personaje(100.0f, 100.0f);
}

// 2. DESTRUCTOR: Gestión de Memoria
LevelScene::~LevelScene() {
	// ?? CRÍTICO: C++ no tiene recolector de basura.
	// Si hiciste un 'new', tienes que hacer un 'delete'.
	// Si te olvidas esto, cada vez que reinicies el nivel, la memoria se llenará (Memory Leak).
	delete m_hero; 
}

// 3. ACTUALIZAR: El cerebro del nivel
void LevelScene::Actualizar(Juego &j) {
	// PASO A: Input
	// Le decimos al personaje: "¿El usuario tocó alguna tecla? Si es así, prepárate para moverte".
	m_hero->ProcesarEntrada();
	
	// PASO B: Física
	// Le decimos: "Aplica gravedad y muévete según tu velocidad actual".
	m_hero->Actualizar();
	
	// PASO C: Colisiones (El piso "mágico")
	// Definimos que el suelo está en la coordenada Y = 400.
	float altura_suelo = 400.0f;
	
	// Obtenemos el rectángulo del personaje
	FloatRect limites = m_hero->ObtenerLimites();
	
	// VERIFICACIÓN: ¿Los pies del personaje (top + height) cruzaron la línea del suelo?
	if (limites.top + limites.height >= altura_suelo) {
		
		// CORRECCIÓN: Llamamos al método que lo "sube" al ras del suelo y frena la caída.
		m_hero->TocarSuelo(altura_suelo);
	}
}

// 4. DIBUJAR: Pintar la pantalla
void LevelScene::Dibujar(RenderWindow &ventana) {
	// A. Limpiar pantalla
	// Usamos un color celeste oscuro ({50, 50, 80}) para diferenciarlo del menú negro.
	ventana.clear({50, 50, 80}); 
	
	// B. Dibujar el "Piso" (Solo visual, para que sepas dónde está la colisión)
	// Creamos un rectángulo verde que ocupe todo el ancho.
	RectangleShape piso({(float)ventana.getSize().x, 20.0f});
	piso.setFillColor({50, 200, 50}); // Verde
	piso.setPosition(0, 400.0f);      // En Y=400, donde está nuestra colisión invisible
	ventana.draw(piso);
	
	// C. Dibujar al Héroe
	// Delegamos el dibujo al propio objeto personaje.
	m_hero->Dibujar(ventana);
	
	// D. Mostrar todo (Swap Buffers)
	ventana.display();
}

// 5. EVENTOS: Control general
void LevelScene::ProcesarEventos(Juego &j, Event &e) {
	// Si el usuario toca ESCAPE, cerramos la ventana.
	if (e.type == Event::KeyPressed) {
		if (e.key.code == Keyboard::Escape) {
			// Nota: Para cerrar la ventana, necesitas acceso a ella. 
			// Si Juego tiene un método para obtener la ventana, úsalo.
			// O simplemente no hagas nada por ahora.
			// j.ObtenerVentana().close(); 
		}
	}
}
