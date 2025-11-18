#include <iostream>
#include <stdio.h>
#include <string.h>

using namespace std;

#include "jugadores_archivos.hpp"

void menu(int &op);
void seleccion_menu(int op,parchivo &jugadores);

main()
{
	int op;
	parchivo jugadores;
	do{
		menu(op);
		seleccion_menu(op,jugadores);
		system("pause");
		system("cls");
	}while(op!=0);
}

void menu(int &op)
{
	cout<<"OPCIONES: "<<endl;
	cout<<"|1| CREAR"<<endl;
	cout<<"|2| MOSTRAR"<<endl;
	cout<<"|3| BUSCAR"<<endl;
	cout<<"|4| MODIFICAR"<<endl;
	cout<<"|5| BORRAR"<<endl;
	cout<<"|0| SALIR"<<endl;
	cout<<"Ingrese opcion: ";
	cin>>op;
}

void seleccion_menu(int op,parchivo &jugadores)
{
	tjugador jugador;
	tcad alias;
	switch(op)
	{
	case 1: 
		crear_jugador(jugadores,jugador);
		break;
	case 2: 
		mostrar_jugadores(jugadores);
		break;
	case 3: 
		cout<<"ALIAS JUGADOR BUSCADO: ";
		fflush(stdin);
		gets(alias);
		consultar_jugador(jugadores,alias);
		break;
	case 4:
		cout<<"ALIAS JUGADOR A MODIFICAR: ";
		fflush(stdin);
		gets(alias);
		modificar_jugador(jugadores,alias);
		break;
	case 5:
		cout<<"LEGAJO REGISTRO A BORRAR: ";
		fflush(stdin);
		gets(alias);
		borrar_jugador(jugadores,alias);
		break;
	default:
		cout<<"SALISTE"<<endl;
		break;
	}
	
}
