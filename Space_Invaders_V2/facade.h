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
/*
void imprimir_fondo(BITMAP* fondo, BITMAP* buffer, IDJuego& id){
    id->IDibujar(fondo, buffer, 0, 0, 0, 0, 600, 600);
}
*/

void pinta(BITMAP* img_nav, BITMAP* buffer, int x, int y,int ix, int iy, int ancho_p, int alto_p){
    masked_blit(img_nav,buffer,ix*ancho_p,iy*alto_p,x,y,ancho_p, alto_p);
}
/*
void pinta23(IDJuego& id, void* img_nav, void* buffer, int x, int y,int ix, int iy, int ancho_p, int alto_p){
    id.IDibujar(img_nav,buffer,ix*ancho_p,iy*alto_p,x,y,ancho_p, alto_p);
}
*/
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

            //ij1->IDibujar(uno.set_imagen(), buffer,0*uno.set_ancho_p(),0*uno.set_alto_p(),uno.set_x(),uno.set_y(),uno.set_ancho_p(),uno.set_alto_p());
void pintar_enemigo(vector<Producto> &a, BITMAP* buffer, int mov,IDJuego* id){
    BITMAP *img_enem = load_bitmap("Recursos/enemigos.bmp",NULL);
    int indice = -1;
    for(int i=0; i<5; i++){
        for(int j=0; j<11; j++){
            indice++;
            if(a[indice].set_vida()>0)
            {
               //masked_blit(img_enem ,buffer,a[indice].set_ancho_p()*mov,a[indice].set_tipo()-1*a[indice].set_alto_p(),a[indice].set_x(),a[indice].set_y(),a[indice].set_ancho_p(),a[indice].set_alto_p());
               pinta(img_enem ,buffer, a[indice].set_x(),a[indice].set_y(),mov,a[indice].set_tipo()-1,a[indice].set_ancho_p(),a[indice].set_alto_p());
            }
        }
    }
}

///////////////////////////////////////////

