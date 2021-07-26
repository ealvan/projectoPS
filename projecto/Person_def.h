//Inclutenfo cabeceras generales
#include "General_def.h"

class Person //Clase para controlar las funciones del Pasajero				
{
	private:
	
		int passportNo, tel;
		list<int> flights;
		string name, surname, nationallity, address;		
	
	public:
		/* --LIBRO DE VUELOS-- */
		void book(); //Libro de Vuelos para cada cliente (Opcion del Menu Νο 6)
		void bookFromQueue(int num); //Libro de Vuelos para el cliente mas antiguo 
					    //(Llamado SOLO cuando una reservacion es cancelada)
		void cancel(); //Cancela una Reservacion (Opcion del Menu Νο 7)
		
		/* --MUESTRA INFORMACION DEL PASAJERO-- */
		static bool displayPersonInfo(int passport);
		
		/* --VERIFICADOR DE PASAPORTE UNICO-- */
		static bool uniquePass(int passport);
		
		/* --GETTERS-- */
		int getPassport() { return this -> passportNo; }
		string getName() { return this -> name; }
		string getSurname() { return this -> surname; }
		
};
