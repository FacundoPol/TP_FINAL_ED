#pragma once
#include <iostream>
#include <cstdio> 
#include <string.h>
#include "pilapalabras.hpp "

using namespace std;

const int MAX2 = 26; 

typedef FILE* parchivo;

typedef struct tnodo *pnodo;
typedef struct tnodo{
	tregistro palabra;
	pnodo sig;
};

typedef struct tletra{
	char primeraLetra;
	pnodo inicio;
	int contador;
};

typedef tletra tdiccionario[MAX2];

//procedimiento que inicia el diccionario
void iniciarDiccionario(tdiccionario &dicci){
	int i;
	char clave='A';
	for(i=0;i<MAX2;i++){
		dicci[i].primeraLetra=clave;
		dicci[i].inicio=NULL;
		dicci[i].contador=0;
		clave++;
	}
}
	
// este procedimiento se encarga de crear el nodo y carga los datos al registro
void crearNodo(pnodo &nuevo,tregistro palabra){
	nuevo = new tnodo;
	if(nuevo!=NULL){
		strcpy(nuevo->palabra.nombre, palabra.nombre);
		strcpy(nuevo->palabra.definicion, palabra.definicion);
		strcpy(nuevo->palabra.sinonimo, palabra.sinonimo);
		nuevo->palabra.cantidadCaracteres=palabra.cantidadCaracteres;
		nuevo->sig=NULL;
	}
	else
	   cout<<"memoria llena"<<endl;
}
	
	
	// este procedimiento se encarga de agregar en cada item del arreglo tomando el puntero inicio y agregar en orden
	// libera el nodo si se ingreso palabra repetida
	void agregar(pnodo &inicio,pnodo nuevo){
		pnodo i;
		pnodo aux=NULL;
		if(inicio==NULL){
			inicio=nuevo;
		}
		else{
			if(strcmp(nuevo->palabra.nombre,inicio->palabra.nombre) == 0){
				aux=nuevo;
			}
			
			if(strcmp(nuevo->palabra.nombre,inicio->palabra.nombre)<0){
				nuevo->sig=inicio;
				inicio=nuevo;
			}
			else{
				for(i=inicio;i->sig!=NULL && strcmp((i->sig)->palabra.nombre,nuevo->palabra.nombre)<0;i=i->sig);
				
				if(i->sig != NULL && strcmp((i->sig)->palabra.nombre, nuevo->palabra.nombre) == 0){
					aux=nuevo;
					
				}
				nuevo->sig=i->sig;
				i->sig=nuevo;
			}
		}
		delete(aux);
	}
	
		// la funcion de este procedimiento es agregar las palabras al diccionario 
		// en la estructura while se encarga de cargar registro llama a crearNodo para crgar los datos y despues agregar para agregarlo al diccionario en orden
	void agregarPalabraDiccionario(tdiccionario &dicci,tregistro palabra,pnodo &nuevo){
		int i = 0;
		bool encontrado=false;
		char primerCaracter=palabra.nombre[0];
		while(i<MAX2 && encontrado==false){
			if(dicci[i].primeraLetra==primerCaracter || dicci[i].primeraLetra==primerCaracter-32){
				crearNodo(nuevo,palabra);
				if (nuevo != NULL) {
					agregar(dicci[i].inicio, nuevo);
					dicci[i].contador++;
					encontrado=true;
				}
			}
			i++;
		}
	}
	
	/*bool empiezaConLetra(tregistro pala){
		char c = pala.nombre[0];
		if((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'))
			return true;
		else
			return false;
	}*/
		// procedimiento que se encarga de cargar los datos en un registro este interactua con el usuario
	void cargaPalabras2(tregistro &p){
		cout<<"para cargar los datos debe asegurarse de no colocar datos vacios y las palabras deben tener 5 o mas caracteres"<<endl;
		do{
			
			cout<<"nombre de la palabra: ";
				fflush(stdin);
				gets(p.nombre);
			
		}while(strcmp(p.nombre,"")==0 || strlen(p.nombre)<=5);
		
		do{
			cout << "cantidad de caracteres de la palabra: "; 
			cin>>p.cantidadCaracteres; 
		   }while( p.cantidadCaracteres==0);
		
		do{
			cout << "definicion de la palabra: ";
			fflush(stdin);
			gets(p.definicion); 
		}while( strcmp(p.definicion,"")==0 );
		
		do{
			cout << "sinonimo de la palabra: ";
			fflush(stdin);
			gets(p.sinonimo); 
		}while( strcmp(p.sinonimo,"")==0 );
		
	}
		void cargarPalabrasDiccionario(tdiccionario &dicci) {
			parchivo pal;
			tregistro p;
			pnodo nuevo = NULL;
			bool archivoExiste = false;
			
			pal = fopen("palabras.txt", "rb");
			
			if (pal != NULL) {
				archivoExiste = true;
			}
			
			if (archivoExiste) {
				cout << "\n--- Cargando diccionario... ---" << endl;
				
				while (fread(&p, sizeof(p), 1, pal) == 1) {
					agregarPalabraDiccionario(dicci, p, nuevo); 
				}
				
				fclose(pal);
				cout << "Carga finalizada." << endl;
			}
		}
		// funcion que recorre en archivo y verifica si existe una palabra devuelve true si y false sino
		bool existePalabraEnArchivo(parchivo palabra, tregistro nueva2) {
			tregistro leida;
			while (fread(&leida, sizeof(nueva2), 1, palabra) == 1) {
				if (strcmp(leida.nombre, nueva2.nombre) == 0) 
					return true;
			}
			return false;
		}
		
		// este procedimiento es el principal este es llamado desde el submenuPalabras se encarga de llamar a otros modulos para cargar las palabras en el archivo y en el diccionario
		// llama a cargaPalabras2 despues pregunta si la palabra esta repetida controla eso
		// si no carga la palabra en el diccionario y tambien en el archivo 
		void altaPalabra(parchivo palabra,tdiccionario &dicci,pnodo &nuevo){
			tregistro pa;
			bool palabraRepetida;
			palabra=fopen("palabras.txt","ab+");
			do {
				cargaPalabras2(pa);
				palabraRepetida = existePalabraEnArchivo(palabra, pa);
				rewind(palabra);
				
				if (palabraRepetida) {
					cout<<" ERROR: La palabra '%s' ya existe en el archivo. Intente con otra " << pa.nombre << endl;
				}
			} while (palabraRepetida);
			agregarPalabraDiccionario(dicci,pa,nuevo);
			fwrite(&pa,sizeof(pa),1,palabra);
			fclose(palabra);
		}
			
			//esto es para mostrar que se cargo correcto en la pila la estructura
		/*void mostrarPilaPalabras(tpila &p) {
				tpila pilaAuxiliar; // se usa una pila auxiliar
				tregistro registroMostrado;
				int contador = 0;
				
				iniciarPila(pilaAuxiliar);
				//  Desapilar y mostrar
				while (!pilaVacia(p)) {
					registroMostrado = quitarPila(p);
					contador++;
					cout << "Elemento :" << contador << ":" << endl;
					cout << "  > Nombre : " << registroMostrado.nombre << endl;
					cout << "  > Caracteres : " << registroMostrado.cantidadCaracteres << endl;
					cout << "  > Definición : " << registroMostrado.definicion << endl;
					cout << "------------------------------------------" << endl;
					
					// se Almacena en la pila auxiliar
					agregarPila(pilaAuxiliar, registroMostrado);
				}
				
				if (contador == 0) {
					cout << "La pila está vacía. No hay palabras cargadas." << endl;
				} else {
					cout << "? Se verificaron " << contador << " registros en la pila." << endl;
				}
				while (!pilaVacia(pilaAuxiliar)) {
					registroMostrado = quitarPila(pilaAuxiliar);
					agregarPila(p, registroMostrado);
				}
			} */	
		
	//cuenta la cantidad de palabras del diccionario
	int contarTotalPalabras(tdiccionario dicci) {
		int total = 0;
		int i;
		for (i = 0; i < MAX2 ; i++) { 
			total += dicci[i].contador; 
		}
		return total;
	}
	
	//trae la palabra del diccionario
		pnodo traerPalabra(pnodo inicio, int posicion) {
			int i = 0;
			pnodo actual = inicio;
			while (actual != NULL && i < posicion) {
				actual = actual->sig;
				i++;
			}
			return actual; // puede ser NULL si no existe
		}
		
	// esta funcion verifica que no existan palabras repetidas en la pila , si llega a pasar el caso que el aleatorioPalabras trajo registro repetido esta funcion
		// lo saca de la pila y devuelve el valor true sino devuelve falso
	bool estaEnPila(tpila &pila, tcad palabra) {
		tpila aux;
		iniciarPila(aux);
		bool encontrado = false;
		
		while (!pilaVacia(pila)) {
			tregistro res = quitarPila(pila);
			if (strcmp(res.nombre, palabra) == 0) 
				encontrado = true;
	        
			agregarPila(aux, res);
		}
		while (!pilaVacia(aux)) {
		   tregistro res = quitarPila(aux);
			agregarPila(pila,res); 
		}
		return encontrado;
	}
	
	//procedimiento lo usa aleatorioPalabras para guardas los datos en el registro
	void copiarPalabraEnRegistro(tregistro &destino, tregistro &origen) {
		destino.cantidadCaracteres = origen.cantidadCaracteres;
		strcpy(destino.nombre, origen.nombre);
		strcpy(destino.definicion, origen.definicion);
		strcpy(destino.sinonimo, origen.sinonimo);
	}
	
	//esta es el procedimiento mas importante 
	//se encarga de seleccionar aleatoreamente las palabras del diccionario
	//la estructura del diccionario tiene un contador que verifica cuantas palabras ahi en el indice sobre eso va recorriendo y preguntando si es 0 no extrae nada sino puede extraer alguna 
	// registro del diccionario
	void aleatorioPalabras(tdiccionario dicci,tpila &p) {
		int palabrasSeleccionadas = 6;
		cout << "\n--- Seleccionando 6 palabras aleatorias ---" << endl;
		
		while (palabrasSeleccionadas > 0) {
			int indiceLetras = rand() % 26; 
			if (dicci[indiceLetras].contador > 0) { 
				int posicionLista = rand() % dicci[indiceLetras].contador; 
				pnodo actual = traerPalabra(dicci[indiceLetras].inicio, posicionLista);
				
				if (actual != NULL && !estaEnPila(p, actual->palabra.nombre)) {
					tregistro registroInsertar;
					copiarPalabraEnRegistro(registroInsertar, actual->palabra);
					agregarPila(p, registroInsertar);
					palabrasSeleccionadas--;
				}
			}
		}
		cout << "------------------------------------------" << endl;
		cout << "Pila de juego cargada con 6 palabras." << endl;
	}
	
