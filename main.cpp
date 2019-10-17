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


// esta es la funcion que dibuja en la pantalla, por ahora ignorala
void putpixel(SDL_Surface *surface, int x, int y){
	Uint32 pixel;
	pixel = SDL_MapRGB(surface->format, 0xff, 0xff, 0x00); // esto crea una "plantilla" de un pixel amarillo

    int bpp = surface->format->BytesPerPixel;
    Uint8 *p;

    for (int i = 0; i<10; i++){
    	for (int h = 0; h<10; h++){
 	   		p = (Uint8 *)surface->pixels + (y+i) * surface->pitch + (x+h) * bpp;


    switch(bpp) {
    case 1:
        *p = pixel;
        break;

    case 2:
        *(Uint16 *)p = pixel;
        break;

    case 3:
        if(SDL_BYTEORDER == SDL_BIG_ENDIAN) {
            p[0] = (pixel >> 16) & 0xff;
            p[1] = (pixel >> 8) & 0xff;
            p[2] = pixel & 0xff;
        } else {
            p[0] = pixel & 0xff;
            p[1] = (pixel >> 8) & 0xff;
            p[2] = (pixel >> 16) & 0xff;
        }
        break;

    case 4:
        *(Uint32 *)p = pixel;
        break;
    }
    	}
	}
}

void mostrar_mapa(int mapa[49][65]){
	for (int i = 0; i < 49; i++){
        for (int j=0;j<65;j++){
            if (mapa[i][j] ==0)
            cout <<" ";
            else{
                cout << "#";
            }
        }
         cout << endl;
	}
}

int main ( int argc, char** argv )
{
    const int TAM_X = 65, TAM_Y = 49;
    /// ------ NOTAS ------ ///
    /// siempre que leas "mapa" se refiere a mapa de pixeles
    /// lo mas importante es la matriz "char mapa" de abajo
    ///el archivo se crea cuando el programa SE CIERRA
    int mapa[TAM_Y][TAM_X]={0};

    int x, y;
    bool buttonState  = false;
    atexit(SDL_Quit);

    // create a new window
    SDL_Surface* screen = SDL_SetVideoMode(640, 480, 16, SDL_HWSURFACE|SDL_DOUBLEBUF);

    // program main loop
    bool done = false;
    while (!done)
    {
        // message processing loop
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
                // exit if the window is closed
            case SDL_QUIT:
                done = true;
                break;

            case SDL_MOUSEBUTTONDOWN:
                buttonState = true;
                break;
            case SDL_MOUSEBUTTONUP:
                buttonState = false;

            }
            if(buttonState){
                SDL_GetMouseState(&x, &y);
                if (x > -1 && x <640 && y > -1 && y <480){

					putpixel(screen, x-(x%10), y-(y%10)); /// los pixeles en la pantalla
				    SDL_UpdateRect(screen, x-(x%10), y-(y%10), 10, 10); // acutalizar la pantalla (si no se actualiza no se ven los cambios)
                    x = (int) x/10;
                    y = (int) y/10;
                    mapa[y][x] = 1;
                }
            }
            }
        }



    mostrar_mapa(mapa);
    FILE *f;
    f = fopen("archivo_matriz.dat", "wb");
    fwrite(mapa, sizeof(int)*65*49, 1, f);

    return 0;
}
