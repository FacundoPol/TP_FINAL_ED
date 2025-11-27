#pragma once
#include <iostream>

using namespace std;

const int MAX = 6; 

typedef char tcad[100]; 

typedef struct tregistro{
	tcad nombre;
	int cantidadCaracteres;
	tcad definicion;
	tcad sinonimo;
};

typedef tregistro tcontenedor[MAX];

typedef struct tpila{
	tcontenedor datos;
	int cima;
};

void iniciarPila(tpila &pila){
	pila.cima = -1;
}
	
bool pilaLLena(tpila pila){
	return pila.cima == MAX - 1;
}
	
bool pilaVacia(tpila pila){
	return pila.cima == -1;
}

void agregarPila(tpila &pila, tregistro reg){
	
	if(pilaLLena(pila)){
		cout << "Error: Pila llena. No se puede agregar el registro." << endl;
	} else {
	pila.cima++;
	pila.datos[pila.cima] = reg;	
	}
}

tregistro quitarPila(tpila &pila) {
	tregistro resultado; // Inicializacion de seguridad a cero/vacio
	if (pilaVacia(pila)) {
		cout << "pila vacia " << endl;
	} else {
		resultado = pila.datos[pila.cima];	
		pila.cima--;
	}
	return resultado;
}
