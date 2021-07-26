//Incluye las Librerias necesarias
#include "General_def.h"

class Menu //Clase para controlar el menu de la aplicacion
{
	public:
		static void displayMenu(); // Muestra el Menu
		static void select(int selection); // Recive las seleccion ingresada del usuario y realiza la funcion correspondiente
		static void exit_prog(); // Cierra la aplicacion
};
