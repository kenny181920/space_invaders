#include <allegro.h>
#include "personajes.h"
#ifndef DISPAROS_H_INCLUDED
#define DISPAROS_H_INCLUDED

struct Balas{
    int x , y;
    int dx , dy;

};

bool colicion(int x1, int y1, int w1, int h1, int x2, int y2, int w2, int h2);

void crear_bala(int& n_disparos, const int max_disparos,struct Balas disparos[], const int X, const int Y ,const int dy);

void pintar_bala(int& n_disparos, const int max_disparos,struct Balas disparos[], BITMAP* buffer, BITMAP* bala, int ancho, int alto);

void elimina_bala(int& n_disparos, const int max_disparos,struct Balas disparos[], const int ANCHO, const int ALTO);

void eliminar(struct Balas disparos[], int& n_disparos, int cont);

bool elimina_bala_objeto(struct NAVE& N, struct NAVE& E, struct Balas B[]);

void elimina_bala_escudo(struct NAVE &N, struct escudo ES[], struct Balas B[]);

#endif // DISPAROS_H_INCLUDED
