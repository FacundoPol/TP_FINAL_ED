
typedef struct tnodov *pnodov;
struct tnodov{
	tjugador jugador;
	pnodov ant;
	pnodov sig;
};

struct tlistav{
	pnodov ini;
	pnodov fin;
};

void iniciar_lista(tlistav &lista)
{
	lista.ini = NULL;
	lista.fin = NULL;
}

void crear_nodo_lista(pnodov &nuevo,tjugador jugador)
{
	nuevo = new tnodov;
	if(nuevo!=NULL)
	{
		nuevo->jugador=jugador;
		nuevo->sig=NULL;
		nuevo->ant=NULL;
	}
}

void agregar_inicio_lista(tlistav &lista,pnodov nuevo)
{
	if(lista.ini==NULL)
	{
		lista.ini=nuevo;
		lista.fin=nuevo;
		nuevo->sig =lista.fin;
		nuevo->ant=lista.ini;
	}
	else
	{
		lista.fin->sig=nuevo;
		lista.ini->ant=nuevo;
		nuevo->ant=lista.fin;
		nuevo->sig=lista.ini;
		lista.ini=nuevo;
	}
}

void cambio_lista_vencedores(tjugador &jugador1,tjugador &jugador2)
{
	tjugador aux;
	
	aux=jugador1;
	jugador1 =jugador2;
	jugador2=aux;
}

void ordenar_lista(tlistav &lista)
{
	pnodov i,j;
	i=lista.ini;
	do
	{
		j=i->sig;
		do{
			if(i->jugador.mejor_puntaje > j->jugador.mejor_puntaje)
			{
				cambio_lista_vencedores(i->jugador,j->jugador);
			}
			j=j->sig;
		}while(j!=lista.fin);
		i=i->sig;
	}while(i!=lista.ini);
}


void seleccion_jugadores_ganadores(pnodoj arbol,tlistav &lista)
{
	tjugador aux;
	pnodov nuevo;
	if(arbol!=NULL)
	{
		if(arbol->jugador.cant_jueg_gan>0)
		{
			aux = arbol->jugador;
			crear_nodo_lista(nuevo,aux);
			agregar_inicio_lista(lista,nuevo);
		}
		seleccion_jugadores_ganadores(arbol->izq,lista);
		seleccion_jugadores_ganadores(arbol->der,lista);
		
	}
}

void mostrar_vencedores_repetitivo(tlistav lista,bool orden)
{
	pnodov i;
	
	
	if(lista.ini==NULL)
		cout<<"LISTA VACIA"<<endl;
	else
	{
		ordenar_lista(lista);
		if(orden == true)
		{
			mostrar_jugador(lista.ini->jugador);
			for(i=lista.ini->sig;i!=lista.ini;i=i->sig)
				mostrar_jugador(i->jugador);
		}
		else
		{
			mostrar_jugador(lista.fin->jugador);
			for(i=lista.fin->ant;i!=lista.fin;i=i->ant)
				mostrar_jugador(i->jugador);
		}
	}
}



void liberar_lista(tlistav &lista)
{
	pnodov i,eliminado;
	if(lista.ini != NULL){
		i=(lista.fin->ant)->ant;
		do{
			eliminado = i->sig;
			delete(eliminado);
			i=i->ant;
		}while(i!=lista.fin);
	}
	
	delete(lista.ini);
	delete(lista.fin);
}


void menu_vencedores(int &op)
{
	cout<<"OPCIONES: "<<endl;
	cout<<"|1| MOSTRAR DE MAYOR A MENOR"<<endl;
	cout<<"|2| MOSTRAR DE MENOR A MAYOR"<<endl;
	cout<<"|0| SALIR"<<endl;
	cout<<"Ingrese opcion: ";
	cin>>op;
}

void seleccion_menu_vencedores(int op,tlistav &lista,pnodoj arbol)
{
	iniciar_lista(lista);
	seleccion_jugadores_ganadores(arbol,lista);
	bool orden;
	switch(op)
	{
	case 1:
		orden = true;
		mostrar_vencedores_repetitivo(lista,orden);
		break;
	case 2:
		orden = false;
		mostrar_vencedores_repetitivo(lista,orden);
		break;
	default:
		liberar_lista(lista);
		cout<<"SALISTE"<<endl;
		break;
	}
	
}
