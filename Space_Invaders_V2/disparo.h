#ifndef DISPARO_H_INCLUDED
#define DISPARO_H_INCLUDED
#include <allegro.h>
#include <iostream>
using namespace std;


struct Balas{
    int x , y;
    int dx , dy;

};

bool colicion(int x1, int y1, int w1, int h1, int x2, int y2, int w2, int h2)
{
    return((x1<x2+w2) and (x2<x1+w1) and (y1<y2+h2) and (y2<y1+h1));
}



void pintar_bala(int n_disparos, const int max_disparos,struct Balas disparos[], BITMAP* buffer, BITMAP* bala, int ancho, int alto)
{

     if ( n_disparos > 0 and n_disparos < max_disparos){
            for ( int cont = 1; cont <= n_disparos; cont++){
                       disparos[cont].x += disparos[cont].dx;
                       disparos[cont].y += disparos[cont].dy;
                       masked_blit( bala, buffer, 0, 0, disparos[cont].x, disparos[cont].y, ancho, alto);
            }
     }

}
/*
void pintar_bala(int n_disparos, const int max_disparos,struct Balas disparos[], BITMAP* buffer, BITMAP* bala, int ancho, int alto, IDJuego& id)
{

     if ( n_disparos > 0 and n_disparos < max_disparos){
            for ( int cont = 1; cont <= n_disparos; cont++){
                       disparos[cont].x += disparos[cont].dx;
                       disparos[cont].y += disparos[cont].dy;
                       id->IDibujar(bala, buffer, 0, 0, disparos[cont].x, disparos[cont].y, ancho, alto);
            }
     }

}
*/


#endif // DISPARO_H_INCLUDED
