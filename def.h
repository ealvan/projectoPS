//Librerias necesarias
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <list>	 //Doble linked list
#include <iostream>
#include <string> // Para la conversion de atoi
#include <sstream> // Para el stringstream (usado para convertirlo en string)
#include <iomanip> // Para organizar la salida en columnas
#include <vector>
using namespace std;

// Declaraciones de la parte delantera
class Person; 
class Flight;
class Queue;

/* ----CLASES---- */

class Menu //Clase para controlar el menu de la aplicacion
{
	public:
		static void displayMenu(); // Muestra el menu
		static void select(int selection); //Recive la entrada del usuario y ejecuta la funcion correspondiente
		static void exit_prog(); // Cierra la aplicacion
};

struct Time //Estructura para controlar los horrarios de llegada y de salida
{
	int min; 
	int hour;
};

class Flight //Clase para controlar las funciones disponibles de un vuelo
{				
	private:
	
		int flightNo, cost, seats, booked_seats;
		string from, to, plane_type;	
		Time t_leave, t_arrive;
		
	public:
		/* --ANADE/ELIMINA VUELOS--*/
		void addFlight(); //Gestiona la adicion de vuelos (Opcion del Menu Νο 1)
		static void deleteFlight(int num); //Gestiona la eliminacion de vuelos (Opcion del menu Νο 2)
		
		/* --MUESTRA LOS VUELOS--*/
		static void displayFlightInfo(int num); //Muestra la informacion ded un vuelo (Opcion del menu Νο 3)
		static void displaySchedule(); //Muestra los vuelos registrados en el sistema (Opcion del menu Νο 4)
		
		/* --RESERVAR ASIENTOS--*/
		static void resSeat(int num, int val); //Flucuta los asientos reservados de un vuelo
		
		/* --COMPROBAR VUELOS--*/
		static bool flightExists(int num); // Comprueba si el vuelo esta reservado
		static bool checkForSeats(int num); // Comprueba por vuelos que ya esten registrados en el sistema
		
		/* --GETTERS--*/
		int getFlightNo() { return this -> flightNo; }
		Time getLeavingTime() { return this -> t_leave; }
		Time getArrivingTime() { return this -> t_arrive; }
		string getDeparture() { return this -> from; }
		string getDestination() { return this -> to; }
};			
	
class Person //Clase para controlar las acciones de un pasajero				
{
	private:
	
		int passportNo, tel;
		list<int> flights;
		string name, surname, nationallity, address;		
	
	public:
		/* --RESERVAR VUELOS-- */
		void book(); // Reserva un vuelo para cada cliente (Opcion del Menu Νο 6)
		void bookFromQueue(int num); // Reserva un vuelo para el cliente mas antiguo 
					    // (llamado SOLO cuando una reservacion es cancelada)
		void cancel(); //Cancela una reservacion (Opcion del Menu Νο 7)
		
		/* --MUESTRA LA INFORMACION DE UN PASAJERO-- */
		static bool displayPersonInfo(int passport);
		
		/* --COMPRUEBA SI EL PASAPORTE ES UNICO-- */
		static bool uniquePass(int passport);
		
		/* --GETTERS-- */
		int getPassport() { return this -> passportNo; }
		string getName() { return this -> name; }
		string getSurname() { return this -> surname; }
		
};	

struct Node //Estructura para manejar cada cola de cada vuelo
{
    Person person;
    Node* next;
};

class Queue //Clase que almacena los pasajeros en cada cola de cada vuelo
{

    private:

	int queueNo;
        Node* rear;
        Node* front;	
	
	public:
		/* --CREA UNA NUEVA COLA-- */
        Queue(int queueId); // queueID es la misma que el numero de vuelo de cada vuelo
		
		/* --ANADE ELIMINA ELEMENTOS-- */
        void enqueue(Person p); // Anade un nuevo pasajero
        void dequeue(); // Elimina el pasajero ultimo en anadir
		
		/* --VISUALIZACION DE DATOS-- */
		static void display(int num); //Muestra a los clientes registrados
						//en la cola de espera de cada vuelo

		/* --DEVOLUCION DEL USUARIO MAS ANTIGUO-- */
		Person oldest(); //Devuele el objeto del usuario mas antiguo,a traves de la clase Person
		
		/* --COMPRUEBA SI LA FILA ESTA VACIA-- */
		bool isEmpty(); // Retorna true si la fila esta vacia
		
		/* --GETTERS-- */
		int getNo() { return this -> queueNo; }	
		Node* getFront() { return this -> front; }
		Node* getRear() { return this -> rear; }
		
		/* --SETTERS-- */
		void setFront(Node* f) { 
			if (f == 0){
				this -> front = NULL;
			}else{
				this -> front = f; 
			}
		}
		void setRear(Node* r) {
			this -> rear = r; 
		}
};
