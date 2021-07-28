//Incluyendo lo necesario
#include "General_impl.cpp"

/* 
------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ 
																IMPLEMENTACION	 
------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
*/

/* ----FUNCIONES DE LA CLASE Queue (Cola)---- */

//Creacion de una cola , con su id
Queue::Queue(int queueId){
    //Asigna el numero
    this -> queueNo = queueId;
    this -> rear = NULL;
    this -> front = NULL;
}

//Agregar a una Persona en la cola
void Queue::enqueue(Person p){

    //Creamos un nodo que servira para registrar a la persona en la cola
    Node* temp = new Node;

    //Asignamos la persona en el nodo
    temp -> person = p;
    //Espacio libre del siguiente
    temp -> next = NULL;

    //En caso la cabecera de la cola este vacio
    //Es decir la primera persona que ingresara a la cola
    if(this -> front == NULL){

	//La asigna como cabecera
       this -> front = temp;

    //Sino
    }else{
	//Lo anexo con el ultimo de la cola
        this -> rear -> next = temp;
    }
    //Y lo actualiza como ultimo de la cola
    this -> rear = temp;
}

//Sacar de la cola
void Queue::dequeue(){

    //Creamos un nodo que servira para eliminar a la persona mas antigua de la cola
    Node* temp = new Node;

    	//Asignamos nuestro nodo como la cabecera de la cola
	temp = this -> front;
	//Asignamos el siguiente como nueva cabecera,
	//Eliminando a la antigua cabecera
	this -> front = this -> front -> next;

	//Eliminamos nuestro nodo
	delete temp;
}

//Mostrar Cola
void Queue::display(int num){
	
	//Iteramos la lista de colas
	for (std::list<Queue>::iterator i = qlist.begin(); i != qlist.end(); ++i) {
		//Compara con el numero de cola
		if(num == i -> queueNo){
			//Creamos un nodo
			Node* p = new Node;
			//Y le asignamos la cabecera
			p = i -> front;

			//Si la cabecera esta vacia
			//Quiere decir q la cola esta vacia
			if(i -> front == NULL){
				cout<<"\nCola vacía.\n";

			//Sino muestra
			}else{
				//Informacion de los pasajeros
				cout << "\nPasajeros esperando en cola: " << endl;
				cout << left << setw(15) << 
				"Passport" << left << setw(15) << 
				"Name" << left << setw(15) << 
				"Surame" << endl;
				//Mientras que el nodo en el que estemos no sea nulo
				while(p!=NULL){
					//Mostramos
					cout << left << setw(15) << p -> person.getPassport() << left << setw(15) << p -> person.getName() << left << setw(15) << p -> person.getSurname() << endl;
					//Y avanzamos de Nodo
					p = p -> next;
				}
			}
		}
	}

    

}
//Obtener la persona mas antigua de la cola
Person Queue::oldest(){
	//Retorna la cabecera de la cola
	return this -> front -> person;
}

//Verifica si la cola esta vacia
bool Queue::isEmpty(){
//Si la cabecera es nula y el final tambien
 if(this -> front == NULL && this -> rear == NULL){
  	//Esta vacia
	 return true;
 }
 //No esta vacia
 return false;
} 


/* ----FUNCIONES DE LA CLASE Menu---- */

//Muestra el menu
void Menu::displayMenu(){
	
	int selection;	// Eleccion hecha por el usuario en el Menu
	string temp; // Variable para almacenar lo ingresado por el usuario
	
	//Opciones
	do{
			cout << "-----------------------------------------------";
			
			cout << "\n \t SISTEMA DE RESERVAS AEROLÍNEAS \n \n";
			cout << "Elija una opción del menú siguiente. \n";
			cout << "1. Agregar nuevos vuelos \n";
			cout << "2. Eliminar vuelos \n";
			cout << "3. Mostrar horario de vuelo \n";
			cout << "4. Mostrar detalles del vuelo \n";
			cout << "5. Mostrar información personal del pasajero \n";
			cout << "6. Reservar reserva \n";
			cout << "7. Cancelar reserva \n";
			cout << "8. Salir \n \n";

			cout << "---------------------------------------------- - "<< endl;

			cout << "Introduzca el número de una opción de menú:";
			//Ingresa
			cin >> temp; 
			
			// COmprueba la validez de lo ingresado por el usuario
			while (!checkNumber(temp)) {
				cout << "Por favor introduzca un numero!" << endl;
				cin.clear();
				cin.ignore(256,'\n');
				//Vuelve a ingresar
				cin >> temp;
			}
			cout << endl;
			//Convierte el string ingresado a entero
			selection = atoi(temp.c_str());
			//Manda ese numero a select para que ejecute segun lo mandado
			select(selection);
	
	}while(true);
}

