#include "Flight_def.h"
#include "Menu_def.h"
#include "Person_def.h"
#include "Queue_def.h"

bool checkTime(string time) { // check the validity of the time (must be xx:xx, where x = Natural number)
	
	// enter ONLY if string is NOT empty
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

bool checkNumber(string s){ // checks if the input string consists ONLY of numbers
	
	// enter if string is NOT empty
	if(!s.empty()){
		for (int i = 0; i < s.length(); i++){
			if ( ((s.at(i) >= 'a' && s.at(i) <= 'z') || (s.at(i) >= 'A' && s.at(i) <= 'Z') || (s.at(i) == ' ')) ){
				return false;
			}
		}
	
		// check if string is a postive number
		if ( atoi(s.c_str()) > 0 ){
			return true;
		}else{
			return false;
		}
	}else{
		return false;
	}
	
	
}

bool checkString(string s){ // checks if string consists only of letters
	
	if(!s.empty()){
		for (int i = 0; i < s.length(); i++){
			if ( !((s.at(i) >= 'a' && s.at(i) <= 'z') || (s.at(i) >= 'A' && s.at(i) <= 'Z')) ){
				return false;
			}
		}
		return true;
	}
	else{ //return false
		return false;
	}
	
	
}

/* --CHECKER FOR NON-DIRECT FLIGHTS-- */
bool checkTime2(Time tLeaving, Time tArriving){	// checks the validity of arrival and departure time
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
																IMPLEMENTATION	 
------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
*/
/* ----GLOBAL VARS---- */

list<Flight> flist; // store the flights of the system
list<Person> plist; // store the passengers 
list<Queue> qlist; // store the customers in the flights' waiting queues