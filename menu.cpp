#include <iostream>
#include <cstring>
#include <string.h>
#include <time.h>
#include "diccionario2.0.hpp "
#include "jugadores.hpp "
#include "vencedores.hpp "
#include "iniciar_juego.hpp"

using namespace std;

typedef FILE *ppalabras;

typedef struct tregistro1{
	tcad nombre;
	int cantidadCaracteres;
	tcad definicion;
	tcad sinonimo;
};

void iniciarJugador(tjugador &jugador);
void iniciarJuego(pnodoj &arbol,tpila &pila,tjugador &jugador);

 main(){
	 srand(time(NULL));
	ppalabras archivo;
	tdiccionario diccionario;
	pnodoj jugador1;
	pnodoj arbol;
	tlistav lista;
	ppalabras jugadores;
	int op;
	pnodo nuevo;
	tcad jugador_buscado;
	tpila pila;
	iniciar_jugadores_abb(arbol);
	insercion_jugadores_abb_archivo(arbol,jugadores);
	iniciarDiccionario(diccionario);
	cargarPalabrasDiccionario(diccionario);
	iniciarPila(pila);
	do{
		system("cls");
		cout<<"---------BIENVENIDO AL JUEGO DE HECHIZO---------"<<endl;
		cout<<" "<<endl;
		cout<<"----------MENU DE OPCIONES----------"<<endl;
		cout<<endl;
		cout<<" |1| -> GESTION DE JUGADORES-"<<endl;
		cout<<" |2| -> GESTION DE PALABRAS"<<endl;
		cout<<" |3| -> INICIAR EL JUEGO"<<endl;
		cout<<" |4| -> VENCEDORES"<<endl;
		cout<<" |5| -> FIN DEL PROGRAMA"<<endl;
		cout<<endl;
		cout<<" SELECCIONE UNA OPCION: ";
		cin>>op;
		switch(op){
		case 1:
			do{
					menu(op);
					seleccion_menu(op,jugadores,arbol);
					system("pause");
					system("cls");
				    }while(op!=0);
			break;
			
		case 2:cout<<"------Acccediendo al submenu de gestion de palabras------"<<endl;
		submenuPalabras(archivo,diccionario,nuevo);
			break;
			
		case 3:cout<<"------Iniciando Juego------"<<endl;
			 if(contarTotalPalabras(diccionario)<6){ 
				 cout<<"no se puede iniciar el juego.por favor cargue mas palabras en el diccionario"<<endl;
			 }
			 else{
				 if(contar_jugadores_abb(arbol)<2){
					 cout<<"debe tener mas de 1 jugador"<<endl;
				}
				 else{
				 cout<<"Ingrese su alias con el jugador que desea jugar: ";
				 fflush(stdin);
				 gets(jugador_buscado);
				 if (strlen(jugador_buscado) == 0 || busqueda_jugador_abb(arbol,jugador_buscado) == NULL ) 
					 cout << "Ingreso alias inválido , jugador no existe." << endl;
				 else{
				 iniciarPila(pila);
				 aleatorioPalabras(diccionario,pila);//carga diccionario
				 jugador1 = busqueda_jugador_abb(arbol,jugador_buscado);
			     iniciarJuego(jugador1,pila,jugador1->jugador);
			        }
			    }
			 }
			break;
			
		case 4:
			menu_vencedores(op);
			seleccion_menu_vencedores(op,lista,arbol);
			break;
		
		case 5: cout<<"fin del programa " << endl;
		
		copiarArchivo(diccionario,archivo);
		iniciarDiccionario(diccionario);
		default:cout<<"Seleccione una opcion correcta: ";
		break;
		}
		
		system("pause");
	} while(op!=5);
	guardar_jugador_archivo(jugadores,arbol);
	
 }
