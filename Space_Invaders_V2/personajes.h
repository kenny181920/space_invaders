#ifndef PERSONAJES_H_INCLUDED
#define PERSONAJES_H_INCLUDED
//#define ANCHO 600
//#define ALTO  600
#include <allegro.h>
#include <vector>
#include "disparo.h"
#include <string>
#include <iostream>
using namespace std;

class Nave
{
private:
    int x,y;
    int max_disp = 2;
    int tick;
    int ancho_b;
    int alto_b;
    int ancho_p;
    int alto_p;
    int dir_bala;

public:
    int set_x()
    {
        return x;
    }

    int set_y()
    {
        return y;
    }

    int set_max_disp()
    {
        return max_disp;
    }

    int set_tick()
    {
        return tick;
    }

    int set_ancho_b()
    {
        return ancho_b;
    }

    int set_alto_b()
    {
        return alto_b;
    }

    int set_ancho_p()
    {
        return ancho_p;
    }

    int set_alto_p()
    {
        return alto_p;
    }

    int set_dir_bala()
    {
        return dir_bala;
    }

    Nave(int _ancho_b, int _alto_b, int _ancho_p, int _alto_p, int _dir_bala)
    {
        //max_disp = 2;
        ancho_b = _ancho_b;
        alto_b = _alto_b;
        ancho_p = _ancho_p;
        alto_p = _alto_p;
        dir_bala = _dir_bala;
    }
    Nave(){};
};

class Heroe:public Nave
{
public:
    Heroe():Nave(6, 12, 30, 20, -8){}//3 vida
};

class Enemigo:public Nave
{
public:
    Enemigo():Nave(6, 12, 25, 20, 8){}//1 vida
};

class NaveFlyweight
{
private:
    static Heroe* s_heroe;
    static Enemigo* s_enemigo;
public:
    static Nave* getNave(int tipo)
    {
        switch(tipo)
        {
        case 1:
            if(!s_heroe)
            {
                s_heroe = new Heroe();
            }
            return s_heroe;
        case 2:
            if(!s_enemigo)
            {
                s_enemigo = new Enemigo();
            }
            return s_enemigo;

        default:
            return NULL;
        }
    }
};

Heroe* NaveFlyweight::s_heroe;
Enemigo* NaveFlyweight::s_enemigo;

class Producto:public Nave
{
private:
    Nave* m_model;
    int x;
    int y;
    int tipo;
    int tick = 0;
    int n_disp = 0;
    int vida;
    //BITMAP* img_bala = load_bitmap("Recursos/Bala2.bmp",NULL);

public:
    Producto(Nave* model,int _x,int _y,int _tipo,int _vida)
    {
        m_model = model;
        x = _x;
        y = _y;
        tipo = _tipo;
        vida = _vida;
    }

    void get_n_disp(int _n_disp)
    {
        n_disp = _n_disp;
    }

    int set_x()
    {
        return x;
    }

    int set_y()
    {
        return y;
    }

    int set_n_disp()
    {
        return n_disp;
    }

    int set_max_disp()
    {
        return m_model->set_max_disp();
    }

    int set_tick()
    {
        return m_model->set_tick();
    }

    int set_ancho_b()
    {
        return m_model->set_ancho_b();
    }

    int set_alto_b()
    {
        return m_model->set_alto_b();
    }

    int set_ancho_p()
    {
        return m_model->set_ancho_p();
    }

    int set_alto_p()
    {
        return m_model->set_alto_p();
    }

    int set_dir_bala()
    {
        return m_model->set_dir_bala();
    }

    int set_vida()
    {
        return vida;
    }

    void get_vida(int _vida)
    {
        vida=_vida;
    }

    int set_tipo()
    {
        return tipo;
    }

    void mueve()
    {
        if(key[KEY_LEFT]) x -= 5;
        if(key[KEY_RIGHT]) x += 5;
    }

    bool limites(vector<Producto> &a, int &dir){
        for(int i=0; i<55; i++){
            if((a[i].set_x()>520 or a[i].set_x()<50) and a[i].set_vida()!= 0){
                dir = -1*dir;
                return true;
            }
        }
        return false;
    }

    void mover_enemigos(vector<Producto> &a, int &mov, int &dir){
        for(int i=0; i<55; i++){
            a[i].x += dir;
        }

        if(++mov == 2) mov = 0;

        if(limites(a,dir)){
            for(int j=0; j<55; j++){
                a[j].y +=10;
            }
        }

    }

    bool temporizador(int tiempo){
        tick++;
        if(tick == tiempo){
            tick = 0;
            return true;
        }
        return false;
    }

};

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
    //BITMAP* img_bala = load_bitmap("Recursos/Bala2.bmp",NULL);

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
                //cout<<"crear bala"<<" ";
        crear_bala(a,a.set_n_disp(), a.set_max_disp(),disparos, a.set_x(), a.set_y(), a.set_dir_bala());

        pintar_bala(a.set_n_disp(), a.set_max_disp(), disparos, buffer, load_bitmap("Recursos/Bala2.bmp",NULL), a.set_ancho_b(), a.set_alto_b());
        elimina_bala(a,a.set_n_disp(), a.set_max_disp(), disparos, 600, 600);
        //cout<<"sadadsadas";
    }


     void crear_bala_nave(Producto& a, struct Balas disparos[]){
        if(key[KEY_SPACE] and a.temporizador(5)){
                //cout<<"espacio"<<" ";
                crear_bala(a,a.set_n_disp(), a.set_max_disp(), disparos, a.set_x(), a.set_y(), a.set_dir_bala());
                //cout<<"espaciotuputa"<<" ";
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
    }

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

#endif // PERSONAJES_H_INCLUDED
