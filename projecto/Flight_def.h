#include "General_def.h"

struct Time //Estructura para controlar los horariosd e LLegada y de Salida
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
		/* --ANADIR/REMOVER VUELOS--*/
		void addFlight(); //Controla el agregar un Vuelo al sistema (Opcion del Menu Νο 1)
		static void deleteFlight(int num); //Controla la eliminacion de Un vuelo (Opcion del Menu Νο 2)
		
		/* --MOSTRAR VUELOS--*/
		static void displayFlightInfo(int num); //Muestra la informacion de un Vuelo (Opcion del Menu Νο 3)
		static void displaySchedule(); //Muestra los vuelos registrados en el sistemaa (Opcion del Menu Νο 4)
		
		/* --RESERVAR ASIENTOS--*/
		static void resSeat(int num, int val); //Modifica los asientos reservados de un vueloo
		
		/* --REVISAR VUELOS--*/
		static bool flightExists(int num); //Comprobar si el vuelo esta Reservado	
		static bool checkForSeats(int num); //Comprueba por vuelos registros en el sistema
		
		/* --GETTERS--*/
		int getFlightNo() { return this -> flightNo; }
		Time getLeavingTime() { return this -> t_leave; }
		Time getArrivingTime() { return this -> t_arrive; }
		string getDeparture() { return this -> from; }
		string getDestination() { return this -> to; }
};