//Ejecuta segun la eleccion mandada
void  Menu::select(int selection){
	
	Flight f; // Objeto Flight (Vuelo)
	Person p; // Objeto Person (Persona)
	string temp; // Variable para almacenar lo ingresado por el usuario

	//Bloque de elecciones	
	switch(selection){
		//Anadir un Vuelo
		case 1:{
				auto start = chrono::high_resolution_clock::now();
    			ios_base::sync_with_stdio(false);
    			//code
				f.addFlight();
    			auto end = chrono::high_resolution_clock::now();
    			double time_taken = chrono::duration_cast<chrono::nanoseconds>(end - start).count();
				time_taken *= 1e-9;
				writetime(time_taken, "addFlight()");
			}
			break;
		//Eliminar un vuelo
		case 2:{
				//En caso la lista de vuelos no este vacia
				if (!flist.empty()) {
					cout << "Ingrese el número de vuelo que desea eliminar:"; cin >> temp;
					cout << endl;
					//Comprueba que sea un numero
					while (! checkNumber (temp)) {
						cout << "¡El número de vuelo debe ser un número!" << endl;
						cin.clear();
						cin.ignore(256,'\n');
						cin >> temp;
						cout << endl;
					}
					//Elimina el vuelo (convierte de string a int)
					 
					
					auto start = chrono::high_resolution_clock::now();
					ios_base::sync_with_stdio(false);
					//code
					Flight::deleteFlight( atoi(temp.c_str()) );
					auto end = chrono::high_resolution_clock::now();
					double time_taken = chrono::duration_cast<chrono::nanoseconds>(end - start).count();
					time_taken *= 1e-9;
					writetime(time_taken, "deleteFlight()"); 
					 
				//Cuando la lista de vuelos este vacia
				}else {
					cout << "No hay vuelos para eliminar" << endl;
				}
			}			
			break;
		//Mostrar todos los vuelos registrados en el sistema
		case 3:
			{
				//En caso la lista de vuelos no este vacia
				if (!flist.empty()) {
					clock_t tStart = clock();
					//Muestra
					
					auto start = chrono::high_resolution_clock::now();
					ios_base::sync_with_stdio(false);
					//code
					Flight::displaySchedule();
					auto end = chrono::high_resolution_clock::now();
					double time_taken = chrono::duration_cast<chrono::nanoseconds>(end - start).count();
					time_taken *= 1e-9;
					writetime(time_taken, "displaySchedule()");					 
					 
				//Cuando la lista de vuelos este vacia
				}else {
					cout << "¡No hay vuelos programados!" << endl;
				}
			}
			break;
		//Mostra la informacion de un vuelo en especifico
		case 4:
			{
				//En caso la lista de vuelos no este vacia
				if (!flist.empty()) {
					//Ingresa el numero
					cout << "Introduzca el número de vuelo:";
					cin >> temp; cout << endl;
					//Comprueba que sea un numero
					while (!checkNumber(temp)){
						cout << "¡El número de vuelo debe ser un número!" << endl; 
						cin.clear();
						cin.ignore(256,'\n');
						//Vuelve a ingresar
						cin >> temp;
						cout << endl;
					}
					auto start = chrono::high_resolution_clock::now();
					ios_base::sync_with_stdio(false);
					//code
					//Muestra la informacion del vuelo(convierte de string a int)
					Flight::displayFlightInfo( atoi(temp.c_str()) );
					auto end = chrono::high_resolution_clock::now();
					double time_taken = chrono::duration_cast<chrono::nanoseconds>(end - start).count();
					time_taken *= 1e-9;
					writetime(time_taken, "displayFlightInfo()");					
				//Cuando la lista de vuelos este vacia
				}else {
					cout << "¡No hay vuelos programados!" << endl;
				}
			}			
			break;
		//Muestra la informacion de una persona en especifico
		case 5:
		{
			auto start = chrono::high_resolution_clock::now();
    		ios_base::sync_with_stdio(false);
    		//code
			//Cuando la lista de persona no este vacia
			if (!plist.empty()){
				//Ingresa el pasaporte
				cout << "Introduzca el número de pasaporte:";
				cin >> temp;
				//Llama a la funcion displayInfo
				//Convirtiendo el string a entero
				//Si no se puede mostrar retorna falso y se pide otro pasaporte
				//Si no simplemente muestra
				while (!Person::displayPersonInfo( atoi(temp.c_str()) )) {
					cout << "¡Número de pasaporte incorrecto!" << endl;
					cin.clear();
					cin.ignore(256,'\n');
					cin >> temp;
					cout << endl;
				}
			//Cuanod la lista de personas este vacia
			}else{
				cout << "¡No hay clientes registrados en este momento!" << endl;
			}
    		auto end = chrono::high_resolution_clock::now();
    		double time_taken = chrono::duration_cast<chrono::nanoseconds>(end - start).count();
			time_taken *= 1e-9;
			writetime(time_taken, "displayPersonInfo()");		
		}
			break;
		//Reservar un asiento
		case 6:
			{
				
				auto start = chrono::high_resolution_clock::now();
    			ios_base::sync_with_stdio(false);
    			//code
				p.book();
    			auto end = chrono::high_resolution_clock::now();
    			double time_taken = chrono::duration_cast<chrono::nanoseconds>(end - start).count();
				time_taken *= 1e-9;
				writetime(time_taken, "p.book()");
			}break;
		//Cancelar una reserva
		case 7:
		{
			auto start = chrono::high_resolution_clock::now();
    			ios_base::sync_with_stdio(false);
    			//code
				p.cancel();
    			auto end = chrono::high_resolution_clock::now();
    			double time_taken = chrono::duration_cast<chrono::nanoseconds>(end - start).count();
				time_taken *= 1e-9;
				writetime(time_taken, "p.cancel()");
			
		}
		break;
		//Salir de la aplicacion
		case 8:
		{
				auto start = chrono::high_resolution_clock::now();
    			ios_base::sync_with_stdio(false);
    			//code
				Menu::exit_prog();
    			auto end = chrono::high_resolution_clock::now();
    			double time_taken = chrono::duration_cast<chrono::nanoseconds>(end - start).count();
				time_taken *= 1e-9;
				writetime(time_taken, "Menu::exit_prog()");
			
		}
		break;
		default:
			cout << "Selección invalida \n"; 
	}
	
}

//Salir de la aplicacion
void Menu::exit_prog(){
	
	cout << "¡Gracias por usar nuestro sistema! \n";
	exit(1); // exit
}

/* ----FUNCIONES DE LA CLASE Flight (Vuelo)---- */

//Escribir un vuelo en nuestro reporte de vuelos
void writeFlight(string line){
	//Abre
	fstream f;
	f.open("reportFlights.csv",  std::ios_base::app);
	if(f.good()){
		//Escribe
		f << line + "\n";
	}
}

