typedef struct tnodo *pnodo;
struct tnodo{
	tjugador jugador;
	pnodo izq;
	pnodo der;
};



void iniciar_jugadores_abb(pnodo &arbol)
{
	arbol=NULL;
}

void crear_nodo_abb(pnodo &nuevo,tjugador jugador)
{
	nuevo = new tnodo;
	if(nuevo!=NULL)
	{
		nuevo->jugador.nombre = jugador.nombre;
		nuevo->jugador.apellido = jugador.apellido;
		nuevo->jugador.signo_zodical = jugador.signo_zodical;
		nuevo->jugador.alias = jugador.alias;
		nuevo->jugador.cant_jueg_gan = jugador.cant_jueg_gan;
		nuevo->jugador.mejor_puntaje = jugador.mejor_puntaje;
		nuevo->jugador.puntaje_acumulado = jugador.puntaje_acumulado;
		nuevo->izq=NULL;
		nuevo->der=NULL;
	}
}


void insercion_jugadores_abb(pnodo &arbol,parchivo jugadores)
{
	pnodo nuevo;
	tjugador jugador;
	jugadores = fopen("jugadores.txt","rb");
	while(!feof(jugadores))
	{
		fread(&jugador,sizeof(jugador),1,jugadores);
		crear_nodo_abb(nuevo,jugador);
		if(arbol==NULL)
			arbol=nuevo;
		else
		{
			if(strcmp(nuevo->jugador.alias,arbol->jugador.alias)==1)
				insercion_jugadores_abb(arbol->der,jugadores);
			else
				insercion_jugadores_abb(arbol->izq,jugadores);
		}
		
	}
	fclose(jugadores);
}

pnodo busqueda_jugador_abb(pnodo arbol,tcad jugador_buscado)
{
	pnodo aux = NULL;
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
