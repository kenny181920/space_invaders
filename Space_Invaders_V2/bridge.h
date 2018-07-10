#ifndef BRIDGE_H_INCLUDED
#define BRIDGE_H_INCLUDED

#include <allegro.h>

class ImplementatorNave
{
public:
    virtual void INDibujar(void *DNav,void *Imgbuffer,int x, int y,int ix, int iy, int ancho_p, int alto_p){};
    virtual void* loadImg(char dirimg[])=0;
    virtual void* loadBuffer()=0;
};

class ImpNaveAll : public ImplementatorNave
{
public:
    void INDibujar(void *DNav,void *Imgbuffer,int x, int y,int ix, int iy, int ancho_p, int alto_p)
    {
        masked_blit(load_bitmap("Recursos/nave.bmp",NULL),create_bitmap(600, 600) ,ix*ancho_p,iy*alto_p,x,y,ancho_p, alto_p);
    }
    void* loadImg(char* dirimg){
        return load_bitmap(dirimg,NULL);
    }
    void* loadBuffer(){
        return create_bitmap(600,600);
    }
};

class IDJuego{
protected:
    static ImplementatorNave* INave;
public:
    virtual void IDibujar (void *DNav,void *Imgbuffer,int x, int y,int ix, int iy, int ancho_p, int alto_p){
        INave->INDibujar(DNav, Imgbuffer, x, y, ix, iy, ancho_p, alto_p);
    };
    IDJuego(ImplementatorNave* _INave)
    {
        INave = _INave;
    }


};
/*
class IDAbstJuego : public IDJuego
{
public:
    IDAbstJuego(ImplementatorNave* _INave): IDJuego(_INave){};
    void IDibujar(Producto& DNave,void* Imgbuffer){
        INave->INDibujar(DNave,Imgbuffer);
    }
};*/

#endif // BRIDGE_H_INCLUDED
