#ifndef NIVELES_H
#define NIVELES_H
#include "NivelBase.h"

// Distintos mapas para cada nivel
class Nivel1 : public NivelBase {
protected:
	void GenerarMapa() override;
public:
	Nivel1() : NivelBase(0) {
		GenerarMapa(); 
	}
};

class Nivel2 : public NivelBase {
protected:
	void GenerarMapa() override;
public:
	Nivel2() : NivelBase(1) {
		GenerarMapa();
	}
};

class Nivel3 : public NivelBase {
protected:
	void GenerarMapa() override;
public:
	Nivel3() : NivelBase(2) {
		GenerarMapa();
	}
};

class Nivel4 : public NivelBase {
protected:
	void GenerarMapa() override;
public:
	Nivel4() : NivelBase(3) {
		GenerarMapa();
	}
};

#endif
