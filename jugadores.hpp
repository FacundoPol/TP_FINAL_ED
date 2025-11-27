
#include <iostream>
#include <stdio.h>
#include <string.h>

typedef FILE *parchivo;

typedef struct tnodoj *pnodoj;

struct tjugador{
	tcad nombre;
	tcad apellido;
	tcad signo_zodical;
	tcad alias;
	int cant_jueg_gan;
	int mejor_puntaje;
	int puntaje_acumulado;
};

struct tnodoj{
	tjugador jugador;
	pnodoj izq;
	pnodoj der;
};

//PROCEDIMIENTOS Y FUNCIONES USADAS PARA JUGADORES Y ESTRUCTURAS

void iniciar_jugadores_abb(pnodoj &arbol)
{
	arbol=NULL;
}

int contar_jugadores_abb(pnodoj arbol)
{
	int i,d;
	if(arbol==NULL)
	{
		return 0;
	}
	else
	{
		 i = contar_jugadores_abb(arbol->izq);
		d = contar_jugadores_abb(arbol->der);
		return i + d  + 1;
	}
}

void actualizar_jugador(pnodoj &arbol,tjugador jugador,bool perdio,int nuevo_puntaje)
{
	tjugador jugadorc = arbol->jugador;
	if(perdio==false)
		jugadorc.cant_jueg_gan = jugador.cant_jueg_gan +1;
	
	
	if(nuevo_puntaje>jugadorc.mejor_puntaje)
		jugadorc.mejor_puntaje = nuevo_puntaje;
	
	
	jugadorc.puntaje_acumulado = jugadorc.puntaje_acumulado+nuevo_puntaje;
	
	cout<<"PUNTAJES JUGADOR ACTUALIZADOS"<<endl;
	arbol->jugador = jugadorc;
}

pnodoj busqueda_jugador_abb(pnodoj arbol,tcad jugador_buscado)
{
	pnodoj aux = NULL;
	if(arbol!=NULL)
	{
		if(strcmp(arbol->jugador.alias,jugador_buscado)==0)
			aux = arbol;
		else
		{
			aux=busqueda_jugador_abb(arbol->izq,jugador_buscado);
			if(aux==NULL)
				aux=busqueda_jugador_abb(arbol->der,jugador_buscado);
		}
		
	}
	return aux;
}


void cargar_jugador_abb(tjugador &jugador,pnodoj arbol)
{
	pnodoj aux = NULL;
	bool encontrado;
	
	cout<<"--- JUGADOR ---"<<endl;
	do{
		cout<<"NOMBRE: ";
		fflush(stdin);
		gets(jugador.nombre);
		if(strlen(jugador.nombre)<4)
			cout<<"EL NOMBRE NO PUEDE SER MENOR A CUATRO LETRAS"<<endl;
	}while(strlen(jugador.nombre)<4);
	
	do{
		cout<<"APELLIDO: ";
		gets(jugador.apellido);
		if(strlen(jugador.apellido)<4)
			cout<<"EL APELLIDO NO PUEDE SER MENOR A CUATRO LETRAS"<<endl;
	}while(strlen(jugador.apellido)<4);
	
	cout<<"SIGNO ZODIACAL: ";
	gets(jugador.signo_zodical);
	
	do{
		encontrado = false;
		cout<<"ALIAS: ";
		gets(jugador.alias);
		if(strlen(jugador.alias)<4)
			cout<<"EL ALIAS NO PUEDE SER MENOR A CUATRO LETRAS"<<endl;
		else
		{
			aux = busqueda_jugador_abb(arbol,jugador.alias);
			if(aux!=NULL){
				encontrado=true;
				cout<<"EL ALIAS YA EXISTE ELIGE OTRO"<<endl;
			}
		}
	}while(strlen(jugador.alias)<4 || encontrado == true);
	
	jugador.puntaje_acumulado=0;
	jugador.cant_jueg_gan=0;
	jugador.mejor_puntaje=0;
}


