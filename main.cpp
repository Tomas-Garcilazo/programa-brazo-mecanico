#include <SDL.h>

#include <cstdlib>
#include <iostream>
#include <math.h>

using namespace std;

#include "crear_codigo.h"
#include "clases.h"
#include "dibujar_formas.h"
#include "programa_grafico.h"

void activar_consola(){
	/*ESTAS 2 LINEAS SON LO QUE ACTIVA LA CONSOLA*/
	/**/fclose (stdout);					   /**/
	/**/freopen("CON","w",stdout);			   /**/
	/*********************************************/
}
int main ( int argc, char** argv ){
	activar_consola();


	/* ACORDATE QUE EL PROGRAMA GRAFICO ES UN LOOP, 
	OSEA QUE TODO LO QUE ESTA ABAJO DE ESTA FUNCION NO 
	VA A FUNCAR HASTA QUE CIERRES EL PROGRAMA*/
	iniciar_programa_grafico();

	// esto borralo si queres, solo era para mostrar que la consola funciona
	cout << "lalala: ";
	int numero = -1;
	cin >> numero;
	cout << "la" << endl;
	cin >> numero;
	cin >> numero;

	// el programa podes abrirlo cuando quieras, cuantas veces quieras
	// no probe si tiene bugs, pero el dibujo parece funcar
	iniciar_programa_grafico();
    return 0;
}
