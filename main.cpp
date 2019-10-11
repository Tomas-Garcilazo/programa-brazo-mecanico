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



void mostrar_mapa(char mapa[49][65]){
for (int i = 0; i < 49; i++){
    cout << mapa[i] << endl;}
}

int main ( int argc, char** argv )
{
    const int TAM_X = 65, TAM_Y = 49;
    /// ------ NOTAS ------ ///
    /// siempre que leas "mapa" se refiere a mapa de pixeles
    /// lo mas importante es la matriz "char mapa" de abajo
    ///el archivo se crea cuando el programa SE CIERRA
    char mapa[TAM_Y][TAM_X];

    for (int j = 0; j<49; j++){
        for (int i = 0; i < 64; i++){
            mapa[j][i] = '#';
        }
        mapa[j][64] = '\0';
    }

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
                if (x > -1 && x <640 && y > -1 && y <480)
                    x = (int) x/10;
                    y = (int) y/10;
                    mapa[y][x] = ' ';
            	break;
            }
        }

    }

    mostrar_mapa(mapa);
    return 0;
}
