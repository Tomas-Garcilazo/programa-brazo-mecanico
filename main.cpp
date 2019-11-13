#ifdef __cplusplus
    #include <cstdlib>
#else
    #include <stdlib.h>
#endif
#ifdef __APPLE__
#include <SDL/SDL.h>
#else
#include <SDL.h>
#endif

#include <iostream>

using namespace std;

#include "clases.h"

#include "dibujar_formas.h"



int main ( int argc, char** argv )
{
    int const screen_w = 640, screen_h = 480;
    Dibujo dibujo_obj;
    Lienzo lienzo_obj;
    int estado_clic = 0;

    int const cuadrado = 0;
    int const circulo = 4;
    int const libre = 1;
    int const linea = 2;
    int const borrar_libre = 3;
    int modoDeDibujo = libre;
    int contador=0;
    /// ------ NOTAS ------ ///
    /// siempre que leas "mapa" se refiere a mapa de pixeles
    /// lo mas importante es la matriz "char mapa" de abajo
    ///el archivo se crea cuando el programa SE CIERRA
    lienzo_obj.Poner_Mapa_0();


    int x, y;
    bool buttonState  = false;
    atexit(SDL_Quit);

    /// cargar imagen
    SDL_Surface* bmp = SDL_LoadBMP("imagenes/botones.bmp");

    /// create a new window
    SDL_Surface* screen = SDL_SetVideoMode(screen_w + bmp->w, screen_h, 16, SDL_HWSURFACE|SDL_DOUBLEBUF);

    /// centre the bitmap on screen
    SDL_Rect dstrect;

    dstrect.x = screen->w - bmp->w;
    dstrect.y = 0;
    SDL_BlitSurface(bmp, 0, screen, &dstrect);

    /// actualizar pantalla
    SDL_Flip(screen);



    /// program main loop
    bool done = false;
    while (!done)
    {

        /// message processing loop
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {

           switch (event.type)
                {
                    /// exit if the window is closed
                case SDL_QUIT:
                    done = true;
                    break;

                case SDL_MOUSEBUTTONDOWN:
                    buttonState = true;
                    estado_clic=1;
                    contador++;

                    break;
                case SDL_MOUSEBUTTONUP:
                    buttonState = false;
                    estado_clic=2;
                    break;
                case SDL_KEYDOWN:
                    switch( event.key.keysym.sym ){
                    case SDLK_c:
                        modoDeDibujo=cuadrado;
                        contador=0;
                        break;
                    case SDLK_l:
                        modoDeDibujo=libre;
                        break;
                    case SDLK_d:
                        modoDeDibujo=linea;
                        break;
                    case SDLK_b:
                        modoDeDibujo=borrar_libre;
                        break;
                    case SDLK_a:
                        modoDeDibujo=circulo;
                        break;
                    default:
                        break;
                    }
                    break;

                }

                        switch(modoDeDibujo){
                            case libre:
                                if(buttonState){
                                    SDL_GetMouseState(&x, &y);
                                    if (x > -1 && x <screen_w && y > -1 && y <screen_h){
                                        dibujo_obj.putpixel(screen, x-(x%10), y-(y%10)); /// los pixeles en la pantalla
                                        SDL_UpdateRect(screen, x-(x%10), y-(y%10), 10, 10); /// acutalizar la pantalla (si no se actualiza no se ven los cambios)
                                        x = (int) x/10;
                                        y = (int) y/10;
                                        lienzo_obj.marcar_mapa(y, x, 1);
                                    }
                                }
                                break;

                            case borrar_libre:
                                if(buttonState){
                                    SDL_GetMouseState(&x, &y);
                                    if (x > -1 && x <screen_w && y > -1 && y <screen_h){
                                        Uint32 negro;
                                        negro = SDL_MapRGB(screen->format, 0x00, 0x00, 0x00);

                                        SDL_Rect rectangulo = {x-(x%10), y-(y%10), 10, 10};
                                        SDL_FillRect(screen, &rectangulo, negro);
                                        SDL_UpdateRect(screen, x-(x%10), y-(y%10), 10, 10); /// acutalizar la pantalla (si no se actualiza no se ven los cambios)
                                        x = (int) x/10;
                                        y = (int) y/10;
                                        lienzo_obj.marcar_mapa(y, x, 0);
                                    }
                                }
                                break;

                            case cuadrado:
                                if(estado_clic==1){
                                SDL_GetMouseState(&x, &y);
                                }
                                if (estado_clic == 2){
                                    int x_F;
                                    int y_F;
                                    SDL_GetMouseState(&x_F, &y_F);
                                    dibujar_cuadrado(x, y, x_F, y_F, dibujo_obj, screen, &lienzo_obj);
                                }
                                break;

                            case linea:
                                int x_F;
                                int y_F;
                                if(estado_clic==1)
                                {
                                    SDL_GetMouseState(&x,&y);
                                }
                                if(estado_clic==2)
                                {
                                    SDL_GetMouseState(&x_F, &y_F);
                                    dibujar_linea(x,y, x_F, y_F, dibujo_obj, screen, &lienzo_obj);

                                }
                                break;

                            case circulo:
                                if(estado_clic==1){
                                    SDL_GetMouseState(&x, &y);
                                }
                                if (estado_clic == 2){
                                    int x_F;
                                    int y_F;
                                    SDL_GetMouseState(&x_F, &y_F);
                                    dibujar_circulo(x, y, x_F, y_F, dibujo_obj, screen, &lienzo_obj);
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

    return 0;
}
