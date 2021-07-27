//Incluyendo lo necesario
#include "General_impl.cpp"
#include <fstream>
/* 
------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ 
																IMPLEMENTACION	 
------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
*/

/* ----FUNCIONES DE LA CLASE Queue (Cola)---- */

Queue::Queue(int queueId){
	
	this -> queueNo = queueId;
    this -> rear = NULL;
    this -> front = NULL;
}
void storeQueue(Person p, int num){
	fstream f;
	f.open("queue"+to_string(num)+".csv",std::ios_base::app);
	string store = "";
	if(f.good()){
		store += to_string(num);
		store += ","+to_string(p.getPassport());
		store += ","+p.getName();
		store += ","+p.getSurname();
		store += ","+p.getNationality();
		store += ","+p.getAddress();
		store+="\n";
		f << store;
	}
	f.close();
}
void Queue::enqueue(Person p){
	cout << "Se encolo con exito" <<endl;
	storeQueue(p, this->getNo());
    Node* temp = new Node;

    temp -> person = p;
    temp -> next = NULL;

    if(this -> front == NULL){
       this -> front = temp;
    }else{
        this -> rear -> next = temp;
    }
    this -> rear = temp;
}

void Queue::dequeue(){

    Node* temp = new Node;

	temp = this -> front;

	this -> front = this -> front -> next;

	delete temp;
}

void Queue::display(int num){

	for (std::list<Queue>::iterator i = qlist.begin(); i != qlist.end(); ++i) {
		if(num == i -> queueNo){
			Node* p = new Node;
			p = i -> front;

			if(i -> front == NULL){
				cout<<"\nCola vacía.\n";
			}else{
				cout << "\nPasajeros esperando en cola: " << endl;
				cout << left << setw(15) << 
				"Passport" << left << setw(15) << 
				"Nombre" << left << setw(15) << 
				"Apellido" << endl;
				while(p!=NULL){
					cout << left << setw(15) << p -> person.getPassport() << left << setw(15) << p -> person.getName() << left << setw(15) << p -> person.getSurname() << endl;
					p = p -> next;
				}
			}
		}
	}
}

Person Queue::oldest(){
	
	return this -> front -> person;
}

bool Queue::isEmpty(){
 if(this -> front == NULL && this -> rear == NULL){
  	return true;
 }
 
 return false;
} 


/* ----FUNCIONES DE LA CLASE Menu---- */

void Menu::displayMenu(){
	
	int selection;	// Eleccion hecha por el usuario en el Menu
	string temp; // Variable para almacenar lo ingresado por el usuario
	
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
			cin >> temp; 
			
			// COmprueba la validez de lo ingresado por el usuario
			while (!checkNumber(temp)) {
				cout << "Por favor introduzca un numero!" << endl;
				cin.clear();
				cin.ignore(256,'\n');
				cin >> temp;
			}
			cout << endl;
			
			selection = atoi(temp.c_str());
			select(selection);
	
	}while(true);
}

void  Menu::select(int selection){
	
	Flight f; // Objeto Flight (Vuelo)
	Person p; // Objeto Person (Persona)
	string temp; // Variable para almacenar lo ingresado por el usuario
	
	switch(selection){
		case 1://agregar flught
			f.addFlight();
			break;
		case 2://eliminar flight
			if (!flist.empty()) {
				cout << "Ingrese el número de vuelo que desea eliminar:"; cin >> temp;
				cout << endl;
				while (! checkNumber (temp)) {
					cout << "¡El número de vuelo debe ser un número!" << endl;
					cin.clear();
					cin.ignore(256,'\n');
					cin >> temp;
					cout << endl;
				}
				
				Flight::deleteFlight( atoi(temp.c_str()) );
			}else {
				cout << "No hay vuelos para eliminar" << endl;
			}
						
			break;
		case 3://mostra horario de vuelo
			if (!flist.empty()) {
				Flight::displaySchedule();
			}else {
				cout << "¡No hay vuelos programados!" << endl;
			}
			break;
		case 4:
			if (!flist.empty()) {
				cout << "Introduzca el número de vuelo:";
				cin >> temp; cout << endl;
				while (!checkNumber(temp)){
					cout << "¡El número de vuelo debe ser un número!" << endl; 
					cin.clear();
					cin.ignore(256,'\n');
					cin >> temp;
					cout << endl;
				}
				Flight::displayFlightInfo( atoi(temp.c_str()) );
			}else {
				cout << "¡No hay vuelos programados!" << endl;
			}			
			break;
		case 5:
			if (!plist.empty()){
				cout << "Introduzca el número de pasaporte:";
				cin >> temp;
				while (!Person::displayPersonInfo( atoi(temp.c_str()) )) {
					cout << "¡Número de pasaporte incorrecto!" << endl;
					cin.clear();
					cin.ignore(256,'\n');
					cin >> temp;
					cout << endl;
				}
			}else{
				cout << "¡No hay clientes registrados en este momento!" << endl;
			}
			break;
		case 6:
			p.book();
			break;
		case 7:
			p.cancel();
			break;
		case 8:
			Menu::exit_prog();
			break;
		default:
			cout << "Selección invalida \n"; 
	}
	
}

