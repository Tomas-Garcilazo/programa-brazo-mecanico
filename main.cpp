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


class Lienzo{
    private:
        int mapa[49][65];
    public:
        void guardar_mapa();
        void mostrar_mapa();
        void marcar_mapa(int y, int x){
            mapa[y][x] = 1;
        }
        void Poner_Mapa_0();
        int* get_mapa(){
            return (int *) mapa;
        }
};

class Dibujo{
    private:
        int *lista_de_trazos; /// esto va a ser un vector que se va a modificar con malloc
        Lienzo *obj_lienzo;
    public:
        void dibujar_nuevo();
        void dibujar();
        void borrar();
        void putpixel(SDL_Surface*, int,int);
};

class Plantilla{
    private:
        int mapa[10][10];
    public:
        void cargar_plantilla();
        void poner_en_lienzo(Lienzo);
};

class Boton{
    private:
        char tecla;
    public:
        cargarBoton();
};

class Ventana{
    private:

    public:


};

// esta es la funcion que dibuja en la pantalla, por ahora ignorala
void Dibujo::putpixel(SDL_Surface *surface, int x, int y){
	Uint32 pixel;
	pixel = SDL_MapRGB(surface->format, 0xff, 0xff, 0x00); // esto crea una "plantilla" de un pixel amarillo

    bool clic_soltado = false;

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

void Lienzo::mostrar_mapa(){
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

void Lienzo::Poner_Mapa_0(){

    for (int i = 0; i < 49; i++){

        for (int j=0;j<65;j++){

            mapa[i][j] = 0;
        }
	}
}
#include "dibujar_formas.h"
int main ( int argc, char** argv )
{
    Dibujo dibujo_obj;
    Lienzo lienzo_obj;
    int estado_clic = 0;

    int const cuadrado = 0;
    int const linea = 2;
    int const libre = 1;
    int modoDeDibujo = libre;
    int contador=0;
    const int TAM_X = 65, TAM_Y = 49;
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
    SDL_Surface* screen = SDL_SetVideoMode(640+bmp->w, 480, 16, SDL_HWSURFACE|SDL_DOUBLEBUF);

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
                    default:
                        break;
                    }
                    break;

                }

                        switch(modoDeDibujo){
                            case libre:
                                if(buttonState){

                                SDL_GetMouseState(&x, &y);
                                if (x > -1 && x <640 && y > -1 && y <480){

                                    dibujo_obj.putpixel(screen, x-(x%10), y-(y%10)); /// los pixeles en la pantalla
                                    SDL_UpdateRect(screen, x-(x%10), y-(y%10), 10, 10); /// acutalizar la pantalla (si no se actualiza no se ven los cambios)
                                    x = (int) x/10;
                                    y = (int) y/10;
                                    lienzo_obj.marcar_mapa(y, x);
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
                                    dibujar_cuadrado(x, y, x_F, y_F, dibujo_obj, screen);
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
                                    dibujar_linea(x,y, x_F, y_F, dibujo_obj, screen);

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
