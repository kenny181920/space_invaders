#ifndef FACADE_H_INCLUDED
#define FACADE_H_INCLUDED

//#define ANCHO 600
//#define ALTO  600

#include "escenario.h"

//#include "disparo.h"
#include "bridge.h"
#include "personajes.h"
#include <allegro.h>
#include <time.h>
#include <vector>
#include <iostream>
using namespace std;

void inicia_allegro(int ANCHO_ , int ALTO_){
   allegro_init();
   install_keyboard();
   set_color_depth(32);
   set_gfx_mode(GFX_AUTODETECT_WINDOWED, ANCHO_, ALTO_, 0, 0);
}

void imprimir_fondo(BITMAP* fondo, BITMAP* buffer){
    masked_blit(fondo, buffer, 0, 0, 0, 0, 600, 600);
}

void pinta(BITMAP* img_nav, BITMAP* buffer, int x, int y,int ix, int iy, int ancho_p, int alto_p){
    masked_blit(img_nav,buffer,ix*ancho_p,iy*alto_p,x,y,ancho_p, alto_p);
}

void acomoda_enemigos(vector<Producto> &a){
    int indice = -1;
    int _tipo = 0;
    for(int i=0; i<5; i++){
        _tipo++;
        if(_tipo == 4) _tipo = 1;
        for(int j=0; j<11; j++){
            indice++;
            Producto aux = Producto(NaveFlyweight::getNave(2),140+j*30, 130+i*24,_tipo,1);
            a.push_back(aux);
        }
    }
}

void pintar_enemigo(vector<Producto> &a, BITMAP* buffer, int mov){
    BITMAP *img_enem = load_bitmap("Recursos/enemigos.bmp",NULL);
    int indice = -1;
    for(int i=0; i<5; i++){
        for(int j=0; j<11; j++){
            indice++;
            if(a[indice].set_vida()>0)
            {
               pinta(img_enem, buffer, a[indice].set_x(),a[indice].set_y(),mov,a[indice].set_tipo()-1,a[indice].set_ancho_p(),a[indice].set_alto_p());
            }
        }
    }
}



class Juego
{

private:

public:
    void start()
    {
        inicia_allegro(600,600);

        BITMAP *img_nav = load_bitmap("Recursos/nave.bmp",NULL);
        //char tipo=save_bitmap("Recursos/nave.bmp",NULL,NULL);
        //cout<<tipo;
        //BITMAP* img_bala = load_bitmap("Recursos/Bala2.bmp",NULL);
        BITMAP *buffer = create_bitmap(600, 600);
       // BITMAP *portada = load_bitmap("Recursos/portada.bmp",NULL);
        BITMAP *fondo = load_bitmap("Recursos/fondo.bmp",NULL);
        BITMAP *img_muros = load_bitmap("Recursos/escudos.bmp",NULL);


         Portada *a = Portada::getInstance();
         //Fondo *s = Fondo::getInstance();
         Producto uno = Producto(NaveFlyweight::getNave(1),600/2,600-70,0,3);
         vector<Producto> E;
         acomoda_enemigos(E);
         int mov = 0, dir = -5;
         int vel_juego = 10;
         Balas disparos[uno.set_max_disp()];
         Balas disp_E[E[0].set_max_disp()];
         int azar= rand()%55;
         escudo ES[30];
         iniciar_escudo(ES);

        while(!key[KEY_ESC]){

            clear_to_color(buffer,0x000000);
            pintar_escudos(ES, img_muros, buffer);

            pinta(img_nav, buffer,uno.set_x(),uno.set_y(),0,0,uno.set_ancho_p(),uno.set_alto_p());
            uno.mueve();

            crear_bala_nave(uno,disparos);
            disparo(uno,disparos,buffer);

            for(int i=0; i<55; i++){
                if(elimina_bala_objeto(uno, E[i], disparos)){
                    explosion1(E[i], buffer);
                }
            }
            elimina_bala_escudo(uno,ES,disparos);


            if(E[0].temporizador(vel_juego)){
                E[0].mover_enemigos(E,mov,dir);
            }
            pintar_enemigo(E,buffer,mov);
            crear_bala_enemigo(E,azar);
            disparo(E[azar],disp_E, buffer);

            if(elimina_bala_objeto(E[azar], uno, disp_E)) explosion2(uno, buffer, fondo);
            elimina_bala_escudo(E[azar],ES,disp_E);
            //s;
            imprimir_fondo(fondo,buffer);
            blit(buffer, screen, 0, 0, 0, 0, 600, 600);
            rest(20);
        }

    }

};

#endif // FACADE_H_INCLUDED
