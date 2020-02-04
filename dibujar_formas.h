#ifndef DIBUJAR_FORMAS_H_INCLUDED
#define DIBUJAR_FORMAS_H_INCLUDED

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
    dibujo_obj.putpixel(screen, x, y);
    lienzo_obj->marcar_mapa(y, x, 1);

    x= i;
    y= minY;
    dibujo_obj.putpixel(screen, x, y);
    lienzo_obj->marcar_mapa(y, x, 1);
}
for(int i=maxY;i>minY;i--){

    x= maxX;
    y=i;
    dibujo_obj.putpixel(screen, x, y);
    lienzo_obj->marcar_mapa(y, x, 1);

    x= minX;
    y=i;
    dibujo_obj.putpixel(screen, x, y);
    lienzo_obj->marcar_mapa( y, x, 1);
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
        x = i;
        y = maxY;

        dibujo_obj.putpixel(screen, x, y);
        lienzo_obj->marcar_mapa(y, x, 1);
    }
}
else
{
    for(int i=maxY;i>minY;i--){
        x = maxX;
        y = i;

        dibujo_obj.putpixel(screen, x, y);
        lienzo_obj->marcar_mapa(y, x, 1);
    }
}

}
void dibujar_circulo(int x1, int y1, int x2, int y2, Dibujo dibujo_obj, SDL_Surface* screen, Lienzo *lienzo_obj){

x1 -= (x1%10);
y1 -= (y1%10);
x2 -= (x2%10);
y2 -= (y2%10);

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
/*
else if (y1 > y2){
    max_y = y1;
    min_y = y2;
}
else{return;}
*/
else{
    max_y = y1;
    min_y = y2;
}

float diametro = max_x - min_x;
float r_x = diametro / 2;
float radio_cuadrada= pow(r_x,2);

for(int j=0;j<=diametro; j+=10){
    for(int i=0;i<=diametro; i+=10){
        for(int a = -10; a <= 10; a+= 10){
            for(int b = -10; b <= 10; b+= 10){
                float cuenta_1 = pow(i-r_x,2.0) + pow(j-r_x,2.0);
                float cuenta_2 = pow(i+b-r_x,2.0) + pow(j+a-r_x,2.0);
                if(cuenta_1 <= radio_cuadrada && cuenta_2 > radio_cuadrada){
                    int x = j+min_x;
                    int y = i+min_y;

                    dibujo_obj.putpixel(screen, x, y);
                    lienzo_obj->marcar_mapa(y, x, 1);
                }
            }
        }
    }
}
}

void dibujar_rombo(int x1, int y1, int x2, int y2, Dibujo dibujo_obj, SDL_Surface* screen, Lienzo *lienzo_obj){

x1 -= x1%10;
y1 -= y1%10;
x2 -= x2%10;
y2 -= y2%10;

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
/*
else if (y1 > y2){
    max_y = y1;
    min_y = y2;
}
else{return;}
*/
else{
    max_y = y1;
    min_y = y2;
}

int radio = (max_x-min_x)/2;
radio -= radio % 10;

for (int j = 0; j <= radio; j+= 10) {

    int x_real = j + min_x;
    int y_real = j + min_y + radio;
    dibujo_obj.putpixel(screen, x_real, y_real);
    lienzo_obj->marcar_mapa(y_real,  x_real, 1);

    y_real = -j + min_y + radio;
    dibujo_obj.putpixel(screen, x_real, y_real);
    lienzo_obj->marcar_mapa(y_real, x_real, 1);

    x_real = j + min_x + radio;
    y_real = j + min_y;
    dibujo_obj.putpixel(screen, x_real, y_real);
    lienzo_obj->marcar_mapa(y_real, x_real, 1);

    y_real = -j + min_y + radio*2;
    dibujo_obj.putpixel(screen, x_real, y_real);
    lienzo_obj->marcar_mapa(y_real, x_real, 1);
}

}

#endif // DIBUJAR_FORMAS_H_INCLUDED
