#ifndef DIBUJAR_FORMAS_H_INCLUDED
#define DIBUJAR_FORMAS_H_INCLUDED

void dibujar_cuadrado(int x1, int y1, int x2, int y2, Dibujo dibujo_obj, SDL_Surface* screen, Lienzo lienzo_obj){
int maxX, maxY, minX, minY, x, y;

if(x1<x2){
    maxX=x2;
    minX=x1;
}
else {
    maxX=x1;
    minX=x2;
}

if(y1<y2){
    maxY=y2;
    minY=y1;
}
else {
    maxY=y1;
    minY=y2;
}

for(int i=maxX;i>minX;i--){
    x= i;
    y=maxY;
    dibujo_obj.putpixel(screen, x-(x%10), y-(y%10));
    SDL_UpdateRect(screen, x-(x%10), y-(y%10), 10, 10);
    lienzo_obj.marcar_mapa((int) y/10, (int) x/10, 1);

    x= i;
    y= minY;
    dibujo_obj.putpixel(screen, x-(x%10), y-(y%10));
    SDL_UpdateRect(screen, x-(x%10), y-(y%10), 10, 10);
    lienzo_obj.marcar_mapa((int) y/10, (int) x/10, 1);
}
for(int i=maxY;i>minY;i--){

    x= maxX;
    y=i;
    dibujo_obj.putpixel(screen, x-(x%10), y-(y%10));
    SDL_UpdateRect(screen, x-(x%10), y-(y%10), 10, 10);
    lienzo_obj.marcar_mapa((int) y/10, (int) x/10, 1);

    x= minX;
    y=i;
    dibujo_obj.putpixel(screen, x-(x%10), y-(y%10));
    SDL_UpdateRect(screen, x-(x%10), y-(y%10), 10, 10);
    lienzo_obj.marcar_mapa((int) y/10, (int) x/10, 1);
}}

void dibujar_linea(int x1, int y1, int x2, int y2, Dibujo dibujo_obj, SDL_Surface* screen, Lienzo lienzo_obj){

int maxX, maxY, minX, minY, x, y;

if(x1<x2){
    maxX=x2;
    minX=x1;
}
else {
    maxX=x1;
    minX=x2;
}

if(y1<y2){
    maxY=y2;
    minY=y1;
}
else {
    maxY=y1;
    minY=y2;
}

int diferenciaX= maxX-minX;
int diferenciaY= maxY-minY;

if(diferenciaX>diferenciaY)
{
    for(int i=maxX;i>minX;i--){
        x= i;
        y=maxY;
        dibujo_obj.putpixel(screen, x-(x%10), y-(y%10));
        SDL_UpdateRect(screen, x-(x%10), y-(y%10), 10, 10);
        lienzo_obj.marcar_mapa((int) y/10, (int) x/10, 1);
    }
}
else
{
    for(int i=maxY;i>minY;i--){
        x= maxX;
        y=i;
        dibujo_obj.putpixel(screen, x-(x%10), y-(y%10));
        SDL_UpdateRect(screen, x-(x%10), y-(y%10), 10, 10);
        lienzo_obj.marcar_mapa((int) y/10, (int) x/10, 1);
    }
}

}




#endif // DIBUJAR_FORMAS_H_INCLUDED
