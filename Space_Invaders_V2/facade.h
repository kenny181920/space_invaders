#ifndef FACADE_H_INCLUDED
#define FACADE_H_INCLUDED
#include <allegro.h>
#include <time.h>
//#define ANCHO 600
//#define ALTO  600
#include <iostream>
#include "escenario.h"
#include "personajes.h"
#include "disparo.h"
#include <vector>
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
            Producto aux = Producto(NaveFlyweight::getNave(2),140+j*30, 130+i*24,_tipo);
            a.push_back(aux);
            //E[indice].inicia("Recursos/enemigos.bmp", "Recursos/Bala_enem.bmp", 6, 12, 25, 20, 140+j*30, 130+i*24, 8, _tipo, 1);
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


 void crear_bala_nave(Producto a, struct Balas disparos[]){
     cout<<"bala";
    if(key[KEY_SPACE] and a.temporizador(5))
        cout<<"espacio";
        crear_bala(a.set_n_disp(), a.set_max_disp(), disparos, a.set_x(), a.set_y(), a.set_dir_bala());
}

class Juego
{

private:
    //Engine engine;
    //Headlights headlights;

public:
    void start()
    {
        inicia_allegro(600,600);

        BITMAP *img_nav = load_bitmap("Recursos/nave.bmp",NULL);
        //BITMAP* img_bala = load_bitmap("Recursos/Bala2.bmp",NULL);
        BITMAP *buffer = create_bitmap(600, 600);
       // BITMAP *portada = load_bitmap("Recursos/portada.bmp",NULL);
        BITMAP *fondo = load_bitmap("Recursos/fondo.bmp",NULL);
        //BITMAP *img_muros = load_bitmap("Recursos/escudos.bmp",NULL);


         Portada *a = Portada::getInstance();
         //Fondo *s = Fondo::getInstance();
         Producto uno = Producto(NaveFlyweight::getNave(1),600/2,600-70,0);
         vector<Producto> E;
         acomoda_enemigos(E);
         int mov = 0, dir = -5;
         int vel_juego = 10;
         Balas disparos[uno.set_max_disp()];
         //Balas disp_E[E[0].set_max_disp];

        while(!key[KEY_ESC]){

            clear_to_color(buffer,0x000000);
            pinta(img_nav, buffer,uno.set_x(),uno.set_y(),0,0,uno.set_ancho_p(),uno.set_alto_p());
            uno.mueve();

            crear_bala_nave(uno,disparos);
            uno.disparo(disparos,buffer);

            if(E[0].temporizador(vel_juego)){
                E[0].mover_enemigos(E,mov,dir);
            }
            pintar_enemigo(E,buffer,mov);
            //s;
            imprimir_fondo(fondo,buffer);
            blit(buffer, screen, 0, 0, 0, 0, 600, 600);
            rest(20);
        }

    }

};

#endif // FACADE_H_INCLUDED