//lista las palabras del diccionario
	void listarDiccionario(tdiccionario dicci) {
		pnodo actual;
		cout << "\n--- LISTADO COMPLETO DEL DICCIONARIO ---" << endl;
		
		for (int i = 0; i < MAX2; i++) {
			if (dicci[i].inicio != NULL) {
				cout << " "<<endl;
				cout <<" Letra: "<< dicci[i].primeraLetra << " ( Total: " << dicci[i].contador << " ) " << endl;
				actual = dicci[i].inicio;
				
				while (actual != NULL) {
					cout << "  -> " << actual->palabra.nombre << endl;
					actual = actual->sig;
				}
			}
		}
		cout << "------------------------------------------" << endl;
	}
 //  BUSCA LA PALABRA en el diccionario y devuelve el nodo si lo encuentra sino devuelve NULL
	pnodo buscarPalabra(tdiccionario dicci, tcad palabra) {
		int i = 0;
		char primerCaracter = palabra[0];
		
		while(i < MAX2){
			if(dicci[i].primeraLetra == primerCaracter || dicci[i].primeraLetra == primerCaracter - 32){
				pnodo actual = dicci[i].inicio;
				while(actual != NULL){
					if(strcmp(actual->palabra.nombre, palabra) == 0){
						return actual;
					}
					actual = actual->sig;
				}
				return NULL; 
			}
			i++;
		}
		return NULL; 
	}
	
	// para consultar si la palabra esta en el diccionario devuelve sus datos sino devuelve que no se encuentra
	void consultarPalabraDiccionario(tdiccionario dicci, tcad palabra){
		pnodo nodo = buscarPalabra(dicci, palabra);
		
		if(nodo != NULL){
			cout << "\n--- DATOS DE LA PALABRA ENCONTRADA ---" << endl;
			cout << "Nombre: " << nodo->palabra.nombre << endl;
			cout << "Caracteres: " << nodo->palabra.cantidadCaracteres << endl;
			cout << "Definicion: " << nodo->palabra.definicion << endl;
			cout << "Sinonimo: " << nodo->palabra.sinonimo << endl;
			cout << "---------------------------------------" << endl;
		} else {
			cout << "Palabra '" << palabra << "' no encontrada en el diccionario." << endl;
		}
	}
		// elimina la palabra del diccionario
		void eliminarPalabraDiccionario(tdiccionario &dicci, tcad palabra) {
			int i = 0;
			bool encontrado = false;
			char primerCaracter = palabra[0];
			
			while (i < MAX2 && encontrado == false) {
				if (dicci[i].primeraLetra == primerCaracter || dicci[i].primeraLetra == primerCaracter - 32) {
					encontrado = true;
				} else {
					i++;
				}
			}
			
			if (encontrado && dicci[i].inicio != NULL) {
				pnodo actual = dicci[i].inicio;
				pnodo anterior = NULL;
				
				while (actual != NULL && strcmp(actual->palabra.nombre, palabra) != 0) {
					anterior = actual;
					actual = actual->sig;
				}
				
				if (actual != NULL) {
					if (anterior == NULL) {
						dicci[i].inicio = actual->sig;
					} else {
						anterior->sig = actual->sig;
					}
					delete actual;
					dicci[i].contador--;
				} else {
					cout << "La palabra no se encontro en el diccionario en memoria." << endl;
				}
			}
		}	
		
	//modifica palabra en el diccionario
		void modificarPalabraDiccionario(tdiccionario &dicci, tcad palabraAntigua) {
			pnodo nodo = buscarPalabra(dicci, palabraAntigua);
			
			if(nodo != NULL){
				tregistro pNueva;
				cout << "Modificando palabra" << palabraAntigua << "' ---" << endl;
				cargaPalabras2(pNueva); 
				
				if(strcmp(palabraAntigua, pNueva.nombre) != 0){
					eliminarPalabraDiccionario(dicci, palabraAntigua);
					
					pnodo nuevoInsertado = NULL;
					agregarPalabraDiccionario(dicci, pNueva, nuevoInsertado);
					cout << "Palabra modificada (nombre cambiado y reordenado)." << endl;
					
				} else {
					strcpy(nodo->palabra.definicion, pNueva.definicion);
					strcpy(nodo->palabra.sinonimo, pNueva.sinonimo);
					nodo->palabra.cantidadCaracteres = pNueva.cantidadCaracteres;
					cout << "Palabra modificada (campos actualizados)." << endl;
				}
			} else {
				cout << "ERROR: No se puede modificar. Palabra '" << palabraAntigua << "' no encontrada." << endl;
			}
		}
		
		//submenu de palabras se accede desde el menu principal
		void submenuPalabras(parchivo &palabra,tdiccionario &dicci,pnodo &nuevo){
			int opcion;
			int cantidad;
			tcad consulta;
			do{
				system("cls");
				cout << "1-Crear y almacenar palabras" << endl;
				cout << "2-Consultar  palabras  " << endl;
				cout << "3-Modificar palabra " << endl;
				cout << "4-Eliminar palabra " << endl;
				cout << "5-Listar palabras " << endl;
				cout << "0-Salir del submenu y guardar cambios" << endl;
				cout << "Elija una opcion: ";
				cin >> opcion;
				
				switch(opcion){
				case 1:
					cout << "Para agregar palabras al juego, indique cuantas palabras va a almacenar: ";
					cin >> cantidad;
					while(cantidad > 0){
						altaPalabra(palabra,dicci,nuevo); 
						cantidad--;
					}
					break;
					
				case 2:
					cout << "Indique cual palabra desea consultar: ";
					fflush(stdin);
					gets(consulta);
					consultarPalabraDiccionario(dicci, consulta);  
					break;
					
				case 3:
					cout << "Indique cual palabra desea modificar: ";
					fflush(stdin);
					gets(consulta);
					modificarPalabraDiccionario(dicci, consulta); 
					break;
					
				case 4:
					cout << "Indique cual palabra va a eliminar: ";
					fflush(stdin);
					gets(consulta);
					eliminarPalabraDiccionario(dicci, consulta); 
					break;
					
				case 5:
					cout << "Palabras en el diccionario" << endl;
					listarDiccionario(dicci);
					break;
					
				case 0:
					cout << "Fin del submenu" << endl;
					break;
					
				default:
					cout << "Opcion incorrecta" << endl;
					break;
				}
				system("pause");
			}while(opcion != 0);	
		}
			
			
			// se encarga de copiar lo del diccionario al archivo lo que se haya modificado en las palabras durante el juego
			void copiarArchivo(tdiccionario dicci, parchivo &palabras){
				pnodo i;
				int controlador=0;
				palabras=fopen("palabras.txt","wb"); 
				while(controlador < MAX2 ){
					if(dicci[controlador].contador > 0){
						i=dicci[controlador].inicio;
						while(i!=NULL){
							fwrite(&(i->palabra),sizeof(i->palabra),1,palabras);
							i=i->sig;
						}
					}
					controlador++;
				}
				fclose(palabras);
			}
				