//Añadir Vuelo
void Flight::addFlight(){ 
	string store = "";
	/* ----INICIALIZA VARIABLES----*/
	bool flag = false; // usado en loops
	
	/* --Comprueba la validez del horario de llegada y de salidad(USADO SOLO EN HORARIO DE EMBARQUE Y DE LLEGADA)-- */
	vector<string> fields; //almacena, divide,lo ingresado por el usuario para ser comprobado
	string temp; // Almacena lo ingresado por el usuario en temp
	char* pch; // Almacena el resultado de la funcion strtok() 
	int hour; // Almacena la hora
	int min; // Almacena los minutos

	cout << "Agregue nuevos vuelos dando los siguientes atributos: \n";
	
	// Limpia
	cin.clear();
	cin.ignore(256,'\n');
	
	/* --NUMERO DE VUELO-- */
	cout << "Número de vuelo: "; 
	// Obtiene lo ingresado por el usuario
	getline(cin, temp);
	
	do{
		flag = true;
		
		// Comprueba lo ingresado
		// Si no es numero
		if (!checkNumber(temp)){
			cout << "Introduzca un número de vuelo válido! " << endl;
			//Cambia flag
			flag = false;
			getline(cin, temp);
		//Comprueba que el vuelo no sea repetido (Convierte de string a entero lo ingresado)
		}else if (Flight::flightExists( atoi(temp.c_str()) )) {
			cout << "¡Este vuelo ya existe!" << endl;
			cout << "Introduzca un número de vuelo válido!:" << endl;
			//Cambia flag
			//ya que el vuelo es repetido
			flag = false;
			getline(cin, temp);
		//Cuando cumple las condiciones
		}else {
			//Flag true
			flag = true;
			//Asigna el numero de vuelo
			//COnvirtiendo el string a entero
			this -> flightNo = atoi(temp.c_str());
			store += temp;
		}
	//Ejecuta esto hasta que el flag salga con verdadero
	}while(!flag);
	
	/* --SALIDA-- */
	cout << "Salida: ";
	flag = false;
	
	// Comprueba lo ingresado
	LOOP:do{
		//Ingresa la salidad
		getline(cin, temp);
		//Comprueba el tamano y que solo sean letras lo ingresado
		if ( (temp.length() <= 10) && (checkString(temp)) ){
			//Asigna
			this -> from = temp;
			store+=","+temp;
			//Cambia el flag
			flag = true;
		//En caso no sea una salida correcta
		}else {
			cout << "Introduzca una ciudad de salida válida!: ";
			goto LOOP;
		}
	//Ejecuta esto hasta que el flag sea verdadero
	}while(!flag);
	
	/* --DESTINO-- */
	cout << "Destino: "; 
	flag = false;
	
	// Comprueba lo ingresado
	LOOP2:do{
		//Ingresa
		getline(cin, temp);
		//Comprueba el tamano ,que solo sean letras lo ingresadoy q no sea el mismo destino
		if ( (temp.length() <= 10) && (checkString(temp)) && (temp.compare(this -> from)) ){
			//Asigna
			this -> to = temp;
			//Cambia el flag
			flag = true;
			store +=","+ temp;
		//En caso no sea un destino correcto
		}else{
			cout << "Introduzca una ciudad de destino válida! ";
			goto LOOP2;
		}
	//Ejecuta esto hasta que el flag sea verdadero
	}while(!flag);
	
	/* --HORA DE SALIDA-- */
	cout << "Hora de embarque (por ejemplo, 19:40):"; //Pregunta al usuario la hora de embarque
	flag = false;
	
	//Comprueba lo ingresado
	LOOP3:do{
		//Ingresa
		getline(cin, temp);
		//Comprueba que el tamano sea 5 y que sean solo numeros
		if( temp.length() != 5 || !checkTime(temp) ){
			cout << "Introduzca una hora de embarque válida (por ejemplo, 19:40)! ";
			goto LOOP3;			 
		}
		//Ingresa
		char t_temp[temp.length()];
		
		strcpy(t_temp, temp.c_str());
		
		//Divide el string
		pch = strtok(t_temp, ":");
		//Comprueba si fue almacenado
		while(pch != NULL){
			//Divide 
			fields.push_back(pch); 
			pch = strtok(NULL, ":");
		}
		
		//Asigna
		hour = atoi(fields[0].c_str()); 
		min = atoi(fields[1].c_str()); 
		
		//Comprueba el horario
		if ((hour >=0 && hour<=23) && (min>=0 && min <=59)){ 
			//Asigna
			this -> t_leave.hour = hour; 
			this -> t_leave.min = min; 
			store += ","+to_string(hour)+":"+to_string(min);
			//Alterna el flag
			flag = true;
		//En caso no sea un horario valido
		}else{
			cout << "Introduzca una hora de embarque válida (por ejemplo, 19:40).";
			fields.clear();		
		}	
	//Ejecuta esto hasta que el flag sea verdadero
	
	}while(!flag); 
	
	/* --HORARIO DE LLEGADA-- */
	cout << "Hora de llegada (por ejemplo, 21:40):";
	flag = false;
	fields.clear();	//limpia las grillas (porque fue usado antes en "HORARIO DE SALIDA")
	
	// Revisa lo ingresado
	LOOP4:do{
		//Ingresa
		getline(cin, temp);
		//Comprueba el tamano y qsean solo numeros
		if( temp.length() > 5 || !checkTime(temp) ){
			cout << "Introduzca una hora de embarque válida (por ejemplo, 19:40).";
			goto LOOP4;			 
		}
		//Ingresa
		char t_temp[temp.length()];
		
		strcpy(t_temp, temp.c_str());
		
		//Divide el string
		pch = strtok(t_temp, ":");
		
		//COmprueba si fue almacenado
		while(pch != NULL){
			fields.push_back(pch); 
			pch = strtok(NULL, ":");
		}
		//Asigna
		hour = atoi(fields[0].c_str());
		min = atoi(fields[1].c_str());
		
		//Comprueba la validez del horario
		if ((hour >=0 && hour<=23) && (min>=0 && min <=59)){ 
			//Asgina
			this -> t_arrive.hour = hour; 
			this -> t_arrive.min = min; 
			//Alterna el flag
			flag = true;
			store += ","+to_string(hour)+":"+to_string(min);
		//En caso no sea un horario valido
		}else{
			cout << "Introduzca una hora de llegada válida (por ejemplo, 19:40).";
			fields.clear();		
		}	
	//Ejecuta esto hasta que el flag sea verdadero
	}while(!flag); 
	
	/* --PRECIO DEL TICKET-- */
	cout << "Precio de la entrada:";
	LOOP5:do{
		//Obtiene
		getline(cin, temp);
		flag = true;
		
		//Comprueba lo ingresado sea solo numeros
		if (!checkNumber(temp)){
			cout << "Por favor, inserte un precio de entrada válido." << endl;
			//Alterna el flag
			flag = false;
			goto LOOP5;
		//Si solo son numeros
		}else{
			//Flag correcto
			flag = true;
			//Almacena
			this -> cost = atoi(temp.c_str());
			store += ","+temp;
		}
	//Ejecuta esto hasta que el flag sea verdadero
	}while(!flag);
	
	/* --TIPO DE AVION-- */
	cout << "Tipo de avión:";
	getline(cin, this -> plane_type);
	//Mientras q el tipo de avion todavia no sea ingresado
	while(this -> plane_type.empty()){
		cout << "Introduzca un tipo de avión válido!" << endl;
		//Vuelve a ingresar
		getline(cin, this -> plane_type);
	}
	store += ","+this->plane_type;
	
	/* --NUMERO DE ASIENTOS-- */
	cout << "Numero de asientos: ";
	LOOP6:do{
		//Ingresa
		getline(cin, temp);
		flag = true;
		
		//Comprueba lo Ingresado sea solo numeros
		if (!checkNumber(temp)){
			cout << "Por favor, inserte un número válido de asientos!" << endl;
			//Alterna el flag
			flag = false;
			goto LOOP6;
		//Si solo son numeros
		}else{
			//Alterna el flag
			flag = true;
			//Asigna , convierte de string a entero
			this -> seats = atoi(temp.c_str());
			store += ","+temp;
		}
	//Ejecuta esto hasta que el flag sea verdadero
	}while(!flag);
	
	/* --NUMERO DE ASIENTOS RESERVADOS-- */
	cout << "Cantidad de asientos reservados: ";
	LOOP7:do{
		//Ingresa
		getline(cin, temp);
		flag = true;
		
		//Comprueba lo ingresado sea solo numeros
		if (!checkNumber(temp)){
			cout << "Introduzca un número válido de asientos reservados!" << endl;
			//Alterna el flag
			flag = false;
			goto LOOP7;
		//Comprueba que el numero de asientos este en el limite de asientos
		//(Convierte de string a entero)
		}else if ( atoi(temp.c_str()) > this -> seats ) {
			cout << "¡Los asientos reservados deben ser menores que los asientos del avión!" << endl;
			//Alterna flag
			flag = false;
			goto LOOP7;
		//Cuando los datos sean correctos
		}else {
			//ALterna el flag
			flag = true;
			//Almacena
			//(Convierte de string a entero)
			this -> booked_seats = atoi(temp.c_str());
			store += ","+temp;
		}
	//Ejecuta esto mientras que el flag no sea verdadero
	}while(!flag);
	cout << endl;
	
	
	flist.push_back(*this); //Anade el objeto a  flist(Lista de vuelos)
	
	Queue q(this -> flightNo); //Crea una nueva cola para el nuevo vuelo
	qlist.push_back(q); //Anade el objetos a qlist (Lista de Cola)
	
	cout << "N° de vuelo: "<< this -> flightNo << " fue agregado exitosamente!" << endl;
	//Escribe en nuestro reporte de vuelo
	writeFlight(store);
}

