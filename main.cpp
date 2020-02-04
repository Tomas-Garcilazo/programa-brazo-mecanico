#include <SDL.h>

#include <cstdlib>
#include <iostream>
#include <math.h>

using namespace std;

#include "crear_codigo.h"
#include "clases.h"
#include "dibujar_formas.h"

int main ( int argc, char** argv ){
	/// tamaño constante de la pantalla
    int const SCREEN_W = 640, SCREEN_H = 480;

    Dibujo dibujo_obj;
    Lienzo lienzo_obj;

    int estado_clic = 0;

    int const CUADRADO      = 0;
    int const LIBRE         = 1;
    int const LINEA         = 2;
    int const BORRAR_LIBRE  = 3;
    int const ROMBO         = 5;
    int const CIRCULO       = 4;

    int modoDeDibujo = LIBRE;
    /// ------ NOTAS ------ ///
    /// siempre que leas "mapa" se refiere a mapa de pixeles
    /// lo mas importante es la matriz "int mapa" de abajo
    ///el archivo se crea cuando el programa SE CIERRA
    lienzo_obj.Poner_Mapa_0();

    int x, y;
    bool buttonState  = false;
    atexit(SDL_Quit);

    /// cargar imagen
    SDL_Surface* bmp = SDL_LoadBMP("imagenes/botones.bmp");

    /// create a new window
    SDL_Surface* screen = SDL_SetVideoMode(SCREEN_W + bmp->w, SCREEN_H, 16, SDL_HWSURFACE|SDL_DOUBLEBUF);

    /// centre the bitmap on screen
    SDL_Rect dstrect;

    dstrect.x = screen->w - bmp->w;
    dstrect.y = 0;
    SDL_BlitSurface(bmp, 0, screen, &dstrect);

    /// actualizar pantalla
    SDL_Flip(screen);

    /// program main loop
    bool done = false;
    while (!done){
        /// message processing loop
        SDL_Event event;
        while (SDL_PollEvent(&event)){
           switch (event.type){
                case SDL_QUIT:
                    done = true;
                    break;

                case SDL_MOUSEBUTTONDOWN:
                    buttonState = true;
                    estado_clic=1;
                    break;

                case SDL_MOUSEBUTTONUP:
                    buttonState = false;
                    estado_clic=2;
                    break;
                case SDL_KEYDOWN:
                    switch( event.key.keysym.sym ){
                    case SDLK_c:
                        modoDeDibujo=CUADRADO;
                        break;
                    case SDLK_l:
                        modoDeDibujo=LIBRE;
                        break;
                    case SDLK_d:
                        modoDeDibujo=LINEA;
                        break;
                    case SDLK_b:
                        modoDeDibujo=BORRAR_LIBRE;
                        break;
                    case SDLK_a:
                        modoDeDibujo=CIRCULO;
                        break;
                    case SDLK_r:
                        modoDeDibujo=ROMBO;
                        break;
                    default:
                        break;
                    }
                    break;

                }

                        switch(modoDeDibujo){
                            case LIBRE:
                                if(buttonState){
                                    SDL_GetMouseState(&x, &y);
                                    if (x > -1 && x <SCREEN_W && y > -1 && y <SCREEN_H){
                                        dibujo_obj.putpixel(screen, x, y);
                                        lienzo_obj.marcar_mapa(y, x, 1);
                                    }
                                }
                                break;

                            case BORRAR_LIBRE:
                                if(buttonState){
                                    SDL_GetMouseState(&x, &y);
                                    if (x > -1 && x <SCREEN_W && y > -1 && y <SCREEN_H){
                                        /// ESTO TIENE QUE SER CAMBIADO PARA USAR LA FUNCION PUTPIXEL
                                        /// PERO PERIMERO HAY QUE PONERLE UN SWITCH CON EL COLOR A LA FUNCION
                                        Uint32 negro;
                                        negro = SDL_MapRGB(screen->format, 0x00, 0x00, 0x00);
                                        SDL_Rect rectangulo = {x-(x%10), y-(y%10), 10, 10};
                                        SDL_FillRect(screen, &rectangulo, negro);
                                        SDL_UpdateRect(screen, x-(x%10), y-(y%10), 10, 10); /// acutalizar la pantalla (si no se actualiza no se ven los cambios)
                                        lienzo_obj.marcar_mapa(y, x, 0);
                                    }
                                }
                                break;

                            case CUADRADO:
                                if(estado_clic==1){
                                SDL_GetMouseState(&x, &y);
                                }
                                else if (estado_clic == 2){
                                    int x_F;
                                    int y_F;
                                    SDL_GetMouseState(&x_F, &y_F);
                                    dibujar_cuadrado(x, y, x_F, y_F, dibujo_obj, screen, &lienzo_obj);
                                    estado_clic = 0;
                                }
                                break;

                            case LINEA:
                                int x_F;
                                int y_F;
                                if(estado_clic==1)
                                {
                                    SDL_GetMouseState(&x,&y);
                                }
                                else if(estado_clic==2)
                                {
                                    SDL_GetMouseState(&x_F, &y_F);
                                    dibujar_linea(x,y, x_F, y_F, dibujo_obj, screen, &lienzo_obj);
                                    estado_clic = 0;

                                }
                                break;

                            case CIRCULO:
                                if(estado_clic==1){
                                    SDL_GetMouseState(&x, &y);
                                }
                                else if (estado_clic == 2){
                                    int x_F;
                                    int y_F;
                                    SDL_GetMouseState(&x_F, &y_F);
                                    dibujar_circulo(x, y, x_F, y_F, dibujo_obj, screen, &lienzo_obj);
                                    estado_clic = 0;
                                }
                                break;

                            case ROMBO:
                                if(estado_clic==1){
                                SDL_GetMouseState(&x, &y);
                                }
                                else if (estado_clic == 2){
                                    int x_F;
                                    int y_F;
                                    SDL_GetMouseState(&x_F, &y_F);
                                    dibujar_rombo(x, y, x_F, y_F, dibujo_obj, screen, &lienzo_obj);
                                    estado_clic = 0;
                                }
                                break;
                            }


                        }
                        estado_clic = 0;

    }

    lienzo_obj.mostrar_mapa();
    FILE *f;
    f = fopen("archivo_matriz.dat", "wb");
    fwrite(lienzo_obj.get_mapa(), sizeof(int)*65*49, 1, f);

    /// escribe las instrucciones que se le pasan al brazo
    escribir_codigo_final();

    return 0;
}