void Menu::exit_prog(){
	
	cout << "¡Gracias por usar nuestro sistema! \n";
	exit(1); // exit
}

/* ----FUNCIONES DE LA CLASE Flight (Vuelo)---- */
void writeFlight(string line){
	fstream f;
	f.open("reportFlights.csv",  std::ios_base::app);
	if(f.good()){
		f << line + "\n";
	}
}

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
		if (!checkNumber(temp)){
			cout << "Introduzca un número de vuelo válido! " << endl;
			flag = false;
			getline(cin, temp);
		}else if (Flight::flightExists( atoi(temp.c_str()) )) {
			cout << "¡Este vuelo ya existe!" << endl;
			cout << "Introduzca un número de vuelo válido!:" << endl;
			flag = false;
			getline(cin, temp);
		}else {
			flag = true;
			this -> flightNo = atoi(temp.c_str());
			store += temp;
		}
	}while(!flag);
	
	/* --SALIDA-- */
	cout << "Salida: ";
	flag = false;
	
	// Comprueba lo ingresado
	LOOP:do{
		getline(cin, temp);
		if ( (temp.length() <= 10) && (checkString(temp)) ){
			this -> from = temp;
			store+=","+temp;
			flag = true;
		}else {
			cout << "Introduzca una ciudad de salida válida!: ";
			goto LOOP;
		}
	}while(!flag);
	
	/* --DESTINO-- */
	cout << "Destino: "; 
	flag = false;
	
	// Comprueba lo ingresado
	LOOP2:do{
		getline(cin, temp);
		if ( (temp.length() <= 10) && (checkString(temp)) && (temp.compare(this -> from)) ){
			this -> to = temp;
			flag = true;
			store +=","+ temp;
		}else{
			cout << "Introduzca una ciudad de destino válida! ";
			goto LOOP2;
		}
	}while(!flag);
	
	/* --HORA DE SALIDA-- */
	cout << "Hora de embarque (por ejemplo, 19:40):"; //Pregunta al usuario la hora de embarque
	flag = false;
	
	//Comprueba lo ingresado
	LOOP3:do{
		getline(cin, temp);
		
		if( temp.length() != 5 || !checkTime(temp) ){
			cout << "Introduzca una hora de embarque válida (por ejemplo, 19:40)! ";
			goto LOOP3;			 
		}
		
		char t_temp[temp.length()];
		
		strcpy(t_temp, temp.c_str());
		
		//Divide el string
		pch = strtok(t_temp, ":");
		
		while(pch != NULL){
			fields.push_back(pch); 
			pch = strtok(NULL, ":");
		}
		
		hour = atoi(fields[0].c_str()); 
		min = atoi(fields[1].c_str()); 
		
		//Comprueba el horario
		if ((hour >=0 && hour<=23) && (min>=0 && min <=59)){ 
			this -> t_leave.hour = hour; 
			this -> t_leave.min = min; 
			store += ","+to_string(hour)+":"+to_string(min);
			flag = true;
		}else{
			cout << "Introduzca una hora de embarque válida (por ejemplo, 19:40).";
			fields.clear();		
		}	
		
	}while(!flag); 
	
	/* --HORARIO DE LLEGADA-- */
	cout << "Hora de llegada (por ejemplo, 21:40):";
	flag = false;
	fields.clear();	//limpia las grillas (porque fue usado antes en "HORARIO DE SALIDA")
	
	// Revisa lo ingresado
	LOOP4:do{
		getline(cin, temp);
		
		if( temp.length() > 5 || !checkTime(temp) ){
			cout << "Introduzca una hora de embarque válida (por ejemplo, 19:40).";
			goto LOOP4;			 
		}
		
		char t_temp[temp.length()];
		
		strcpy(t_temp, temp.c_str());
		
		//Divide el string
		pch = strtok(t_temp, ":");
		
		while(pch != NULL){
			fields.push_back(pch); 
			pch = strtok(NULL, ":");
		}
		
		hour = atoi(fields[0].c_str());
		min = atoi(fields[1].c_str());
		
		//Comprueba la validez del horario
		if ((hour >=0 && hour<=23) && (min>=0 && min <=59)){ 
			this -> t_arrive.hour = hour; 
			this -> t_arrive.min = min; 
			flag = true;
			store += ","+to_string(hour)+":"+to_string(min);
		}else{
			cout << "Introduzca una hora de llegada válida (por ejemplo, 19:40).";
			fields.clear();		
		}	
		
	}while(!flag); 
	
	/* --PRECIO DEL TICKET-- */
	cout << "Precio de la entrada:";
	LOOP5:do{
		
		getline(cin, temp);
		flag = true;
		
		//Comprueba lo ingresado
		if (!checkNumber(temp)){
			cout << "Por favor, inserte un precio de entrada válido." << endl;
			flag = false;
			goto LOOP5;
		}else{
			flag = true;
			this -> cost = atoi(temp.c_str());
			store += ","+temp;
		}
	}while(!flag);
	
	/* --TIPO DE AVION-- */
	cout << "Tipo de avión:";
	getline(cin, this -> plane_type);
	while(this -> plane_type.empty()){
		cout << "Introduzca un tipo de avión válido!" << endl;
		getline(cin, this -> plane_type);
	}
	store += ","+this->plane_type;
	
	/* --NUMERO DE ASIENTOS-- */
	cout << "Numero de asientos: ";
	LOOP6:do{
		
		getline(cin, temp);
		flag = true;
		
		//Comprueba lo Ingresado
		if (!checkNumber(temp)){
			cout << "Por favor, inserte un número válido de asientos!" << endl;
			flag = false;
			goto LOOP6;
		}else{
			flag = true;
			this -> seats = atoi(temp.c_str());
			store += ","+temp;
		}
	}while(!flag);
	
	/* --NUMERO DE ASIENTOS RESERVADOS-- */
	cout << "Cantidad de asientos reservados: ";
	LOOP7:do{
		
		getline(cin, temp);
		flag = true;
		
		//Comprueba lo ingresado
		if (!checkNumber(temp)){
			cout << "Introduzca un número válido de asientos reservados!" << endl;
			flag = false;
			goto LOOP7;
		}else if ( atoi(temp.c_str()) > this -> seats ) {
			cout << "¡Los asientos reservados deben ser menores que los asientos del avión!" << endl;
			flag = false;
			goto LOOP7;
		}else {
			flag = true;
			this -> booked_seats = atoi(temp.c_str());
			store += ","+temp;
		}
	}while(!flag);
	cout << endl;
	
	
	flist.push_back(*this); //Anade el objeto a  flist(Lista de vuelos)
	
	Queue q(this -> flightNo); //Crea una nueva cola para el nuevo vuelo
	qlist.push_back(q); //Anade el objetos a qlist (Lista de Cola)
	
	cout << "N° de vuelo: "<< this -> flightNo << " fue agregado exitosamente!" << endl;
	writeFlight(store);
}

