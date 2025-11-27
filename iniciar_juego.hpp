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
				cout<<"PUNTAJE GANADO: " << " : " << puntaje << endl;
				cout<<endl;
				cout<<"Tiene " << intentos << " intentos por palabra "<<endl;
				cout<<endl;
				cout<<"*************************************"<<endl;
				cout<<endl;
				cout<<"----Desea usar una pista para acceder a la palabra----"<<endl;
				cout<<endl;
				cout<<"PISTA 1 -> Cantidad de letras - precio 2 puntos"<<endl;
				cout<<"PISTA 2 -> Primera letra - precio 3 puntos"<<endl;
				cout<<"PISTA 3 -> Definicion de palabra - precio 4 puntos"<<endl;
				cout<<"PISTA 4 -> Sinonimo de palabra - precio 4 puntos"<<endl;
				cout<<"Ingrese 0 si no desea elegir una pista"<<endl;
				cout<<endl;
				cout<<"INGRESE SU OPCION: ";
				cin>>respuesta;
				switch(respuesta){
				case 1:
					cout<<endl;
					cout<<"PISTA 1 - " << palabraEspejo.cantidadCaracteres << endl;
					cout<<endl;
					cout<<"INGRESE LA PALABRA A ADIVINAR: ";	
					fflush(stdin);
					gets(palabraParaAdivinar);
					cout<<endl;
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
					cout<<endl;
					cout<<"PISTA 2 - " << palabraEspejo.nombre[0] <<endl;
					cout<<endl;
					cout<<"INGRESE LA PALABRA A ADIVINAR: ";
					fflush(stdin);
					gets(palabraParaAdivinar);
					cout<<endl;
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
					cout<<endl;
					cout<<"PISTA 3 - " << palabraEspejo.definicion << endl;
					cout<<endl;
					cout<<"INGRESE LA PALABRA A ADIVINAR: ";
					fflush(stdin);
					gets(palabraParaAdivinar);
					cout<<endl;
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
					cout<<endl;
					cout<<"PISTA 4 - " << palabraEspejo.sinonimo << endl;
					cout<<endl;
					cout<<"INGRESE LA PALABRA A ADIVINAR: ";	
					fflush(stdin);
					gets(palabraParaAdivinar);
					cout<<endl;
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
					cout<<endl;
					cout<<"INGRESE LA PALABRA A ADIVINAR: ";
					fflush(stdin);
					gets(palabraParaAdivinar);
					cout<<endl;
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
	