void Flight::deleteFlight(int num){
		
		//Itera la lista de colas de vuelos
		for (std::list<Queue>::iterator i = qlist.begin(); i != qlist.end(); ++i){
			if( num == i -> getNo() ){
				
				//Ingresa SI la cola de espera para el vuelo NO esta vacia
				if (!i -> isEmpty()) {
					//Elimina el objeto de flist (Lista de vuelos)
					//Itera la lista de vuelos
					for (std::list<Flight>::iterator i2 = flist.begin(); i2 != flist.end(); ++i2){
						if( num == (i2 -> flightNo) ){
							i2 = flist.erase(i2);
							i = qlist.erase(i);
							cout << "Vuelo con número: " << num << " fue eliminado correctamente " << endl;
							return;
						}
					}
				}else{
					cout << "Hay pasajeros en la cola del vuelo con N°: " << num << endl;
					cout << "¡Primero elimínelos TODOS de la cola!" << endl;
					return;
				}
			}
		}
		cout << "¡Este número de vuelo no existe!" << endl;
		return;					
}
//Mostrar la informacion de un vuelo especifico
void Flight::displayFlightInfo(int num){

	string l_time, a_time; // Horario de salida y de llegada
	//Para convertir
	stringstream convert; 
	stringstream convert2; 
	
	//Itera la lista que tiene los vuelos
	for (std::list<Flight>::iterator i = flist.begin(); i != flist.end(); ++i) {
		//Compara el numero ingresado con el numero de vuelo actual
		if (num == i -> flightNo) {
				
			convert.str(std::string()); // Limpia stringstream "convert"
			convert2.str(std::string()); // Limpia stringstream "convert2"
			
			//Convierte horas y minutos de Salida
			convert << i -> t_leave.hour;
			convert2 << i -> t_leave.min;		 
			l_time = convert.str() + ":" + convert2.str();
				
			convert.str(std::string()); // Limpia stringstream "convert"
			convert2.str(std::string()); // Limpia stringstream "convert2"
			
			//Convierte horas y minutos de Llegada
			convert << i -> t_arrive.hour;
			convert2 << i -> t_arrive.min;		 
			a_time = convert.str() + ":" + convert2.str();
			
			//Muestra la informacion
			cout << left << setw(10) << 
			"VUELO" << left << setw(10) << 
			"DESDE" << left << setw(10) << 
			"A" << left << setw(10) << 
			"SALIDA" << left << setw(10) << 
			"LLEGADA" << left << setw(10) << 
			"PRECIO" << left << setw(10) << 
			"TIPO" << left << setw(10) << 
			"ASIENTOS" << left << setw(10) << 
			"RESERVADO" << endl;
			cout << left << setw(10) << 
			i -> flightNo << left << setw(10) << 
			i -> from << left << setw(10) << 
			i -> to << left << setw(10) << 
			l_time << left << setw(10) << 
			a_time << left << setw(10) << 
			i -> cost << left << setw(10) << 
			i -> plane_type << left << setw(10) << 
			i -> seats << left << setw(10) << 
			i -> booked_seats << endl;
			
			//Muestra la cola del vuelo segun el numero
			Queue::display(num);
			//Termina
			return;
		}
	}	
	//Cuando no sea un numero valido
	cout << "Se proporcionó un número de vuelo no válido " << endl;
}
//Mostrar los vuelos registrados en el sistema
void Flight::displaySchedule(){
	
	string l_time, a_time; // Horario de salida y de llegada
	//Para convertir
	stringstream convert; 
	stringstream convert2; 
	 
		//Muestra la informacion del vuelo
		cout << "\n\t\t\t\t HORARIO DE VUELO" << endl << endl;
		cout << left << setw(10) << 
		"VUELO" << left << setw(10) << 
		"DESDE" << left << setw(10) << 
		"A" << left << setw(10) << 
		"SALIDA" << left << setw(10) << 
		"LLEGADA" << left << setw(10) << 
		"PRECIO" << left << setw(10) << 
		"TIPO" << left << setw(10) << 
		"ASIENTOS" << left << setw(10) << 
		"RESERVADO" << endl;
		
		//Itera la lista de vuelos
		for (std::list<Flight>::iterator i = flist.begin(); i != flist.end(); ++i) {
				convert.str(std::string());	// Limpia stringstream "convert"
				convert2.str(std::string());	// Limpia stringstream "convert2"
				
				//Convierte las horas y minutos de salidad
				convert << i -> t_leave.hour;
				convert2 << i -> t_leave.min;		 
				l_time = convert.str() + ":" + convert2.str();
				
				convert.str(std::string());	// Limpia stringstream "convert"
				convert2.str(std::string());	// Limpia stringstream "convert2"
				
				//Convierte las horas y minutos de llegada
				convert << i -> t_arrive.hour;
				convert2 << i -> t_arrive.min;		 
				a_time = convert.str() + ":" + convert2.str();
				
				//Muestra
				cout << left << setw(10) << 
				i -> flightNo << left << setw(10) << 
				i -> from << left << setw(10) << 
				i -> to << left << setw(10) << 
				l_time << left << setw(10) << 
				a_time << left << setw(10) << 
				i -> cost << left << setw(10) << 
				i -> plane_type << left << setw(10) << 
				i -> seats << left << setw(10) << 
				i -> booked_seats << endl;
		}
		
		cout << endl;
}

