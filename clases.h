#ifndef CLASES_H_INCLUDED
#define CLASES_H_INCLUDED

class Dibujo{
    private:
        int *lista_de_trazos; /// esto va a ser un vector que se va a modificar con malloc
        SDL_Surface *screen;
        Uint32 colores[2];

    public:
        void cargar_Dibujo(int *mapa);

        Dibujo(SDL_Surface *new_screen){
            screen = new_screen;
            // esto crea un de un pixel negro y uno amarillo
            // despues son copiados en las zonas de 10x10 que se quieran pintar
            colores[0] = SDL_MapRGB(screen->format, 0x00, 0x00, 0x00); // negro
            colores[1] = SDL_MapRGB(screen->format, 0xff, 0xff, 0x00); // amarillo
        }
        void putpixel(int, int, int);
};

// esta es la funcion que dibuja en la pantalla
void Dibujo::putpixel(int x, int y, int color_elegido = 1){
    x -= x%10;
    y -= y%10;
    if (x >= 640 || y >= 480 || x < 0 || y < 0){
        return;
    }

    // crea un rectangulo de 10x10 con una determinada cordenada
    SDL_Rect rectangulo = {x, y, 10, 10};
    // llena el rectangulo anterior con los pixeles del color elegido
    SDL_FillRect(screen, &rectangulo, colores[color_elegido]);
    /// acutalizar la pantalla en la zona recien pintada
    SDL_UpdateRect(screen, x, y, 10, 10);
}

void Dibujo::cargar_Dibujo(int *mapa){
int x=0;
int y=0;
    for (int i = 0; i < 49; i++){
        for (int j=0; j<65; j++){
            if (mapa[x] ==0){
                this->putpixel(10*x, y*10, 0);
            }
            else{
                this->putpixel(10*x, y*10);
            }
            x++;
        }
    }
}

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
        void guardar_mapa(){
            FILE *f;
            f = fopen("archivo_matriz.dat", "wb");
            fwrite(mapa, sizeof(int)*65*49, 1, f);
        }
        cargar(){
        FILE *p;
        p=fopen("archivo_matriz.dat","rb");
            fread(mapa, sizeof(int)*65*49, 1, p);
        fclose(p);
        }

        void mostrar_mapa();
        void marcar_mapa(int y, int x, int valor);
        void Poner_Mapa_0();
        int* get_mapa(){return (int *) mapa;}
        int get_valor(int y, int x){return mapa[y][x];
        }
};

void Lienzo::mostrar_mapa(){
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

void Lienzo::marcar_mapa(int y, int x, int valor){
    x = (int) x/10;
    y = (int) y/10;
    if (x >= width || y >= height || x < 0 || y < 0){
        return;
    }
    mapa[y][x] = valor;
}

void Lienzo::Poner_Mapa_0(){
    for (int i = 0; i < 49; i++){
        for (int j=0; j<65; j++){
            mapa[i][j] = 0;
        }
    }
}

#endif // CLASES_H_INCLUDED
