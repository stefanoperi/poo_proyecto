#ifndef NIVELES_H
#define NIVELES_H
#include "NivelBase.h"

// Nivel 1: Pilares verticales para cubrirse
class Nivel1 : public NivelBase {
protected:
	void GenerarMapa() override;
public:
	Nivel1() : NivelBase(0) {
		GenerarMapa(); 
	}
};

// Nivel 2: Cruz grande que divide el mapa
class Nivel2 : public NivelBase {
protected:
	void GenerarMapa() override;
public:
	Nivel2() : NivelBase(1) {
		GenerarMapa();
	}
};

// Nivel 3: Patrón de tablero de ajedrez
class Nivel3 : public NivelBase {
protected:
	void GenerarMapa() override;
public:
	Nivel3() : NivelBase(2) {
		GenerarMapa();
	}
};

// Nivel 4: Escombros aleatorios
class Nivel4 : public NivelBase {
protected:
	void GenerarMapa() override;
public:
	Nivel4() : NivelBase(3) {
		GenerarMapa();
	}
};

#endif