void crear_bala(Producto& a,int n_disparos, const int max_disparos ,struct Balas disparos[], const int X, const int Y , const int dy)
    {
                  if( n_disparos < max_disparos-1){
                       n_disparos++;
                        int aux=n_disparos;
                       disparos[n_disparos].x  = X+11;
                       disparos[n_disparos].y  = Y;
                       disparos[n_disparos].dx = 0;
                       disparos[n_disparos].dy = dy;
                       a.get_n_disp(aux);
                   }

    }

    void eliminar(Producto& a, struct Balas disparos[], int n_disparos, int cont)
    {
        Balas Btemp;
        Btemp = disparos[cont];
        disparos[cont] = disparos[n_disparos];
        disparos[n_disparos] = Btemp;
        n_disparos--;
        a.get_n_disp(n_disparos);
        if ( a.set_n_disp() < 0 ) a.get_n_disp(0);
    }

    void elimina_bala(Producto& a,int n_disparos, const int max_disparos,struct Balas disparos[], const int ANCHO, const int ALTO)
    {
          if ( n_disparos > 0 and n_disparos < max_disparos){
                for ( int cont = 1; cont <= n_disparos; cont++){

                          if ( disparos[cont].y > ALTO or disparos[cont].y < 0 or disparos[cont].x > ANCHO or disparos[cont].x < 0  )
                           {
                                  eliminar(a, disparos, n_disparos, cont);
                           }
                }
          }
    }

    void disparo(Producto& a, struct Balas disparos[], BITMAP* buffer){
        if(a.set_tipo())
        crear_bala(a,a.set_n_disp(), a.set_max_disp(),disparos, a.set_x(), a.set_y(), a.set_dir_bala());

        pintar_bala(a.set_n_disp(), a.set_max_disp(), disparos, buffer, load_bitmap("Recursos/Bala2.bmp",NULL), a.set_ancho_b(), a.set_alto_b());
        elimina_bala(a,a.set_n_disp(), a.set_max_disp(), disparos, 600, 600);
    }


     void crear_bala_nave(Producto& a, struct Balas disparos[]){
        if(key[KEY_SPACE] and a.temporizador(5)){
                crear_bala(a,a.set_n_disp(), a.set_max_disp(), disparos, a.set_x(), a.set_y(), a.set_dir_bala());
        }
    }


    void crear_bala_enemigo(vector<Producto> &E, int &azar){
        if(E[azar].set_n_disp() == 0){
            azar = rand()%55;
            while(E[azar].set_vida() == 0){
                azar = rand()%55;
            }
        }
    }

    struct escudo{
        int x,y;
        int dan;
        int tipo;
    };

    void iniciar_escudo(struct escudo muros[]){
        char pos_muros[3][22] = {
            "AEC   AEC   AEC   AEC",
            "B D   B D   B D   B D",
        };
        int r = 0;
        for(int i=0; i<21; i++){
            for(int j=0; j<2; j++){
                if(pos_muros[j][i]!=' '){
                    muros[r].x = 90+i*20;
                    muros[r].y = 450+j*15;
                    muros[r].dan = 0;
                    if(pos_muros[j][i] == 'A') muros[r].tipo = 0;
                    if(pos_muros[j][i] == 'B') muros[r].tipo = 1;
                    if(pos_muros[j][i] == 'C') muros[r].tipo = 2;
                    if(pos_muros[j][i] == 'D') muros[r].tipo = 3;
                    if(pos_muros[j][i] == 'E') muros[r].tipo = 4;
                    r++;
                }
            }
        }
    };

    void pintar_escudos(struct escudo ES[], BITMAP* img_mur, BITMAP* buffer){
        for(int i=0; i<20; i++){
            if(ES[i].dan!=3)
                masked_blit(img_mur, buffer, ES[i].dan*20, ES[i].tipo*16, ES[i].x, ES[i].y, 20, 16);
        }
    }
    /*
    void pintar_escudos(struct escudo ES[], BITMAP* img_mur, BITMAP* buffer, IDJuego& id){
        for(int i=0; i<20; i++){
            if(ES[i].dan!=3)
                id->IDibujar(img_mur, buffer, ES[i].dan*20, ES[i].tipo*16, ES[i].x, ES[i].y, 20, 16);
        }
    }
    */
    bool elimina_bala_objeto(Producto& N, Producto& E, struct Balas B[])
    {
        if ( N.set_n_disp() > 0 and N.set_n_disp() < N.set_max_disp()){
            for ( int cont = 1; cont <= N.set_n_disp(); cont++){
                if(colicion(E.set_x(), E.set_y(), E.set_ancho_p(), E.set_alto_p(), B[cont].x, B[cont].y, N.set_ancho_b(), N.set_alto_b()) and E.set_vida()>0){
                    eliminar(N,B,N.set_n_disp(), cont);
                    int aux = E.set_vida()-1;
                    E.get_vida(aux);
                    return true;
                }
            }
            return false;
        }
    }

    void elimina_bala_escudo(Producto& N, struct escudo ES[], struct Balas B[]){
        if ( N.set_n_disp() > 0 and N.set_n_disp() < N.set_max_disp()){
            for ( int cont = 1; cont <= N.set_n_disp(); cont++){
                for(int i=0; i<20; i++){
                    if(colicion(ES[i].x, ES[i].y, 20, 16, B[cont].x, B[cont].y, N.set_ancho_b(), N.set_alto_b()) and ES[i].dan<3){
                        eliminar(N,B, N.set_n_disp(), cont);
                        ES[i].dan++;
                    }
                }
            }
        }
    }

    void explosion1(Producto& E, BITMAP* buffer){
        BITMAP* parche = create_bitmap(25,20);
        clear_to_color(parche, 0x000000);
        blit(parche, buffer, 0, 0, E.set_x(), E.set_y(), 25, 20);
        masked_blit(load_bitmap("Recursos/pum_enemigo.bmp", NULL), buffer, 0, 0, E.set_x() - 10, E.set_y(), 41, 34);
        //IDibujar()
    }

    /*
    void explosion1(Producto& E, IDJuego& id){
        BITMAP* parche = create_bitmap(25,20);
        clear_to_color(parche, 0x000000);
        blit(parche, buffer, 0, 0, E.set_x(), E.set_y(), 25, 20);
        id->IDibujar(load_bitmap("Recursos/pum_enemigo.bmp", NULL), buffer, 0, 0, E.set_x() - 10, E.set_y(), 41, 34);
    }
    */
    void explosion2(Producto& N, BITMAP* buffer, BITMAP* fondo){
        BITMAP* parche = create_bitmap(30,20);
        clear_to_color(parche, 0x000000);
        for(int i=0; i<6; i++){
            for(int j=1; j<=2; j++){
                blit(parche, buffer, 0, 0, N.set_x(), N.set_y(), 30, 20);
                masked_blit(load_bitmap("Recursos/nave.bmp",NULL), buffer, j*30, 0, N.set_x(), N.set_y(), 30, 20);
                masked_blit(fondo, buffer, 0, 0, 0, 0, 600, 600);
                blit(buffer, screen, 0, 0, 0, 0, 600, 600);
                rest(50);
            }
        }
    }
    /*
    void explosion2(Producto& N, BITMAP* buffer, BITMAP* fondo,IDJuego& id){
        BITMAP* parche = create_bitmap(30,20);
        clear_to_color(parche, 0x000000);
        for(int i=0; i<6; i++){
            for(int j=1; j<=2; j++){
                blit(parche, buffer, 0, 0, N.set_x(), N.set_y(), 30, 20);
                id->IDibujar(load_bitmap("Recursos/nave.bmp",NULL), buffer, j*30, 0, N.set_x(), N.set_y(), 30, 20)
                id->IDibujar(fondo, buffer, 0, 0, 0, 0, 600, 600)
                blit(buffer, screen, 0, 0, 0, 0, 600, 600);
                rest(50);
            }
        }
    }
    */
//////////////////////////////////////////////////////////

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


        ImplementatorNave* hh=new ImpNaveAll();
        IDJuego* ij1=new IDAbstJuego(hh);

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

        while(!key[KEY_ESC] and uno.set_vida()>0){

            clear_to_color(buffer,0x000000);
            pintar_escudos(ES, img_muros, buffer);

            //pinta23(uno.set_imagen(), uno.set_buffer(),uno.set_x(),uno.set_y(),0,0,uno.set_ancho_p(),uno.set_alto_p(), ij1);
            ij1->IDibujar(uno.set_imagen(), buffer,0*uno.set_ancho_p(),0*uno.set_alto_p(),uno.set_x(),uno.set_y(),uno.set_ancho_p(),uno.set_alto_p());
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
            pintar_enemigo(E,buffer,mov,ij1);
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
