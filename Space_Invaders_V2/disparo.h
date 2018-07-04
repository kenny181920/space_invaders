#ifndef DISPARO_H_INCLUDED
#define DISPARO_H_INCLUDED
#include <allegro.h>
#include "personajes.h"
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
bool elimina_bala_objeto(struct NAVE& N, struct NAVE& E, struct Balas B[])
{
    if ( N.n_disp > 0 and N.n_disp < N.max_disp){
        for ( int cont = 1; cont <= N.n_disp; cont++){
            if(colicion(E.x, E.y, E.ancho_p, E.alto_p, B[cont].x, B[cont].y, N.ancho_b, N.alto_b) and E.vida>0){
                eliminar(B,N.n_disp, cont);
                E.vida--;
                return true;
            }
        }
        return false;
    }
}

void elimina_bala_escudo(struct NAVE &N, struct escudo ES[], struct Balas B[]){
    if ( N.n_disp > 0 and N.n_disp < N.max_disp){
        for ( int cont = 1; cont <= N.n_disp; cont++){
            for(int i=0; i<20; i++){
                if(colicion(ES[i].x, ES[i].y, 20, 16, B[cont].x, B[cont].y, N.ancho_b, N.alto_b) and ES[i].dan<3){
                    eliminar(B, N.n_disp, cont);
                    ES[i].dan++;
                }
            }
        }
    }
}
*/

#endif // DISPARO_H_INCLUDED
