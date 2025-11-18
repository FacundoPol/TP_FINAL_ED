#include <iostream>
#include <stdio.h>
#include <string.h>


typedef char tcad[50];

typedef FILE *parchivo;

struct tjugador{
	tcad nombre;
	tcad apellido;
	tcad signo_zodical;
	tcad alias;
	int cant_jueg_gan;
	int mejor_puntaje;
	int puntaje_acumulado;
};

void cargar_jugador(tjugador &jugador,parchivo jugadores)
{
	bool encontrado;
	tjugador jugador_lista;
	
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
				jugadores = fopen("jugadores.txt","rb");
				while(!feof(jugadores)&&!encontrado)
				{
					fread(&jugador_lista,sizeof(jugador_lista),1,jugadores);
					if(strcmp(jugador.alias,jugador_lista.alias)==0)
					{
						encontrado=true;
						cout<<"EL ALIAS YA EXISTE ELIGE OTRO"<<endl;
					}
				}
				fclose(jugadores);
			}
		}while(strlen(jugador.alias)<4 || encontrado == true);
	
	jugador.puntaje_acumulado=7;
	jugador.cant_jueg_gan=0;
	jugador.mejor_puntaje=0;
}

void crear_jugador(parchivo &jugadores,tjugador jugador)
{
	cargar_jugador(jugador,jugadores);
	
	jugadores = fopen("jugadores.txt","ab");
	
	fwrite(&jugador,sizeof(jugador),1,jugadores);
	
	fclose(jugadores);
	
}

void mostrar_jugador(tjugador jugador)
{
	cout<<"--- JUGADOR ---"<<endl;
	cout<<"NOMBRE: "<<jugador.nombre<<endl;
	cout<<"APELLIDO: "<<jugador.apellido<<endl;
	cout<<"SIGNO ZODIACAL: "<<jugador.signo_zodical<<endl;
	cout<<"ALIAS: "<<jugador.alias<<endl;
	cout<<"CANTIDAD JUEGOS GANADOS: "<<jugador.cant_jueg_gan<<endl;
	cout<<"MEJOR PUNTAJE: "<<jugador.mejor_puntaje<<endl;
	cout<<"PUNTAJE ACUMULADO: "<<jugador.puntaje_acumulado<<endl;
}

void consultar_jugador(parchivo jugadores, tcad alias)
{
	bool encontrado =false;
	tjugador jugador;
	jugadores = fopen("jugadores.txt","rb");
	while(!feof(jugadores)&&!encontrado)
	{
		fread(&jugador,sizeof(jugador),1,jugadores);
		if(strcmp(jugador.alias,alias)==0)
		{
			mostrar_jugador(jugador);
			encontrado=true;
		}
	}
	if(encontrado==false)
		cout<<"JUGADOR NO ENCONTRADO"<<endl;
	fclose(jugadores);
}

void cargar_jugador_mod(tjugador &jugador)
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
}

void modificar_jugador(parchivo jugadores, tcad alias)
{
	tjugador jugador;
	bool encontrado=false;
	
	jugadores = fopen("jugadores.txt","rb+");
	
	while(!feof(jugadores)&&encontrado != true)
	{
		fread(&jugador,sizeof(jugador),1,jugadores);
		
		if(strcmp(jugador.alias,alias)==0)
		{
			mostrar_jugador(jugador);
			encontrado=true;
		}
	}
	
	if(encontrado == false)
		cout<<"JUGADOR NO ENCONTRADO"<<endl;
	else
	{
		cargar_jugador_mod(jugador);
		fseek(jugadores,-sizeof(jugador),1);
		fwrite(&jugador,sizeof(jugador),1,jugadores);
	}
	
	fclose(jugadores);
}

void actualizar_jugador(parchivo jugadores,tjugador jugador,tcad alias,bool gano,int nuevo_puntaje)
{
	bool encontrado=false;
	
	jugadores = fopen("jugadores.txt","rb+");
	
	while(encontrado != true)
	{
		fread(&jugador,sizeof(jugador),1,jugadores);
		if(strcmp(jugador.alias,alias)==0)
			encontrado=true;
	}

	if(gano==true)
		jugador.cant_jueg_gan = jugador.cant_jueg_gan +1;
	if(nuevo_puntaje>jugador.mejor_puntaje)
		jugador.mejor_puntaje = nuevo_puntaje;
	jugador.puntaje_acumulado = jugador.puntaje_acumulado + nuevo_puntaje ;
	
	fseek(jugadores,-sizeof(jugador),1);
	fwrite(&jugador,sizeof(jugador),1,jugadores);

	fclose(jugadores);
	
	cout<<"PUNTAJES JUGADOR ACTUALIZADOS"<<endl;
}



void borrar_jugador(parchivo jugadores,tcad alias)
{
	tjugador jugador;
	parchivo aux;
	
	jugadores = fopen("jugadores.txt","rb");
	
	if(jugadores == NULL)
	{
		cout<<"NO EXISTE EL ARCHIVO"<<endl;
		fclose(jugadores);
	}
	else
	{
		aux = fopen("copia.txt","wb");
		while(!feof(jugadores))
		{
			fread(&jugador,sizeof(jugador),1,jugadores);
			if(!feof(jugadores)&&strcmp(jugador.alias,alias)==1)
				fwrite(&jugador,sizeof(jugador),1,aux);
		}
		
		fclose(aux);
		fclose(jugadores);
		
		if(remove("jugadores.txt")==0){
			rename("copia.txt","jugadores.txt");
			cout<<"JUGADOR BORRADO CON EXITO"<<endl;
		}
		else
			cout<<"NO SE PUDO BORRAR EL REGISTRO"<<endl;
	}
}

void mostrar_jugadores(parchivo jugadores)
{
	tjugador jugador;
	jugadores = fopen("jugadores.txt","rb");
	
	while(!feof(jugadores))
	{
		fread(&jugador,sizeof(jugador),1,jugadores);
		if(!feof(jugadores))
		{
			mostrar_jugador(jugador);
		}
	}
	fclose(jugadores);
}
