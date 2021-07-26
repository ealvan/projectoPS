//Incluyendo las funciones
#include "Flight_def.h"
#include "Menu_def.h"
#include "Person_def.h"
#include "Queue_def.h"

bool checkTime(string time) { //Comprueba la validez del horario(debe ser xx:xx, donde x es un Numero Natual)
	
	//Ingresa SOLO si el string NO esta vacio
	if(!time.empty()){
		for (int i=0; i < time.length(); i++) {		
			if (i==2){
				if (time.at(i) != ':') {
				return false;
				}
				
			}else if ( !(time.at(i) >= '0' && time.at(i) <= '9') ) {
				return false;
			}				
		}
		return true;
	}else{ 
		return false;
	}
	
}

bool checkNumber(string s){ //Comprueba si el string ingresado consiste de SOLO numeros
	
	//Ingresa si el string es NO vacio
	if(!s.empty()){
		for (int i = 0; i < s.length(); i++){
			if ( ((s.at(i) >= 'a' && s.at(i) <= 'z') || (s.at(i) >= 'A' && s.at(i) <= 'Z') || (s.at(i) == ' ')) ){
				return false;
			}
		}
	
		//Comprueba que el string es un numero positivo
		if ( atoi(s.c_str()) > 0 ){
			return true;
		}else{
			return false;
		}
	}else{
		return false;
	}
	
	
}

bool checkString(string s){ //Comprueba si el string consiste de solo letras
	
	if(!s.empty()){
		for (int i = 0; i < s.length(); i++){
			if ( !((s.at(i) >= 'a' && s.at(i) <= 'z') || (s.at(i) >= 'A' && s.at(i) <= 'Z')) ){
				return false;
			}
		}
		return true;
	}
	else{
		return false;
	}
	
	
}

/* --VERIFICADOR DE VUELOS NO DIRECTOS-- */
bool checkTime2(Time tLeaving, Time tArriving){	//Comprueba la validez de la hora de llegada y de salida
	if(tLeaving.hour > tArriving.hour){
		return true;
	}else if(tLeaving.hour == tArriving.hour){
		if(tLeaving.min > tArriving.min){
			return true;
		}
	}
	return false;	
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
