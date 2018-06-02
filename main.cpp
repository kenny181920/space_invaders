#include <allegro.h>
#include <stdlib.h>
#include <time.h>
#include "inicia.h"
#include "disparos.h"
#include "personajes.h"
#include "diseno.h"

#define ANCHO 600
#define ALTO  600




int main(){

    srand(time(NULL));

    inicia_allegro(ANCHO,ALTO);
    BITMAP *buffer = create_bitmap(ANCHO, ALTO);
    BITMAP *portada = load_bitmap("Recursos/portada.bmp",NULL);
    BITMAP *fondo = load_bitmap("Recursos/fondo.bmp",NULL);

    PORTADA(portada);

    NAVE N;
    N.inicia("Recursos/nave.bmp", "Recursos/Bala2.bmp", 6, 12, 30, 20, ANCHO/2, ALTO-70, -8, 0, 3);
    NAVE E[60];
    acomoda_enemigos(E);
    Balas disparos[N.max_disp];
    Balas disp_E[E[0].max_disp];

    int azar = rand()%55;
    int mov = 0;

    while(!key[KEY_ESC]){
        clear_to_color(buffer,0x000000);
        N.pinta(buffer,0,0);
        N.mueve();
        if(key[KEY_SPACE] and N.temporizador(5))
        crear_bala(N.n_disp, N.max_disp, disparos, N.x, N.y, N.dir_bala);
        N.disparo(disparos, buffer);

        for(int i=0; i<55; i++){
            if(elimina_bala_objeto(N, E[i], disparos)){
                explosion1(E[i], buffer);
            }
        }

        pintar_enemigo(E,buffer,mov);
        if(E[azar].n_disp == 0) azar = rand()%55;
        E[azar].disparo(disp_E, buffer);
        if(E[0].temporizador(20))
        if(++mov == 2) mov = 0;

        if(elimina_bala_objeto(E[azar], N, disp_E)) explosion2(N, buffer, fondo);

        imprimir_fondo(fondo, buffer);
        blit(buffer, screen, 0, 0, 0, 0, ANCHO, ALTO);
        rest(20);

    }

	return 0;
}
END_OF_MAIN();