//Reservar ASiento
//Con numero de vuelo y el numero de asientosasiento
void Flight::resSeat(int num, int val){
	//Itera la lista de vuelos
	for (std::list<Flight>::iterator i = flist.begin(); i != flist.end(); ++i){	
		//Encuentra el vuelo
		if( num == (i -> flightNo) ){			
			//Agrega el asiento
			i -> booked_seats += val ;
			break;
		}
	}	
}

//Comprueba si es que existe un vuelo , ingresando su numero
bool Flight::flightExists(int num){
	//Itera la lista de vuelos
	for (std::list<Flight>::iterator i = flist.begin(); i != flist.end(); ++i){
		//Compara
		if (num == i -> flightNo){
			//Encontrado
			return true;
		}
	}
	//No encontrado
	return false;
}

//Verifica si hay asientos disponibles
bool Flight::checkForSeats(int num){
	//Itera la lista de vuelos
	for (std::list<Flight>::iterator i = flist.begin(); i != flist.end(); ++i){		
		//Encuentra el vuelo
		if( num == (i -> flightNo) ){
			//COmpara el numero de asientos con los reservados	
			if( i -> seats == i -> booked_seats )
					//No dipsonibles
					return false;
				else
					//Si disponibles
					return true;
		}
	}
	//En caso no encuentre
	return false;
}

/* ----FUNCIONES DE LA CLASE Person---- */	

