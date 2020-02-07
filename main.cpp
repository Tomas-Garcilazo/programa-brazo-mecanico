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
    int numero=1;
	activar_consola();


	/* ACORDATE QUE EL PROGRAMA GRAFICO ES UN LOOP,
	OSEA QUE TODO LO QUE ESTA ABAJO DE ESTA FUNCION NO
	VA A FUNCAR HASTA QUE CIERRES EL PROGRAMA*/
	do{
	iniciar_programa_grafico(false);
	activar_consola();
    printf("Ingrese 0 para cerrar o Otro numero para continuar : ") ;
    ///SDL_Surface *screen = SDL_SetVideoMode(200,300 , 16, SDL_HWSURFACE|SDL_DOUBLEBUF);
	 numero = -1;
	cin >> numero;
	}while(numero!=0);

	// esto borralo si queres, solo era para mostrar que la consola funciona


	// el programa podes abrirlo cuando quieras, cuantas veces quieras
	// no probe si tiene bugs, pero el dibujo parece funcar

    return 0;
}
