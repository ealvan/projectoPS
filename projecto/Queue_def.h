//Incluyendo las librerias necesarias
#include "General_def.h"



struct Node //Estructura para controlar cada cola de vuelos
{
    Person person;
    Node* next;
};

class Queue //Clase se que alamcena a los pasajeros en la cola de cada vuelo
{

    private:

	int queueNo;
        Node* rear;
        Node* front;	
	
	public:
		/* --CREA UNA NUEVA FILA-- */
        Queue(int queueId); // queueID es el mismo que el numero de vuelo para cada vuelo
		
		/* --ANADIR O ELIMINAR PASAJEROS-- */
        void enqueue(Person p); //Agrega a un pasajero a una cola
        void dequeue(); // Elimina al ultimo pasajero agregado
		
		/* --Visualizacion de la cola y pasajeros-- */
		static void display(int num); //muestra a un cliente registrado 
						//en la cola de espera de cada vuelo

		/* --Retorna el Ultimo Pasajero-- */
		Person oldest(); //Retorna el Objeto Cliente Mas Antiguo, a traves de la clase Person
		
		/* --REVISAR SI FILA ESTA VACIA-- */
		bool isEmpty(); //Retorna true si la fila esta vacia
		
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