void archivo_jugador_abb(pnodoj &arbol,parchivo &jugadores)
{
	pnodoj eliminado;
	if(arbol!=NULL)
	{
		archivo_jugador_abb(arbol->izq,jugadores);
		archivo_jugador_abb(arbol->der,jugadores);
		fwrite(&arbol->jugador,sizeof(arbol->jugador),1,jugadores);
		eliminado=arbol;
		delete(eliminado);
	}
}

void guardar_jugador_archivo(parchivo &jugadores,pnodoj &nodo)
{
	tjugador jugador;
	
	jugadores = fopen("jugadores.txt","wb");
	
	archivo_jugador_abb(nodo,jugadores);
	
	jugador = nodo->jugador;
	
	fclose(jugadores);
}


void mostrar_jugador(tjugador jugador)
{
	cout<<endl;
	cout<<"--- JUGADOR ---"<<endl;
	cout<<"NOMBRE: "<<jugador.nombre<<endl;
	cout<<"APELLIDO: "<<jugador.apellido<<endl;
	cout<<"SIGNO ZODIACAL: "<<jugador.signo_zodical<<endl;
	cout<<"ALIAS: "<<jugador.alias<<endl;
	cout<<"CANTIDAD JUEGOS GANADOS: "<<jugador.cant_jueg_gan<<endl;
	cout<<"MEJOR PUNTAJE: "<<jugador.mejor_puntaje<<endl;
	cout<<"PUNTAJE ACUMULADO: "<<jugador.puntaje_acumulado<<endl;
	cout<<endl;
}

void mostrar_jugador_abb(pnodoj arbol)
{
	if(arbol!=NULL)
	{
		mostrar_jugador_abb(arbol->izq);
		mostrar_jugador(arbol->jugador);
		mostrar_jugador_abb(arbol->der);
	}
}

tjugador cargar_jugador_mod(tjugador jugador)
{
	cout<<"--- JUGADOR ---"<<endl;
	do{
		cout<<"NOMBRE: ";
		fflush(stdin);
		gets(jugador.nombre);
		if(strlen(jugador.nombre)<4)
			cout<<"EL NOMBRE NO PUEDE SER MENOR A CUATRO LETRAS"<<endl;
	}while(strlen(jugador.nombre)<4);
	
	do{
		cout<<"APELLIDO: ";
		gets(jugador.apellido);
		if(strlen(jugador.apellido)<4)
			cout<<"EL APELLIDO NO PUEDE SER MENOR A CUATRO LETRAS"<<endl;
	}while(strlen(jugador.apellido)<4);
	
	cout<<"SIGNO ZODIACAL: ";
	gets(jugador.signo_zodical);
	
	return jugador;
}


void modificar_jugador_abb(pnodoj &arbol, tcad alias)
{
	pnodoj aux;
	tjugador jugador;
	
	if(busqueda_jugador_abb(arbol,alias)==NULL)
		cout<<"JUGADOR NO ENCONTRADO"<<endl;
	else
	{
		aux=busqueda_jugador_abb(arbol,alias);
		jugador = cargar_jugador_mod(aux->jugador);
		aux->jugador = jugador;
	}
}

void cambio(tjugador &jugador,tjugador &nuevo)
{
	tjugador aux;
	aux=jugador;
	jugador=nuevo;
	nuevo = aux;
}
pnodoj menor_mayores(pnodoj elegido,pnodoj &menor)
{
	pnodoj aux;
	if(menor->izq!=NULL)
		aux=menor_mayores(elegido,menor->izq);
	else
	{
		cambio(elegido->jugador,menor->jugador);
		aux=menor;
		menor=menor->der;
	}
	
	return aux;
}

pnodoj eliminar_jugador_abb(pnodoj &arbol,tcad alias)
{
	pnodoj aux;
	
	if(arbol == NULL)
		aux=NULL;
	else
	{
		if(strcmp(arbol->jugador.alias,alias)>0)
			aux=eliminar_jugador_abb(arbol->izq,alias);
		else
		{
			if(strcmp(arbol->jugador.alias,alias)<0)
				aux=eliminar_jugador_abb(arbol->der,alias);
			else
			{
				aux=arbol;
				if(arbol->izq==NULL)
					arbol=arbol->der;
				else
				{
					if(arbol->der==NULL)
						arbol=arbol->izq;
					else
						aux=menor_mayores(arbol,arbol->der);
				}
			}
		}
	}
	
	return aux;
}



