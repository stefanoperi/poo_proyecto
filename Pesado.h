#ifndef PESADO_H
#define PESADO_H

#include "Personaje.h"
#include <SFML/Graphics.hpp>

using namespace sf;

class Pesado : public Personaje {
public:
	Pesado(float x, float y);
	~Pesado() override {};
	
	void ProcesarEntrada() override;
	void Actualizar() override;
	float ObtenerAlturaPies() const override;
	void TocoElSuelo(const float ALTURA_SUELO) override;
	void Dibujar(RenderWindow &ventana) override;
	
private:
	const float VELOCIDAD_MAXIMA = 15.0f; 
	const float FUERZA_SALTO = -12.0f; 
	const float GRAVEDAD = 1.5f; 
	
	bool m_saltoPresionadoAntes;
};

#endif // PESADO_H
