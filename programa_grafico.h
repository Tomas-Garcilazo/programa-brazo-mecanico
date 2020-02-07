#ifndef PROGRAMA_GRAFICO_H_INCLUDED
#define PROGRAMA_GRAFICO_H_INCLUDED

void iniciar_programa_grafico(){
	/// tamaño constante de la pantalla
    int const SCREEN_W = 640, SCREEN_H = 480;

    Lienzo lienzo_obj(SCREEN_W/10, SCREEN_H/10);
    lienzo_obj.Poner_Mapa_0();

    int estado_clic = 0;

    int const CUADRADO      = 0;
    int const LIBRE         = 1;
    int const LINEA         = 2;
    int const BORRAR_LIBRE  = 3;
    int const CIRCULO       = 4;
    int const ROMBO         = 5;

    int modoDeDibujo = LIBRE;
    /// ------ NOTAS ------ ///
    /// siempre que leas "mapa" se refiere a mapa de pixeles
    /// lo mas importante es la matriz "int mapa" de abajo
    ///el archivo se crea cuando el programa SE CIERRA

    // pocicion del mouse cuando presiona el clic
    int x, y;
    // pocicion del mouse cuando suelta el clic (f de final)
    int x_f, y_f;

    bool buttonState  = false;
    atexit(SDL_Quit);

    /// cargar imagen
    SDL_Surface *bmp = SDL_LoadBMP("imagenes/botones.bmp");

    /// crea la ventana principal
    SDL_Surface *screen = SDL_SetVideoMode(SCREEN_W + bmp->w, SCREEN_H, 16, SDL_HWSURFACE|SDL_DOUBLEBUF);
    
    Dibujo dibujo_obj(screen);


    /// rectangulo que va a contener la posicion donde se va a mostrar la imagen
    SDL_Rect rectangulo;

    rectangulo.x = screen->w - bmp->w;
    rectangulo.y = 0;

    SDL_BlitSurface(bmp, 0, screen, &rectangulo);

    /// actualizar pantalla
    SDL_Flip(screen);

    /// program main loop
    bool done = false;
    while (!done){
        /// message processing loop
        SDL_Event event;
        while (SDL_PollEvent(&event)){
           switch (event.type){
                case SDL_QUIT:
                    done = true;
                    break;

                case SDL_MOUSEBUTTONDOWN:
                    buttonState = true;
                    estado_clic=1;
                    break;

                case SDL_MOUSEBUTTONUP:
                    buttonState = false;
                    estado_clic=2;
                    break;
                case SDL_KEYDOWN:
                    switch( event.key.keysym.sym ){
                    case SDLK_c:
                        modoDeDibujo=CUADRADO;
                        break;
                    case SDLK_l:
                        modoDeDibujo=LIBRE;
                        break;
                    case SDLK_d:
                        modoDeDibujo=LINEA;
                        break;
                    case SDLK_b:
                        modoDeDibujo=BORRAR_LIBRE;
                        break;
                    case SDLK_a:
                        modoDeDibujo=CIRCULO;
                        break;
                    case SDLK_r:
                        modoDeDibujo=ROMBO;
                        break;
                    default:
                        break;
                    }
                    break;

                }

                        switch(modoDeDibujo){
                            case LIBRE:
                                if(buttonState){
                                    SDL_GetMouseState(&x, &y);
                                    if (x > -1 && x <SCREEN_W && y > -1 && y <SCREEN_H){
                                        dibujo_obj.putpixel(x, y);
                                        lienzo_obj.marcar_mapa(y, x, 1);
                                    }
                                }
                                break;

                            case BORRAR_LIBRE:
                                if(buttonState){
                                    SDL_GetMouseState(&x, &y);

                                    dibujo_obj.putpixel(x, y, 0);
                                    lienzo_obj.marcar_mapa(y, x, 0);
                                }
                                break;

                            case CUADRADO:
                                if(estado_clic==1){
                                SDL_GetMouseState(&x, &y);
                                }
                                else if (estado_clic == 2){

                                    SDL_GetMouseState(&x_f, &y_f);
                                    dibujar_cuadrado(x, y, x_f, y_f, &dibujo_obj, &lienzo_obj);
                                    estado_clic = 0;
                                }
                                break;

                            case LINEA:
                                if(estado_clic==1)
                                {
                                    SDL_GetMouseState(&x,&y);
                                }
                                else if(estado_clic==2)
                                {
                                    SDL_GetMouseState(&x_f, &y_f);
                                    dibujar_linea(x,y, x_f, y_f, &dibujo_obj, &lienzo_obj);
                                    estado_clic = 0;

                                }
                                break;

                            case CIRCULO:
                                if(estado_clic==1){
                                    SDL_GetMouseState(&x, &y);
                                }
                                else if (estado_clic == 2){
                                    SDL_GetMouseState(&x_f, &y_f);
                                    dibujar_circulo(x, y, x_f, y_f, &dibujo_obj, &lienzo_obj);
                                    estado_clic = 0;
                                }
                                break;

                            case ROMBO:
                                if(estado_clic==1){
                                SDL_GetMouseState(&x, &y);
                                }
                                else if (estado_clic == 2){
                                    SDL_GetMouseState(&x_f, &y_f);
                                    dibujar_rombo(x, y, x_f, y_f, &dibujo_obj, &lienzo_obj);
                                    estado_clic = 0;
                                }
                                break;
                            }


                        }
                        estado_clic = 0;

    }

    // ajusta la pantalla y hace el screenshot
    screen->w = 640;
    screen->h = 480;
    SDL_SaveBMP(screen, "imagen.bmp");


    SDL_Quit(); // sale de sdl


    //lienzo_obj.mostrar_mapa();
    lienzo_obj.guardar_mapa();

    /// escribe las instrucciones que se le pasan al brazo
    escribir_codigo_final();

}

#endif // PROGRAMA_GRAFICO_H_INCLUDED