void crear_nodo_abb(pnodoj &nuevo,tjugador jugador)
{
	nuevo = new tnodoj;
	if(nuevo!=NULL)
	{
		strcpy(nuevo->jugador.nombre,jugador.nombre);
		strcpy(nuevo->jugador.apellido,jugador.apellido);
		strcpy(nuevo->jugador.signo_zodical,jugador.signo_zodical);
		strcpy(nuevo->jugador.alias,jugador.alias);
		nuevo->jugador.cant_jueg_gan = jugador.cant_jueg_gan;
		nuevo->jugador.mejor_puntaje = jugador.mejor_puntaje;
		nuevo->jugador.puntaje_acumulado = jugador.puntaje_acumulado;
		nuevo->izq=NULL;
		nuevo->der=NULL;
	}
}

pnodoj crear_jugador_abb(pnodoj arbol)
{
	pnodoj nuevo;
	tjugador jugador;
	cargar_jugador_abb(jugador,arbol);
	crear_nodo_abb(nuevo,jugador);
	
	return nuevo;
}


void insertar_archivo_abb(pnodoj &arbol,pnodoj nuevo)
{
	if(arbol==NULL)
		arbol=nuevo;
	else
	{
		if(strcmp(nuevo->jugador.alias,arbol->jugador.alias)>0)
			insertar_archivo_abb(arbol->der,nuevo);
		else
			insertar_archivo_abb(arbol->izq,nuevo);
	}
}


void insercion_jugadores_abb_archivo(pnodoj &arbol,parchivo jugadores)
{
	pnodoj nuevo;
	tjugador jugador;
	jugadores = fopen("jugadores.txt","rb");
	if(jugadores!=NULL)
	{
		
		while(!feof(jugadores))
		{
			fread(&jugador,sizeof(jugador),1,jugadores);
			if(!feof(jugadores)){
				crear_nodo_abb(nuevo,jugador);
				insertar_archivo_abb(arbol,nuevo);
			}
		}
	}
	fclose(jugadores);
}

void insercion_jugadores_abb(pnodoj &arbol,pnodoj nuevo)
{
	
	if(arbol==NULL)
		arbol=nuevo;
	else
	{
		if(strcmp(nuevo->jugador.alias,arbol->jugador.alias)>0)
			insercion_jugadores_abb(arbol->der,nuevo);
		else
			insercion_jugadores_abb(arbol->izq,nuevo);
	}
	
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
	cout<<endl;
	cout<<"INGRESE OPCION: ";
	cin>>op;
}

void seleccion_menu(int op,parchivo &jugadores,pnodoj &arbol)
{
	tcad alias;
	pnodoj nuevo;
	pnodoj aux;
	switch(op)
	{
	case 1: 
		nuevo = crear_jugador_abb(arbol);
		insercion_jugadores_abb(arbol,nuevo);
		break;
	case 2: 
		mostrar_jugador_abb(arbol);
		break;
	case 3: 
		cout<<"ALIAS JUGADOR BUSCADO: ";
		fflush(stdin);
		gets(alias);
		aux = busqueda_jugador_abb(arbol,alias);
		if(aux!=NULL)
			mostrar_jugador(aux->jugador);
		else
			cout<<"NO EXISTE EL JUGADOR BUSCADO"<<endl;
		break;
	case 4:
		cout<<"ALIAS JUGADOR A MODIFICAR: ";
		fflush(stdin);
		gets(alias);
		modificar_jugador_abb(arbol,alias);
		break;
	case 5:
		cout<<"JUGADOR A BORRAR: ";
		fflush(stdin);
		gets(alias);
		aux = busqueda_jugador_abb(arbol,alias);
		if(aux!=NULL)
		{
			eliminar_jugador_abb(arbol,alias);
			cout<<"EL JUGADOR HA SIDO BORRADO CON EXITO"<<endl;
		}
		else
		   cout<<"EL JUGADOR INGRESADO NO EXISTE"<<endl;
		break;
	default:
		cout<<"SALISTE"<<endl;
		break;
	}
	
}
