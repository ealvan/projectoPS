//Incluyendo las funciones
#include "Flight_def.h"
#include "Menu_def.h"
#include "Person_def.h"
#include "Queue_def.h"

bool checkTime(string time) { //Comprueba la validez del horario(debe ser xx:xx, donde x es un Numero Natual)
	
	//Ingresa SOLO si el string NO esta vacio
	if(!time.empty()){
		//Recorre el time o tiempo (string)
		for (int i=0; i < time.length(); i++) {
			//Cuando llegue a la 3era letra		
			if (i==2){
				//Comprueba que tiene que ser ":"
				if (time.at(i) != ':') {
					//En caso no sea,retona falso
					return false;
				}
			//Cuando no sea la 3era letra
			//Comprueba que sea mayor a 0 y menor a 9 (Un numero)	
			}else if ( !(time.at(i) >= '0' && time.at(i) <= '9') ) {
				//Si no lo es retorna falso
				return false;
			}				
		}
		//Cuando sea un horario
		return true;
	//Cuando el string esta vacio	
	}else{ 
		return false;
	}
	
}

bool checkNumber(string s){ //Comprueba si el string ingresado consiste de SOLO numeros
	
	//Ingresa si el string es NO vacio
	if(!s.empty()){
		//Recorre la cadena ingresada
		for (int i = 0; i < s.length(); i++){
			//Comprueba que no este en el intervalo de la a-z y del intervalo de la A-Z
			if ( ((s.at(i) >= 'a' && s.at(i) <= 'z') || (s.at(i) >= 'A' && s.at(i) <= 'Z') || (s.at(i) == ' ')) ){
				//En caso contrario retorna falso
				return false;
			}
		}
	
		//Comprueba que el string es un numero positivo
		if ( atoi(s.c_str()) > 0 ){
			return true;
		//Si no lo es , retorna falso
		}else{
			return false;
		}
	//En caso el string sea vacio
	}else{
		return false;
	}
	
	
}

bool checkString(string s){ //Comprueba si el string consiste de solo letras
	//Ingresa si el string es NO vacio
	if(!s.empty()){
		//Recorre el string
		for (int i = 0; i < s.length(); i++){
			//Comprueba que  este en el intervalo de la a-z y del intervalo de la A-Z
			if ( !((s.at(i) >= 'a' && s.at(i) <= 'z') || (s.at(i) >= 'A' && s.at(i) <= 'Z')) ){
				//En caso contrario retorna falso
				return false;
			}
		}
		//Verdadero cuando sea solo letras
		return true;
	}
	//Cuando este vacio
	else{
		return false;
	}
	
	
}

/* --VERIFICADOR DE VUELOS NO DIRECTOS-- */
bool checkTime2(Time tLeaving, Time tArriving){	//Comprueba la validez de la hora de llegada y de salida
	
	//Verifica que la hora de salida sea mayor a la de llegada
	if(tLeaving.hour > tArriving.hour){
		//Retorna verdadero
		return true;
	//En caso sea la mismaa hora
	}else if(tLeaving.hour == tArriving.hour){
		//Compara los minutos
		if(tLeaving.min > tArriving.min){
			//Retorna verdadero
			return true;
		}
	}

	//Cuando no cumple
	return false;	
}
void writetime(double time, string function){
	fstream f;
	f.open("time_functions.txt", ios::ios_base::app);
	if(f.good()){
		string line = function+"=" +to_string(time);
		f << line+"\n";
	}
}
/* 
------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ 
																IMPLEMENTACION	 
------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
*/
/* ----VARIABLES GLOBALES---- */

list<Flight> flist; // Almacena los vuelos del sistema
list<Person> plist; // Almacena los Pasajeros
list<Queue> qlist; // Almacena a los clientes en la cola de espera de los vuelos
