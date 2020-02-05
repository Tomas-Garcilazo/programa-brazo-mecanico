#ifndef CLASES_H_INCLUDED
#define CLASES_H_INCLUDED

class Lienzo{
    private:
        int mapa[49][65];
        int width;
        int height;        
    public:
        Lienzo(int new_width, int new_height){
            width = new_width;
            height = new_height;
        }
        void guardar_mapa();
        void mostrar_mapa();
        void marcar_mapa(int y, int x, int valor)
        {   
            x = (int) x/10;
            y = (int) y/10;

            if (x >= width || y >= height || x < 0 || y < 0){
                return;
            }

            mapa[y][x] = valor;
        }
        void Poner_Mapa_0();
        int* get_mapa()
        {
            return (int *) mapa;
        }
        int get_valor(int y, int x)
        {
            return mapa[y][x];
        }
};

class Dibujo{
    private:
        int *lista_de_trazos; /// esto va a ser un vector que se va a modificar con malloc
        Lienzo *obj_lienzo;
        SDL_Surface *screen;
    public:
        void dibujar_nuevo();
        void dibujar();
        void borrar();
        void putpixel(int, int);
        void set_screen(SDL_Surface *new_screen){
            screen = new_screen;
        }
};

// esta es la funcion que dibuja en la pantalla
void Dibujo::putpixel(int x, int y)
{   
    x -= x%10;
    y -= y%10;
    if (x >= 640 || y >= 480 || x < 0 || y < 0){
        return;
    }
    Uint32 px_amarillo, px_negro;

    // esto crea un de un pixel amarillo
    px_amarillo = SDL_MapRGB(screen->format, 0xff, 0xff, 0x00);

    // ese pixel despues es copiado en las zonas que se quieran pintar
    px_negro = SDL_MapRGB(screen->format, 0x00, 0x00, 0x00);

    // crea un rectangulo de 10x10 con una determinada cordenada
    SDL_Rect rectangulo = {x, y, 10, 10};

    // llena el rectangulo anterior con el pixel dado
    SDL_FillRect(screen, &rectangulo, px_amarillo);

    /// acutalizar la pantalla en la zona recien pintada
    SDL_UpdateRect(screen, x, y, 10, 10);
}

void Lienzo::mostrar_mapa()
{
    for (int i = 0; i < 49; i++){
        for (int j=0; j<65; j++){
            if (mapa[i][j] ==0)
                cout <<" ";
            
            else{
                cout << "#";
            }
        }
        cout << endl;
    }
}

void Lienzo::Poner_Mapa_0()
{
    for (int i = 0; i < 49; i++){
        for (int j=0; j<65; j++){
            mapa[i][j] = 0;
        }
    }
}
#endif // CLASES_H_INCLUDED