//Reservar un vuelo
void Person::book(){
	
	/* ----INICIALIZA VARIABLES----*/
	/* --FLIGHTS (Vuelos)-- */
	string temp; //Variable temp para almacenar lo ingresado por el usuario, para ser comprobado despues
	int num; // Almacena el numero dedl vuelo, despues de haber sido comprobado correctamente
	
	/* --VARIABLES PARA VUELOS NO DIRECTOS-- */
	int counter = 1; // Almacena la cantidad(>=2) de los vuelos no directos
	string choice; // Almacena la eleccion del usuario para anadir o no mas vuelos a su reservacion
	//HOrarios de salida y llegada
	Time tArriving; 
	Time tLeaving;
       //Destino de salida y llegada	
	string Departure; 
	string Destination; 
	list<int> nums; // Guarda los numeros de los vuelos
	list<int>::iterator i1 = nums.begin(); //iteracion para acceder a la lista de los numeros de los vuelos
	
	/* --VARIABLE PARA ITERACIONES-- */
	bool flag = true;
	
	// Limpia
	cin.clear();
	cin.ignore(256,'\n');
	
	//En caso la lista de vuelos este vacia
	if (!flist.empty()) {
		cout << "Inserte 'y' (si) para un nuevo cliente o 'n' (no) para un cliente existente.";
		getline(cin, choice);
		
		// Ingresa si el cliente es nuevo
		if (choice == "y" || choice == "Y") {
			
			cout << "Por favor, danos tu información personal. " << endl;
		
			/* --NOMBRE-- */
			cout << "Nombre: ";
			flag = false;
			
			// Comprueba lo ingresado
			LOOP8:do{
				getline(cin, this -> name);
				//COmprueba tamano y si son solo letras
				if ( (this -> name.length() <= 10) && (checkString(this -> name)) ){
					//Cambia flag a true
					flag = true;
				//Si no
				}else {
					//Lo deja en false
					cout << "¡Por favor inserte un nombre válido! ";
					goto LOOP8;
				}
			//Ejecuta esto hasta que sea verderos
			}while(!flag);
			
			/* --APELLIDO-- */
			cout << "Apellido: ";
			flag = false;
			
			// Comprueba lo ingresado
			LOOP9:do{
				getline(cin, this -> surname);
				//COmprueba tamano y si son solo letras
				if ( (this -> surname.length() <= 10) && (checkString(this -> surname)) ){
					 //Cambia flag a true
					flag = true;
				//Sino
				}else {
					//Deja en false
					cout << "Introduzca un apellido válido! ";
					goto LOOP9;
				}
			//Ejecuta esto hasta que sea verderos
			}while(!flag);
			
			/* --NUMERO DE PASAPORTE-- */
			cout << "Número de pasaporte: ";
			
			// Comprueba lo Ingresado
			LOOP10:do{
				
				getline(cin, temp);
				flag = true;
				//Comprueba que solo sean numeros
				if (!checkNumber(temp)){
					cout << "Introduzca un número de pasaporte válido! " << endl;
					//Alterna el flag
					flag = false;
					goto LOOP10;
				//Comprueba que sea un pasaporte unico
				//Convierte de string a entero
				}else if (!Person::uniquePass( atoi(temp.c_str()) )) {
					cout << "Verifique la validez de su número de pasaporte" << endl;
					//ALterna flag
					flag = false;
					goto LOOP10;
				//Datos validos
				}else{
					//Flag Verdadero
					flag = true;
					//Asign
					this -> passportNo = atoi(temp.c_str());
				}
			//Asigna esto hata que sea verdadero	
			}while(!flag);
			
			/* --NACIONALIDAD-- */
			cout << "Nacionalidad: ";
			flag = false;
			
			// Comprueba lo Ingresado
			LOOP11:do{
				
				getline(cin, this -> nationallity);
				//COmprueba el tamano y si son solo letras
				if ( (this -> nationallity.length() <= 10) && (checkString(this -> nationallity)) ){
					flag = true;
				//Si no
				}else {
					//Flag continua en false
					cout << "Introduzca una nacionalidad válida! ";
					goto LOOP11;
				}
			//Ejecuta esto hasta q flag sea verdadero
			}while(!flag);
			
			/* --DIRECCION-- */
			cout << "Dirección: ";
			getline(cin, this -> address);
			
			/* --TELEFONO-- */
			cout << "Teléfono: "; 
			getline(cin, temp);
			
			// Comprueba lo Ingresado , osea solo numeros
			while (!checkNumber(temp)) {
				cout << "Introduzca un número de teléfono válido!" << endl;
				getline(cin, temp);
			}
			//Asigna (convierte)
			this -> tel = atoi(temp.c_str());

			
		}else { // Cliente existente
			cout << "Por favor dénos su número de pasaporte: ";
			getline(cin, temp);
			
			// Comprueba lo Ingresado, es decir solo numeros
			while(!checkNumber(temp)){
				cout << "Introduzca un número de pasaporte válido!" << endl;
				//ALterna flag
				flag = false;
				getline(cin, temp);
			}
				
			// Comprueba si el pasaporte es NO unico
			// (Convierte de string a int)
			if ( !(Person::uniquePass( atoi(temp.c_str()) ))) {
				//Itera la lista de Personas	
				for (std::list<Person>::iterator i = plist.begin(); i != plist.end(); ++i){
					//Encuentra a la persona
					//(Convierte)	
					if (atoi(temp.c_str()) == i -> passportNo) {
							//Copia la informacion de la persona
							this -> name = i -> name;
							this -> surname = i -> surname;
							this -> passportNo = i -> passportNo;
							this -> nationallity = i -> nationallity;
							this -> address = i -> address;
							this -> tel = i -> tel;
							
							//Vuelve a iterar
							for (std::list<int>::iterator i2 = i->flights.begin(); i2 != i->flights.end(); ++i2) {
								//Agrega a vuelos
								this -> flights.push_back(*i2);
							}
							
							// Despues de copiar la informacion del cliente
							// Elimina el viejo objeto ,reapuntandolo a el
							i = plist.erase(i);
							break;
						}
					}
			//En caso no sea un pasaportevalido
			}else {
				cout << "¡Número de pasaporte incorrecto!" << endl;
				return;
			}
		}
		
		
		// Muestra los Vuelos
		Flight::displaySchedule(); 
		
		/* --NUMERO DE VUELO-- */
		cout << "\n\nIngrese el número del vuelo que le interesa: ";
		getline(cin, temp);
		flag = true;
		
		// Comprueba lo Ingresado
		// SI es solo numeros y si
		// El numero del vuelo existe
		// (Convierte de string a etnero)
		while ( !checkNumber(temp) && !Flight::flightExists(atoi(temp.c_str())) ) {
			cout << "Introduzca un número de vuelo válido! " << endl;
			getline(cin, temp);
		}
		//Convierte de string a entero
		num = atoi(temp.c_str());
		
		/*
		------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ 
							RESERVAR EL/LOS VUELO(S) ELEGIDOS POR EL CLIENTE	 
		------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
		*/
		
		//VUELO DIRECTO
		if(Flight::checkForSeats(num)){ //Comprueba por reservaciones disponibles
			//Agrega a la lista de vuelos		
			this -> flights.push_back(num);
			//Reserva el asiento (solo 1 asiento)
			Flight::resSeat(num,1);
			cout << "Tu vuelo con N°: " << num << " se reservó con éxito." << endl;
		
		// VUELO NO DIRECTO	
		}else{
			choice = "y";
			
			cout << "No hay vuelos directos disponibles para este destino"<< endl;
			cout << "Por favor ingrese los números especiales para los vuelos alternativos.";
			
			while(choice == "y" || choice == "Y"){ //Sale si el usuario no quiere agregar mas vuelos
				
		  LOOP12:cout << "\nNumber #" << counter << " : ";
				getline(cin, temp);
				
				//Comprueba lo Ingresado
				//SI es solo numeros y si existe el vuelo
				while ( !checkNumber(temp) && !Flight::flightExists(atoi(temp.c_str())) ) {
					cout << "Introduzca un número de vuelo válido!" << endl;
					cin >> temp;
				}
				
				//Convierte de string a entero
				num = atoi(temp.c_str());	
								
				if (counter > 1){ // Ingresa solo si el usuario ha ingresado  2 o mas vuelos	
				
					// Almacena el horario de la llegada y salida , y la ciudad de la llegada y salida
					//Itera la lista de vuelos
					for (std::list<Flight>::iterator i2 = flist.begin(); i2 != flist.end(); ++i2) {
						//Compara el numero ded vuelos
						//i1 empezo en el 1ero
						//y i2 esta iterando
						//Compara si es que este sera el siguiente del  1ero
						if (*i1 == i2 -> getFlightNo()) {
							//Asigna la llegada y el destino					
							tArriving = i2 -> getArrivingTime();
							Destination = i2 -> getDestination();
						//En caso no continuedel 1er vuelo
						}else if (num == i2 -> getFlightNo()) {
							//Asigna el horario de salidad y la salida
							tLeaving = i2 -> getLeavingTime();
							Departure = i2 -> getDeparture();
						}
					}
					
					// Comprueba la validez de cada vuelo
					if ( !(checkTime2(tLeaving,tArriving) && !Departure.compare(Destination)) ) {
						cout << "Introduzca un vuelo a un destino válido!" << endl;
						goto LOOP12;	
					}
				}
				
				nums.push_back(num); // Anade el numero del vuelo		
				//Avanzla la iteracion de i1
				i1++;
				//Pregunta si quiere anadir otro vuelo
				if(counter >= 2){ 
					cout << "¿Desea agregar más números de vuelo? (y/n)"; 
					getline(cin, choice);
				}
				//AUmenta el contador
				counter++; 
			} 
			
			
			// COmprueba por puestos en el vuelo elegido
			// Y anade todos los numeros de los vuelos al nodo especifico de la lista de los vuelos
			for (std::list<int>::iterator i = nums.begin(); i != nums.end(); ++i){
				//Comprueba si se pueden asientos
				flag = Flight::checkForSeats(*i) and flag;
				//Anade a la lista de vuelos
				this -> flights.push_back(*i);
			}
			
			//Ingresa SOLO si hay asientos disponibles y se reserva un asiento para cada vuelo elegio
			if(flag){
				//Itera
				for (std::list<int>::iterator i = nums.begin(); i != nums.end(); ++i){				
					//Reserva 1 asiento
					Flight::resSeat(*i,1);
				}
				cout << "Sus vuelos se reservaron correctamente." << endl;
			//Si por lo menos un vuelo esta completamente reservado anade al cliente a la fila para cada vuelo
			}else{
				cout << endl;
				cout << "Algunos de los vuelos que insertó estaban sobre reservados." << endl;
				//Itera la lista 1 de vuelos
				for (std::list<int>::iterator i = nums.begin(); i != nums.end(); ++i){
					//Itera la 2da lista (Osea de colas)
					for (std::list<Queue>::iterator i2 = qlist.begin(); i2 != qlist.end(); ++i2){
						//Compara si corresponde el vuelo
						if( *i == i2 -> getNo()){
							//Lo agrega a la cola
							i2 -> enqueue(*this);
						}
					}
				}
				cout << "Lo hemos agregado en las colas para cada uno de estos vuelos." << endl;
			}
		}
		plist.push_back(*this); //Anade el objeto a la lista de personas del vuelo
	}else{
		cout << "No hay vuelos disponibles en este momento." << endl;
		return;
	}	
}

