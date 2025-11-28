
#ifndef AGIL_H
#define AGIL_H

#include "Personaje.h"
#include <SFML/Graphics.hpp>

using namespace sf;
class Agil : public Personaje{
public:
	Agil(float x, float y);
	~Agil() override {};
	
	void ProcesarEntrada() override;
	void Actualizar() override;
	float ObtenerAlturaPies() const override;
	void TocoElSuelo(const float ALTURA_SUELO) override;
	void Dibujar(RenderWindow &ventana) override;
	
private:
	// Constantes de juego específicas de Agil
	const float VELOCIDAD_MAXIMA = 30.0f;
	const float FUERZA_SALTO = -20.0f;
	const float GRAVEDAD = 1.2f;
	// Características única del ágil
	bool m_saltoPresionadoAntes;
	bool m_puedeDobleSalto;
};
#endif // AGIL_H
