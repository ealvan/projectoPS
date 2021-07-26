#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <list>	 //double linked list
#include <iostream>
#include <string> // for the atoi conversion
#include <sstream> // for the stringstream (used to convert into to string)
#include <iomanip> // for organizing output into columns
#include <vector>
using namespace std;

// forward declaration
class Person; 
class Flight;
class Queue;

/* ----CLASSES---- */

class Menu //class for managing the app's menu
{
	public:
		static void displayMenu(); // displays the menu
		static void select(int selection); // receives user's input and performs the corresponding function
		static void exit_prog(); // exits the app
};

struct Time // structure for managing the Arrival and Departing times
{
	int min; 
	int hour;
};

class Flight // class for managing the availabe functions of a flight
{				
	private:
	
		int flightNo, cost, seats, booked_seats;
		string from, to, plane_type;	
		Time t_leave, t_arrive;
		
	public:
		/* --ADD/REMOVE FLIGHTS--*/
		void addFlight(); //διαχειρίζεται την προσθήκη πτήσεων (επιλογή μενού Νο 1)
		static void deleteFlight(int num); //διαχειρίζεται την αφαίρεση πτήσεων (επιλογή μενού Νο 2)
		
		/* --DISPLAY FLIGHTS--*/
		static void displayFlightInfo(int num); //προβάλλει τις πληροφορίες μιας πτήσης (επιλογή μενού Νο 3)
		static void displaySchedule(); //προβάλλει τις πτήσεις που υπάρχουν καταχωρημένες στο σύστημα (επιλογή μενού Νο 4)
		
		/* --BOOK SEATS--*/
		static void resSeat(int num, int val); //αυξομειώνει τις κατοχυρωμένες θέσεις μιας πτήσεις
		
		/* --FLIGHT CHECKERS--*/
		static bool flightExists(int num); // check flight is booked	
		static bool checkForSeats(int num); // checks for already registerd flight in the system
		
		/* --GETTERS--*/
		int getFlightNo() { return this -> flightNo; }
		Time getLeavingTime() { return this -> t_leave; }
		Time getArrivingTime() { return this -> t_arrive; }
		string getDeparture() { return this -> from; }
		string getDestination() { return this -> to; }
};			
	
class Person //class for managing the functions of a passenger				
{
	private:
	
		int passportNo, tel;
		list<int> flights;
		string name, surname, nationallity, address;		
	
	public:
		/* --BOOK FLIGHT-- */
		void book(); // book flight for each customer (Menu Option Νο 6)
		void bookFromQueue(int num); // book flight for the oldest customer in 
					    // (call ONLY when a reservation is cancelled)
		void cancel(); //cancel a reservation (Menu Option Νο 7)
		
		/* --SHOW PASSENGER'S INFO-- */
		static bool displayPersonInfo(int passport);
		
		/* --CHECHKER FOR UNIQUE PASSPORT-- */
		static bool uniquePass(int passport);
		
		/* --GETTERS-- */
		int getPassport() { return this -> passportNo; }
		string getName() { return this -> name; }
		string getSurname() { return this -> surname; }
		
};	

struct Node //structure for managing each flight's queue
{
    Person person;
    Node* next;
};

class Queue // class that stores passengers on each flight's queue
{

    private:

	int queueNo;
        Node* rear;
        Node* front;	
	
	public:
		/* --CREATE NEW QUEUE-- */
        Queue(int queueId); // queueID is the same as the flight number for each flight
		
		/* --ADD/REMOVE ELEMENTS-- */
        void enqueue(Person p); // add a new passenger
        void dequeue(); // remove the passenger add last 
		
		/* --ΠΡΟΒΟΛΗ ΣΤΟΙΧΕΙΩΝ ΟΥΡΑΣ-- */
		static void display(int num); //εμφανίζει τους πελάτες, που βρίσκονται κατοχυρωμένοι 
									 //στην ουρά αναμονής της εκάστοτε πτήσης

		/* --ΕΠΙΣΤΡΟΦΗ ΑΡΧΑΙΟΤΕΡΟΥ ΧΡΗΣΤΗ-- */
		Person oldest(); //επιστρέφει το αντικέιμενο του αρχαιότερου πελάτη, μέσω της κλάσης Person
		
		/* --CHECK FOR EMPTY QUEUE-- */
		bool isEmpty(); // returns true if queue is empty
		
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