//Cancelar vuelo para el cliente mas antido
void Person::bookFromQueue(int num){  //Es llamado solo desde cancel()
	
	bool flag = true;
	Person queueFront; //Objeto del cilente que se encuentra al principio de la cola

	// Encuentra al cliente mas antiguo
	for (std::list<Queue>::iterator it = qlist.begin(); it != qlist.end(); ++it){
		//Cimpara
		if (num == it -> getNo() ){
			//En caso no este vacio
			if( !(it -> isEmpty()) ){
				//Cambia de cabecer
				queueFront = it -> oldest();
				break;
			}else{
				return;
			}	
		}
	}
	
	//Comprueba si todas las elecciones de los clientes  tienen asientos disponibles
	for (std::list<int>::iterator i = queueFront.flights.begin(); i != queueFront.flights.end(); ++i){
		flag = Flight::checkForSeats(*i) and flag;
	}
	
	//INgresa SOLO si hay vacantes en TODAS las elecciones de los clientes en sus respectivos vuelos
	// y se los reserva
	if(flag){			
		Node* p = new Node; 
		
		// Encuentra los vuelos del cliente mas antiguo
		for (std::list<int>::iterator i = queueFront.flights.begin(); i != queueFront.flights.end(); ++i){
			
			// Lo elimina de las colas
			for (std::list<Queue>::iterator i2 = qlist.begin(); i2 != qlist.end(); ++i2) {				
				//COmpara con la cola
				if(*i == i2 -> getNo()){
					//Obtiene la persona de la frente de la cola
					p = i2 -> getFront();		
					while(p != NULL){
						//Compara que sean la misma persona					
						if(queueFront.passportNo == p -> person.passportNo){
							//Lo remueve
							i2 -> dequeue();
							//Lo agrega a la lista 1
							Flight::resSeat(*i,1);	
						}
						//Avanza						
						p = p -> next;
					}
				}
			}
					
		}	
	}	
}
//Cancela la reservacion de un asiento
void Person::cancel(){
	//Pasaporte de la persona
	//y el numero de vuelo	
	string passport, num; 
	int counter = 1; //Contador que almacena entradas incorrectas del usuario
	bool flightFound = false; //Es falso si el cliente ya tiene un asiento reservado en ese vuelo
	bool isInQueue = false; //Es falso si el cliente ,que sera eliminado,no pertenece
				// a la cola de cada vuelo
	//Si la lista de personas del vuelo no  esta vacia
	if (!plist.empty()) {
		// Limpia
		cin.clear();
		cin.ignore(256,'\n');
		//INgresa pasaporte
		cout << "Indíquenos su número de pasaporte: ";
		getline(cin, passport); cout << endl;
		
		// Comprueba lo ingresado si es olo numeros
		while(!checkNumber(passport)){
			cout << "Introduzca un número de pasaporte válido." << endl;
			getline(cin, passport); cout << endl; 
		}
		//Busca si se encuentra la persona
		//y se muestran sus datos
		while(!Person::displayPersonInfo( atoi(passport.c_str()) )) {
					
			//Sale de la apĺicacion si es que se le da un numero de pasaporte incorrecto 5 veces
			if (counter == 5) {
				cout << "Se dio demasiadas veces un número de pasaporte incorrecto.";
				return;
			}else{
				cout << "Verifique su número de pasaporte." << endl;
				getline(cin, passport); cout << endl;
				
				//Comprueba si es que el numero de pasaporte consta solo de digitos
				while(!checkNumber(passport)){
					cout << "Introduzca un número de pasaporte válido!" << endl;
					getline(cin, passport); cout << endl; 
				}
			}
			//Suma si se equivoca una vez			
			counter++;
		}
		
		//Pide el vuelo
		cout << "\n¿Qué vuelo desea cancelar (ingrese el número de vuelo)?"; 
		getline(cin, num);
		counter = 1;
		
		// Comprueba lo ingresado si es solo numeros
		while(!checkNumber(num)){
			cout << "Introduzca un número de vuelo válido." << endl;
			getline(cin, num); cout << endl; 
		}
		
		// Itera atraves de los vuelos del pasajero
		for (std::list<Person>::iterator i = plist.begin(); i != plist.end(); ++i){
			//Encuntra el vuelo
			if (atoi(passport.c_str()) == i -> passportNo) {	
				
				// Comprueba lo ingresado y sale si el contador de errores = 5
				do{
					//Itera la lista de vuelo					
					for (std::list<int>::iterator i2 = (i -> flights).begin(); i2 != (i -> flights).end(); ++i2){
						//Encuentra el vuelo
						if (atoi(num.c_str()) == *i2) {
							//VUelo encontrado
							flightFound = true;
							//Lo saca de 
							i2 = flights.erase(i2); // Elimina el vuelo de la iformacion del pasajero
							break;
						}
					}
					//Equivoco 5 veces
					if (counter == 5){
						cout << "Se dio un número de vuelo incorrecto demasiadas veces.";
						return;
					//Si el vuelo no fue encontrado
					}else if(!flightFound){
						cout << "¡Por favor verifique su número de vuelo!.";
						getline(cin, num); cout << endl;
						
						// Comprueba lo ingresado
						while(!checkNumber(num)){
						cout << "Introduzca un número de vuelo válido." << endl;
						getline(cin, num); cout << endl; 
						}
					}
					//Numero de veces equivocadas				
					counter++;
				//Ejecuta hasta que no sea encontrado
				}while(!flightFound);
				break;
			}
		}
		
		//Elimina al cliente de la colda de vuelos , si es que formaban parte de el
		for (std::list<Queue>::iterator i = qlist.begin(); i != qlist.end(); ++i){
			//Encuentra
			if( atoi(num.c_str()) == i -> getNo() ){
				//Si es que la cola no esta vacia
				if(!i -> isEmpty()){
					//Guarda el nodo y el anterior
					Node* p = new Node;			
					Node* previousNode;
					//Obtiene la cabecera
					p = i -> getFront();
					
					//Mientras q no termine la cola
					while(p!=NULL){
						//Encuntra a la persona
						if (atoi(passport.c_str()) == p -> person.passportNo){
							//Flag
							isInQueue = true;
							
							//Ingresa si el cliente esta en la 1era posicion
							if (p == i -> getFront()){
								//Asigna la nueva cabecer
								i -> setFront(p -> next);
								// Ingresa si la cola solo tiene un elemento
								if (i -> getFront() == i -> getRear()){
									i -> setRear(NULL);
								}						
							}else if(p == i -> getRear()){ // Ingresa si el cliente esta en la ultima posicion de la cola del vuelo
								previousNode -> next = NULL;								
							}else{ 
								//En otro caso simplemente avanza
								previousNode -> next = p -> next;								
							}
							//Elimina
							delete(p);
							break;						
						}
						//Actualiza los nodos
						previousNode = p;
						p = p -> next;
					}
				}
			}
		}
		
		//Ingresa si el pasajer NO es parte de la actual cola
		if (!isInQueue){
			//Elimina el asiento en el vuelo
			Flight::resSeat(atoi(num.c_str()), -1); 		
			//ACtualiza la reservacion
			this -> bookFromQueue(atoi(num.c_str()));
		}
		cout << "\n¡Su reserva fue eliminada con éxito! \n" << endl;
	}else {
		cout << "¡No hay clientes registrados en este momento!" << endl;
	}
}

