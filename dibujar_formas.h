#ifndef DIBUJAR_FORMAS_H_INCLUDED
#define DIBUJAR_FORMAS_H_INCLUDED
#include <math.h>
void dibujar_cuadrado(int x1, int y1, int x2, int y2, Dibujo dibujo_obj, SDL_Surface* screen, Lienzo *lienzo_obj){
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
    lienzo_obj->marcar_mapa((int) y/10, (int) x/10, 1);

    x= i;
    y= minY;
    dibujo_obj.putpixel(screen, x-(x%10), y-(y%10));
    SDL_UpdateRect(screen, x-(x%10), y-(y%10), 10, 10);
    lienzo_obj->marcar_mapa((int) y/10, (int) x/10, 1);
}
for(int i=maxY;i>minY;i--){

    x= maxX;
    y=i;
    dibujo_obj.putpixel(screen, x-(x%10), y-(y%10));
    SDL_UpdateRect(screen, x-(x%10), y-(y%10), 10, 10);
    lienzo_obj->marcar_mapa((int) y/10, (int) x/10, 1);

    x= minX;
    y=i;
    dibujo_obj.putpixel(screen, x-(x%10), y-(y%10));
    SDL_UpdateRect(screen, x-(x%10), y-(y%10), 10, 10);
    lienzo_obj->marcar_mapa((int) y/10, (int) x/10, 1);
}}

void dibujar_linea(int x1, int y1, int x2, int y2, Dibujo dibujo_obj, SDL_Surface* screen, Lienzo *lienzo_obj){

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
        x = (int) x/10;
        y = (int) y/10;
        lienzo_obj->marcar_mapa(y, x, 1);
    }
}
else
{
    for(int i=maxY;i>minY;i--){
        x= maxX;
        y=i;
        dibujo_obj.putpixel(screen, x-(x%10), y-(y%10));
        SDL_UpdateRect(screen, x-(x%10), y-(y%10), 10, 10);
        lienzo_obj->marcar_mapa((int) y/10, (int) x/10, 1);
    }
}

}
void dibujar_circulo(int x1, int y1, int x2, int y2, Dibujo dibujo_obj, SDL_Surface* screen, Lienzo *lienzo_obj){
int r_x;

x1 = x1-(x1%10);
y1 = y1-(y1%10);
x2 = x2-(x2%10);
y2 = y2-(y2%10);

int max_x, max_y, min_x, min_y;
if (x2 > x1){
    max_x = x2;
    min_x = x1;
}
else if (x1 > x2){
    max_x = x1;
    min_x = x2;
}
else{return;}

if (y2 > y1){
    max_y = y2;
    min_y = y1;
}
else if (y1 > y2){
    max_y = y1;
    min_y = y2;
}
else{return;}

int radius=(max_x-min_x)/2;

float dist;

// for horizontal movement
for (int i = 0; i <= 2 * radius; i++) {

            // for vertical movement
            for (int j = 0; j <= 2 * radius; j++) {
            dist = sqrt((i - radius) * (i - radius) +
                                               (j - radius) * (j - radius));

            // dist should be in the range (radius - 0.5)
            // and (radius + 0.5) to print stars(*)
            if (dist > radius - 0.5 && dist < radius + 0.5){


                dibujo_obj.putpixel(screen, j-(j%1)+min_x, i-(i%1)+min_y);
                SDL_UpdateRect(screen, j-(j%1)+min_x, i-(i%1)+min_y, 5, 5);
                lienzo_obj->marcar_mapa((int) ((j+min_x)/10), (int) ((i+min_y)/10), 1);

            }

            }
}

int radio_cuadrada= pow(r_x,2);
/*
for(int j=0;j<=r_x*2;j++){
    for(int i=0;i<=r_x*2;i++){
        float cuenta =pow(i-r_x,2.0)+ pow(j-r_x,2.0);

        if(cuenta >= radio_cuadrada-(int)radio_cuadrada/200 && cuenta <= radio_cuadrada+(int)radio_cuadrada/200 ){
        	if (j+min_x < 640 && i+min_y < 480){
                cout << "j: " << j << "\ti: " << i << endl;

                dibujo_obj.putpixel(screen, j-(j%10)+min_x, i-(i%10)+min_y);
                SDL_UpdateRect(screen, j-(j%10)+min_x, i-(i%10)+min_y, 10, 10);
                lienzo_obj->marcar_mapa((int) i/10, (int) j/10, 1);
        	}

        }
    }
}
*/
}

void dibujar_rombo(int x1, int y1, int x2, int y2, Dibujo dibujo_obj, SDL_Surface* screen, Lienzo *lienzo_obj){

x1 = x1-(x1%10);
y1 = y1-(y1%10);
x2 = x2-(x2%10);
y2 = y2-(y2%10);

int max_x, max_y, min_x, min_y;
if (x2 > x1){
    max_x = x2;
    min_x = x1;
}
else if (x1 > x2){
    max_x = x1;
    min_x = x2;
}
else{return;}

if (y2 > y1){
    max_y = y2;
    min_y = y1;
}
else if (y1 > y2){
    max_y = y1;
    min_y = y2;
}


int n = (max_x-min_x)/2;

for (int j = 0; j < n ; ++j) {
        for (int i = 0; i < n-j-1; ++i){
            for (int i = 0; i < 2*j+1; ++i){

                dibujo_obj.putpixel(screen, j-(j%1)+min_x, i-(i%1)+min_y);
                SDL_UpdateRect(screen, j-(j%1)+min_x, i-(i%1)+min_y, 5, 5);
                lienzo_obj->marcar_mapa((int) ((j+min_x)/10), (int) ((i+min_y)/10), 1);
            }
        }
}

        for (int j=n-2; j>=0; --j){
            for (int i=0; i<n-j-1; ++i){
                for (int i=0; i<2*j+1; ++i){
                    dibujo_obj.putpixel(screen, j-(j%1)+min_x, i-(i%1)+min_y);
                    SDL_UpdateRect(screen, j-(j%1)+min_x, i-(i%1)+min_y, 5, 5);
                    lienzo_obj->marcar_mapa((int) ((j+min_x)/10), (int) ((i+min_y)/10), 1);

                }
            }
        }



}



#endif // DIBUJAR_FORMAS_H_INCLUDED
