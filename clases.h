#ifndef CLASES_H_INCLUDED
#define CLASES_H_INCLUDED

class Lienzo
{
private:
    int mapa[49][65];
public:
    void guardar_mapa();
    void mostrar_mapa();
    void marcar_mapa(int y, int x)
    {
        mapa[y][x] = 1;
    }
    void Poner_Mapa_0();
    int* get_mapa()
    {
        return (int *) mapa;
    }
};

class Dibujo
{
private:
    int *lista_de_trazos; /// esto va a ser un vector que se va a modificar con malloc
    Lienzo *obj_lienzo;
public:
    void dibujar_nuevo();
    void dibujar();
    void borrar();
    void putpixel(SDL_Surface*, int,int);
};

class Plantilla
{
private:
    int mapa[10][10];
public:
    void cargar_plantilla();
    void poner_en_lienzo(Lienzo);
};

class Boton
{
private:
    char tecla;
public:
    cargarBoton();
};

class Ventana
{
private:
public:
};

// esta es la funcion que dibuja en la pantalla, por ahora ignorala
void Dibujo::putpixel(SDL_Surface *surface, int x, int y)
{
    Uint32 pixel;
    pixel = SDL_MapRGB(surface->format, 0xff, 0xff, 0x00); // esto crea una "plantilla" de un pixel amarillo

    bool clic_soltado = false;

    int bpp = surface->format->BytesPerPixel;
    Uint8 *p;

    for (int i = 0; i<10; i++)
    {
        for (int h = 0; h<10; h++)
        {
            p = (Uint8 *)surface->pixels + (y+i) * surface->pitch + (x+h) * bpp;

            switch(bpp)
            {
            case 1:
                *p = pixel;
                break;
            case 2:
                *(Uint16 *)p = pixel;
                break;
            case 3:
                if(SDL_BYTEORDER == SDL_BIG_ENDIAN)
                {
                    p[0] = (pixel >> 16) & 0xff;
                    p[1] = (pixel >> 8) & 0xff;
                    p[2] = pixel & 0xff;
                }
                else
                {
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

void Lienzo::mostrar_mapa()
{
    for (int i = 0; i < 49; i++)
    {
        for (int j=0; j<65; j++)
        {
            if (mapa[i][j] ==0)
                cout <<" ";
            else
            {
                cout << "#";
            }
        }
        cout << endl;
    }
}

void Lienzo::Poner_Mapa_0()
{
    for (int i = 0; i < 49; i++)
    {
        for (int j=0; j<65; j++)
        {
            mapa[i][j] = 0;
        }
    }
}
#endif // CLASES_H_INCLUDED