//Mostrar la informacion de una persona
bool Person::displayPersonInfo(int passport){
	//Itera la lista de personas
	for (std::list<Person>::iterator i = plist.begin(); i != plist.end(); ++i){
		//Compara si es la persona
		if(passport == i -> passportNo){
			//Muestra la informacio
			cout << "\n\t\t\t\t INFORMACIÓN PERSONAL" << endl << endl;
			cout << left << setw(15) << "NOMBRE" << left << setw(15) << "APELLIDO" << left << setw(15) << "N° PASAPORTE" << left << setw(15) << "NACIONALIDAD" << left << setw(15) << "DIRECCION" << left << setw(15) << "TELÉFONO" << endl;
			
			cout << left << setw(15) << i -> name << left << setw(15) << i -> surname << left << setw(15) << i -> passportNo << left << setw(15) << i -> nationallity << left << setw(15) << i -> address << left << setw(15) << i -> tel << endl << endl;
			cout << "Su vuelo (s):";
			//Itera su lista de vuelos
			for (std::list<int>::iterator i2 = (i -> flights).begin(); i2 != (i -> flights).end(); ++i2){
				cout << *i2 << "  ";
			}
			cout << endl;
			//Es encontrado
			return true;
		}
	}
	cout << "No se encontró el número de pasaporte. ¡Revisar otra vez!" << endl;
	//No es encontrado
	return false;	
}
//Comprueba que el pasaporte sea unico
bool Person::uniquePass(int passport){
	//Itera la lista de personas
	for (std::list<Person>::iterator i = plist.begin(); i != plist.end(); ++i){
		//En caso sea repetido
		if (passport == i -> getPassport()) {
			//NO es unico
			return false;
		}
	}
	//Es unico
	return true;
}

