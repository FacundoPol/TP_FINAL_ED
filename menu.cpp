#include <iostream>
#include <cstring>
#include <string.h>
#include <time.h>
#include "diccionario2.0.hpp "
#include "pilapalabras.hpp "
#include "jugadores.hpp "
#include "vencedores.hpp "

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
		cout<<"1-GESTION DE JUGADORES-"<<endl;
		cout<<"2-GESTION DE PALABRAS"<<endl;
		cout<<"3-INICIAR EL JUEGO"<<endl;
		cout<<"4-VENCEDORES"<<endl;
		cout<<"5-FIN DEL PROGRAMA"<<endl;
		cout<<"ELIJA UNA OPCION: ";
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
	crear_jugador(jugadores,arbol);
	
 }	
	
	
		
	void iniciarJuego(pnodoj &arbol,tpila &pila,tjugador &jugador){
		
		int puntaje = 7;
		
		bool perdio=false;
		int cantidadDePalabrasAdivinadas=0;
		
		while(!pilaVacia(pila) && !perdio){
			
        int intentos=3;
		int respuesta;
		bool adivino=false;
		
		tregistro palabraEspejo = quitarPila(pila);
		cout<<"Siguiente palabra"<<endl;
		do{
			system("cls");
			tcad palabraParaAdivinar;
		    if(puntaje>0){
				
			cout<<" "<<endl;
			cout<<"Puntaje: " << " : " << puntaje << endl;
			cout<<"Tiene " << intentos << " intentos por palabra "<<endl;
			cout<<"*************************************"<<endl;
			cout<<"----Desea usar una pista para acceder a la palabra----"<<endl;
			cout<<"PISTA 1 -> Cantidad de letras - precio 2 puntos"<<endl;
			cout<<"PISTA 2 -> Primera letra - precio 3 puntos"<<endl;
			cout<<"PISTA 3 -> Definicion de palabra - precio 4 puntos"<<endl;
			cout<<"PISTA 4 -> Sinonimo de palabra - precio 4 puntos"<<endl;
			cout<<"Ingrese 0 si no desea elegir una pista"<<endl;
			cout<<"Ingrese una opcion: ";
			cin>>respuesta;
			switch(respuesta){
			case 1:
				cout<<"PISTA 1 - " << palabraEspejo.cantidadCaracteres << endl;
			    cout<<"INGRESE LA PALABRA A ADIVINAR: ";	
			    fflush(stdin);
		 	    gets(palabraParaAdivinar);
			if(strcmp(palabraParaAdivinar,palabraEspejo.nombre)==0){
					cout<<"Adivinaste la palabra -obtienes recompensa de 7 puntos"<<endl;
				    puntaje=puntaje+7;
					puntaje=puntaje-2;
					adivino=true;
			        intentos=0;
			    }
			else{
				puntaje=puntaje-2;
				cout<<"Lo lamento esa no es  la palabra - sigue intentando"<<endl;
				intentos--;
			}
			break;
			
			case 2:
				cout<<"PISTA 2 - " << palabraEspejo.nombre[0] << endl;
				cout<<"INGRESE LA PALABRA A ADIVINAR: ";	
				fflush(stdin);
				gets(palabraParaAdivinar);
				if(strcmp(palabraParaAdivinar,palabraEspejo.nombre)==0){
					cout<<"Adivinaste la palabra -obtienes recompensa de 7 puntos"<<endl;
					puntaje=puntaje+7;
					puntaje=puntaje-3;
				    adivino=true;
				    intentos=0;
				}
				else{
					puntaje=puntaje-3;
					cout<<"Lo lamento esa no es  la palabra - sigue intentando"<<endl;
					intentos--;
				}
				break;
			
			case 3 :
				cout<<"PISTA 3 - " << palabraEspejo.definicion << endl;
				cout<<"INGRESE LA PALABRA A ADIVINAR: ";	
				fflush(stdin);
				gets(palabraParaAdivinar);
				if(strcmp(palabraParaAdivinar,palabraEspejo.nombre)==0){
					 cout<<"Adivinaste la palabra - obtienes recompensa de 7 puntos"<<endl;
					 puntaje=puntaje+7;
					 puntaje=puntaje-4;
                     adivino=true;
				     intentos=0;
				     }
				else{
					puntaje=puntaje-4;
					intentos--;
					cout<<"Lo lamento esa no es  la palabra-sigue intentando"<<endl;
				}
				break;
				
            case 4:
				cout<<"PISTA 4 - " << palabraEspejo.sinonimo << endl;
				cout<<"INGRESE LA PALABRA A ADIVINAR: ";	
				fflush(stdin);
				gets(palabraParaAdivinar);
				if(strcmp(palabraParaAdivinar,palabraEspejo.nombre)==0){
					cout<<"Adivinaste la palabra - obtienes recompensa de 7 puntos"<<endl;
					puntaje=puntaje+7;
					puntaje=puntaje-5;
		            adivino=true;
				    intentos=0;
				}
				else{
					puntaje=puntaje-5;
					cout<<"Lo lamento esa no es  la palabra - sigue intentando"<<endl;
					intentos--;
				}
				break;
				
			case 0:
				cout<<"INGRESE LA PALABRA A ADIVINAR: ";	
				fflush(stdin);
				gets(palabraParaAdivinar);
				if(strcmp(palabraParaAdivinar,palabraEspejo.nombre)==0){
					cout<<"Adivinaste la palabra - obtienes recompensa de 7 puntos"<<endl;
					puntaje=puntaje+7;
				    adivino=true;
				    intentos=0;
				 }
				else{
					cout<<"Lo siento esa no es la palabra - siguen intentando"<<endl;
					intentos--;
				}
				break;
			
			default:cout<<"OPCION INCORRECTA"<<endl;
			    break;
		     	}
			}
			else{
				cout<<"<----  PERDISTE TE CONVERTISTE EN PIEDRA  ---->"<<endl;
				intentos=0;
			}
			system("pause");
		} while(intentos>0 && !adivino);
		
		if(!adivino) {
			perdio = true;
		} else {
			cantidadDePalabrasAdivinadas++;
		}
	}
		if(perdio) {
			cout << "<---- PERDISTE TE CONVERTISTE EN PIEDRA ---->" << endl;
			
		} else if(cantidadDePalabrasAdivinadas == 6) {
			cout << "------> FELICIDADES!!! - GANASTE EL JUEGO - LA PRINCESA HA SIDO LIBERADA - BIEN HECHO <------"<< endl;
		}
	
		actualizar_jugador(arbol,jugador,perdio,puntaje);
	}
