#ifndef PERSONAJES_H_INCLUDED
#define PERSONAJES_H_INCLUDED
//#define ANCHO 600
//#define ALTO  600
#include <allegro.h>
#include <vector>
#include "disparo.h"
#include "bridge.h"
#include <string>
#include <iostream>
using namespace std;

class ImplementatorNave;
class IDJuego;

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
    void* image;
    void* imageBala;
    void* imageBuffer;
    void* imageEXPL;
    void* imagePARCHE;

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

    void* set_imagen(){
        return image;
    }

    void* set_buffer(){
        return imageBuffer;
    }

    Nave(int _ancho_b, int _alto_b, int _ancho_p, int _alto_p, int _dir_bala, char *dir_ar, char *dir_explo, int _xparche, int _yparche)
    {
        //max_disp = 2;
        ancho_b = _ancho_b;
        alto_b = _alto_b;
        ancho_p = _ancho_p;
        alto_p = _alto_p;
        dir_bala = _dir_bala;
        image = IDJuego::INave->loadImg(dir_ar);
        //imageBala = IDJuego::INave->loadImg("Recursos/Bala2.bmp");
        //imageBuffer = IDJuego::INave->createBit(600,600);
        //imageEXPL = IDJuego::INave->loadImg(dir_explo);
        //imagePARCHE = IDJuego::INave->createBit(_xparche,_yparche);
    }
    Nave(){};
};

class Heroe:public Nave
{
public:
    Heroe():Nave(6, 12, 30, 20, -8,"Recursos/nave.bmp","Recursos/pum_enemigo.bmp",30,20){}//3 vida
};

class Enemigo:public Nave
{
public:
    Enemigo():Nave(6, 12, 25, 20, 8,"Recursos/enemigos.bmp","Recursos/pum_enemigo.bmp",25,20){}//1 vida
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

    void* set_imagen()
    {
        return m_model->set_imagen();
    }

    void* set_buffer()
    {
        return m_model->set_buffer();
    }

};

#endif // PERSONAJES_H_INCLUDED