void Flight::deleteFlight(int num){
		
		for (std::list<Queue>::iterator i = qlist.begin(); i != qlist.end(); ++i){
			if( num == i -> getNo() ){
				
				//Ingresa SI la cola de espera para el vuelo NO esta vacia
				if (!i -> isEmpty()) {
					//Elimina el objeto de flist (Lista de vuelos)
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

void Flight::displayFlightInfo(int num){

	string l_time, a_time; // Horario de salida y de llegada
	stringstream convert; 
	stringstream convert2; 
	
	for (std::list<Flight>::iterator i = flist.begin(); i != flist.end(); ++i) {
		if (num == i -> flightNo) {
				
			convert.str(std::string()); // Limpia stringstream "convert"
			convert2.str(std::string()); // Limpia stringstream "convert2"
			
			convert << i -> t_leave.hour;
			convert2 << i -> t_leave.min;		 
			l_time = convert.str() + ":" + convert2.str();
				
			convert.str(std::string()); // Limpia stringstream "convert"
			convert2.str(std::string()); // Limpia stringstream "convert2"
			
			convert << i -> t_arrive.hour;
			convert2 << i -> t_arrive.min;		 
			a_time = convert.str() + ":" + convert2.str();
			
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
			
			Queue::display(num);
			return;
		}
	}	
	
	cout << "Se proporcionó un número de vuelo no válido " << endl;
}

void Flight::displaySchedule(){
	
	string l_time, a_time; // Horario de salida y de llegada
	stringstream convert; 
	stringstream convert2; 
	 
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
		
		for (std::list<Flight>::iterator i = flist.begin(); i != flist.end(); ++i) {
				convert.str(std::string());	// Limpia stringstream "convert"
				convert2.str(std::string());	// Limpia stringstream "convert2"
				
				convert << i -> t_leave.hour;
				convert2 << i -> t_leave.min;		 
				l_time = convert.str() + ":" + convert2.str();
				
				convert.str(std::string());	// Limpia stringstream "convert"
				convert2.str(std::string());	// Limpia stringstream "convert2"
				
				convert << i -> t_arrive.hour;
				convert2 << i -> t_arrive.min;		 
				a_time = convert.str() + ":" + convert2.str();
				
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

void Flight::resSeat(int num, int val){
	for (std::list<Flight>::iterator i = flist.begin(); i != flist.end(); ++i){	
		if( num == (i -> flightNo) ){			
			i -> booked_seats += val ;
			break;
		}
	}	
}

bool Flight::flightExists(int num){
	for (std::list<Flight>::iterator i = flist.begin(); i != flist.end(); ++i){
		if (num == i -> flightNo){
			return true;
		}
	}
	return false;
}

bool Flight::checkForSeats(int num){
	for (std::list<Flight>::iterator i = flist.begin(); i != flist.end(); ++i){		
		if( num == (i -> flightNo) ){
				if( i -> seats == i -> booked_seats )
					return false;
				else
					return true;
		}
	}
	return false;
}

/* ----FUNCIONES DE LA CLASE Person---- */	

void Person::book(){
	
	/* ----INICIALIZA VARIABLES----*/
	/* --FLIGHTS (Vuelos)-- */
	string temp; //Variable temp para almacenar lo ingresado por el usuario, para ser comprobado despues
	int num; // Almacena el numero dedl vuelo, despues de haber sido comprobado correctamente
	
	/* --VARIABLES PARA VUELOS NO DIRECTOS-- */
	int counter = 1; // Almacena la cantidad(>=2) de los vuelos no directos
	string choice; // Almacena la eleccion del usuario para anadir o no mas vuelos a su reservacion
	Time tArriving; 
	Time tLeaving; 
	string Departure; 
	string Destination; 
	list<int> nums; // Guarda los numeros de los vuelos
	list<int>::iterator i1 = nums.begin(); //iteracion para acceder a la lista de los numeros de los vuelos
	
	/* --VARIABLE PARA ITERACIONES-- */
	bool flag = true;
	
	// Limpia
	cin.clear();
	cin.ignore(256,'\n');
	
	if (!flist.empty()) {
		cout << "Inserte 'y' (si) para un nuevo cliente o 'n' (no) para un cliente existente: ";
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
				if ( (this -> name.length() <= 10) && (checkString(this -> name)) ){
					flag = true;
				}else {
					cout << "¡Por favor inserte un nombre válido! ";
					goto LOOP8;
				}
			}while(!flag);
			
			/* --APELLIDO-- */
			cout << "Apellido: ";
			flag = false;
			
			// Comprueba lo ingresado
			LOOP9:do{
				getline(cin, this -> surname);
				if ( (this -> surname.length() <= 10) && (checkString(this -> surname)) ){
					flag = true;
				}else {
					cout << "Introduzca un apellido válido! ";
					goto LOOP9;
				}
			}while(!flag);
			
			/* --NUMERO DE PASAPORTE-- */
			cout << "Número de pasaporte: ";
			
			// Comprueba lo Ingresado
			LOOP10:do{
				
				getline(cin, temp);
				flag = true;
				
				if (!checkNumber(temp)){
					cout << "Introduzca un número de pasaporte válido! " << endl;
					flag = false;
					goto LOOP10;
				}else if (!Person::uniquePass( atoi(temp.c_str()) )) {
					cout << "Verifique la validez de su número de pasaporte" << endl;
					flag = false;
					goto LOOP10;
				}else{
					flag = true;
					this -> passportNo = atoi(temp.c_str());
				}	
			}while(!flag);
			
			/* --NACIONALIDAD-- */
			cout << "Nacionalidad: ";
			flag = false;
			
			// Comprueba lo Ingresado
			LOOP11:do{
				
				getline(cin, this -> nationallity);
				
				if ( (this -> nationallity.length() <= 10) && (checkString(this -> nationallity)) ){
					flag = true;
				}else {
					cout << "Introduzca una nacionalidad válida! ";
					goto LOOP11;
				}
			}while(!flag);
			
			/* --DIRECCION-- */
			cout << "Dirección: ";
			getline(cin, this -> address);
			
			/* --TELEFONO-- */
			cout << "Teléfono: "; 
			getline(cin, temp);
			
			// Comprueba lo Ingresado
			while (!checkNumber(temp)) {
				cout << "Introduzca un número de teléfono válido!" << endl;
				getline(cin, temp);
			}
			this -> tel = atoi(temp.c_str());
		}else { // Cliente existente
			cout << "Por favor dénos su número de pasaporte: ";
			getline(cin, temp);
			
			// Comprueba lo Ingresado
			while(!checkNumber(temp)){
				cout << "Introduzca un número de pasaporte válido!" << endl;
				flag = false;
				getline(cin, temp);
			}
				
			// Comprueba si el pasaporte es NO unico
			if ( !(Person::uniquePass( atoi(temp.c_str()) ))) {
					for (std::list<Person>::iterator i = plist.begin(); i != plist.end(); ++i){
						if (atoi(temp.c_str()) == i -> passportNo) {
							this -> name = i -> name;
							this -> surname = i -> surname;
							this -> passportNo = i -> passportNo;
							this -> nationallity = i -> nationallity;
							this -> address = i -> address;
							this -> tel = i -> tel;
							
							for (std::list<int>::iterator i2 = i->flights.begin(); i2 != i->flights.end(); ++i2) {
								this -> flights.push_back(*i2);
							}
							
							// Despues de copiar la informacion del cliente
							// Elimina el viejo objeto ,reapuntandolo a el
							i = plist.erase(i);
							break;
						}
					}
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
		while ( !checkNumber(temp) && !Flight::flightExists(atoi(temp.c_str())) ) {
			cout << "Introduzca un número de vuelo válido! " << endl;
			getline(cin, temp);
		}
		num = atoi(temp.c_str());
		
		/*
		------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ 
							RESERVAR EL/LOS VUELO(S) ELEGIDOS POR EL CLIENTE	 
		------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
		*/
		
		//VUELO DIRECTO
		if(Flight::checkForSeats(num)){ //Comprueba por reservaciones		
			this -> flights.push_back(num);
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
				while ( !checkNumber(temp) && !Flight::flightExists(atoi(temp.c_str())) ) {
					cout << "Introduzca un número de vuelo válido!" << endl;
					cin >> temp;
				}
				
				num = atoi(temp.c_str());	
								
				if (counter > 1){ // Ingresa solo si el usuario ha ingresado  2 o mas vuelos	
				
					// Almacena el horario de la llegada y salida , y la ciudad de la llegada y salida
					for (std::list<Flight>::iterator i2 = flist.begin(); i2 != flist.end(); ++i2) {
						if (*i1 == i2 -> getFlightNo()) {					
							tArriving = i2 -> getArrivingTime();
							Destination = i2 -> getDestination();
						}else if (num == i2 -> getFlightNo()) {
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
				i1++;
				
				if(counter >= 2){ 
					cout << "¿Desea agregar más números de vuelo? (y/n)"; 
					getline(cin, choice);
				}
				
				counter++; 
			} 
			
			
			// COmprueba por puestos en el vuelo elegido
			// Y anade todos los numeros de los vuelos al nodo especifico de la lista de los vuelos
			for (std::list<int>::iterator i = nums.begin(); i != nums.end(); ++i){
				flag = Flight::checkForSeats(*i) and flag;
				this -> flights.push_back(*i);
			}
			
			//Ingresa SOLO si hay asientos disponibles y se reserva un asiento para cada vuelo elegio
			if(flag){
				for (std::list<int>::iterator i = nums.begin(); i != nums.end(); ++i){				
					Flight::resSeat(*i,1);
				}
				cout << "Sus vuelos se reservaron correctamente." << endl;
			//Si por lo menos un vuelo esta completamente reservado anade al cliente a la fila para cada vuelo
			}else{
				cout << endl;
				cout << "Algunos de los vuelos que insertó estaban sobre reservados." << endl;
				
				for (std::list<int>::iterator i = nums.begin(); i != nums.end(); ++i){
					for (std::list<Queue>::iterator i2 = qlist.begin(); i2 != qlist.end(); ++i2){
						if( *i == i2 -> getNo()){
							i2 -> enqueue(*this);
						}
					}
				}
				cout << "Lo hemos agregado en las colas para cada uno de estos vuelos." << endl;
			}
		}
		plist.push_back(*this); //Anade el objeto a plist
	}else{
		cout << "No hay vuelos disponibles en este momento." << endl;
		return;
	}	
}

void Person::bookFromQueue(int num){  //Es llamado solo desde cancel()
	
	bool flag = true;
	Person queueFront; //Objeto del cilente que fue el ultimo en agregar

	// Encuentra al cliente mas antiguo
	for (std::list<Queue>::iterator it = qlist.begin(); it != qlist.end(); ++it){
		if (num == it -> getNo() ){
			if( !(it -> isEmpty()) ){
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
				if(*i == i2 -> getNo()){
					p = i2 -> getFront();		
					while(p != NULL){					
						if(queueFront.passportNo == p -> person.passportNo){
							i2 -> dequeue();
							Flight::resSeat(*i,1);	
						}							
						p = p -> next;
					}
				}
			}
					
		}	
	}	
}

void Person::cancel(){
		
	string passport, num; 
	int counter = 1; //Contador que almacena entradas incorrectas del usuario
	bool flightFound = false; //Es falso si el cliente ya tiene un asiento reservado en ese vuelo
	bool isInQueue = false; //Es falso si el cliente ,que sera eliminado,no pertenece
				// a la cola de cada vuelo
	
	if (!plist.empty()) {
		// Limpia
		cin.clear();
		cin.ignore(256,'\n');
		
		cout << "Indíquenos su número de pasaporte: ";
		getline(cin, passport); cout << endl;
		
		// Comprueba lo ingresado
		while(!checkNumber(passport)){
			cout << "Introduzca un número de pasaporte válido." << endl;
			getline(cin, passport); cout << endl; 
		}
		
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
			counter++;
		}
		
		cout << "\n¿Qué vuelo desea cancelar (ingrese el número de vuelo)?"; 
		getline(cin, num);
		counter = 1;
		
		// Comprueba lo ingresado
		while(!checkNumber(num)){
			cout << "Introduzca un número de vuelo válido." << endl;
			getline(cin, num); cout << endl; 
		}
		
		// Itera atraves de los vuelos del pasajero
		for (std::list<Person>::iterator i = plist.begin(); i != plist.end(); ++i){
			if (atoi(passport.c_str()) == i -> passportNo) {	
				
				// Comprueba lo ingresado y sale si el contado = 5
				do{										
					for (std::list<int>::iterator i2 = (i -> flights).begin(); i2 != (i -> flights).end(); ++i2){
						if (atoi(num.c_str()) == *i2) {
							flightFound = true;
							i2 = flights.erase(i2); // Elimina el vuelo de la iformacion del pasajero
							break;
						}
					}
					
					if (counter == 5){
						cout << "Se dio un número de vuelo incorrecto demasiadas veces.";
						return;
					}else if(!flightFound){
						cout << "¡Por favor verifique su número de vuelo!.";
						getline(cin, num); cout << endl;
						
						// Comprueba lo ingresado
						while(!checkNumber(num)){
						cout << "Introduzca un número de vuelo válido." << endl;
						getline(cin, num); cout << endl; 
						}
					}				
					counter++;
				}while(!flightFound);
				break;
			}
		}
		
		//Elimina al cliente de la colda de vuelos , si es que formaban parte de el
		for (std::list<Queue>::iterator i = qlist.begin(); i != qlist.end(); ++i){
			if( atoi(num.c_str()) == i -> getNo() ){
				if(!i -> isEmpty()){
					Node* p = new Node;			
					Node* previousNode;
					p = i -> getFront();
					
					while(p!=NULL){
						if (atoi(passport.c_str()) == p -> person.passportNo){
							isInQueue = true;
							
							//Ingresa si el cliente esta en la 1era posicion
							if (p == i -> getFront()){
								i -> setFront(p -> next);
								// Ingresa si la cola solo tiene un elemento
								if (i -> getFront() == i -> getRear()){
									i -> setRear(NULL);
								}						
							}else if(p == i -> getRear()){ // Ingresa si el cliente esta en la ultima posicion de la cola del vuelo
								previousNode -> next = NULL;								
							}else{ 
								previousNode -> next = p -> next;								
							}
							delete(p);
							break;						
						}
						previousNode = p;
						p = p -> next;
					}
				}
			}
		}
		
		//Ingresa si el pasajer NO es parte de la actual cola
		if (!isInQueue){
			Flight::resSeat(atoi(num.c_str()), -1); 		
		
			this -> bookFromQueue(atoi(num.c_str()));
		}
		cout << "\n¡Su reserva fue eliminada con éxito! \n" << endl;
	}else {
		cout << "¡No hay clientes registrados en este momento!" << endl;
	}
}

bool Person::displayPersonInfo(int passport){
	
	for (std::list<Person>::iterator i = plist.begin(); i != plist.end(); ++i){
		
		if(passport == i -> passportNo){
			
			cout << "\n\t\t\t\t INFORMACIÓN PERSONAL" << endl << endl;
			cout << left << setw(15) << "NOMBRE" << left << setw(15) << "APELLIDO" << left << setw(15) << "N° PASAPORTE" << left << setw(15) << "NACIONALIDAD" << left << setw(15) << "DIRECCION" << left << setw(15) << "TELÉFONO" << endl;
			
			cout << left << setw(15) << i -> name << left << setw(15) << i -> surname << left << setw(15) << i -> passportNo << left << setw(15) << i -> nationallity << left << setw(15) << i -> address << left << setw(15) << i -> tel << endl << endl;
			cout << "Su vuelo (s):";
			
			for (std::list<int>::iterator i2 = (i -> flights).begin(); i2 != (i -> flights).end(); ++i2){
				
				cout << *i2 << "  ";
			}
			cout << endl;
			return true;
		}
	}
	cout << "No se encontró el número de pasaporte. ¡Revisar otra vez!" << endl;
	return false;	
}

bool Person::uniquePass(int passport){
	for (std::list<Person>::iterator i = plist.begin(); i != plist.end(); ++i){
		if (passport == i -> getPassport()) {
			return false;
		}
	}
	return true;
}

