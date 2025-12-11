#ifndef MANEJADORPUNTAJES_H
#define MANEJADORPUNTAJES_H

#include <string>
#include <vector>

struct EntradaPuntaje {
	std::string nombre;
	int tiempo; 
};

class ManejadorPuntajes {
public:
	// Declaramos metodos estaticos para poder llamarlos sin instanciar la clase
	static void GuardarPuntaje(std::string nombre, int tiempo);
	static std::vector<EntradaPuntaje> ObtenerMejoresPuntajes();
	
private:
	// Metodo interno para el ordenamiento
	static bool CompararPuntajes(const EntradaPuntaje& a, const EntradaPuntaje& b);
};

#endif
