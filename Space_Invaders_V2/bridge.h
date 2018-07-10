#ifndef BRIDGE_H_INCLUDED
#define BRIDGE_H_INCLUDED

#include <allegro.h>

class ImplementatorNave
{
public:
    virtual void INDibujar(void *DNav,void *Imgbuffer,int x, int y,int ix, int iy, int ancho_p, int alto_p){};
    virtual void* loadImg(char* dirimg)=0;
    virtual void* createBit(int x, int y)=0;
    //virtual void* clear_Color(void *b_m_p, int x)=0;
};

class ImpNaveAll : public ImplementatorNave
{
public:
    void INDibujar(void *DNav,void *Imgbuffer,int x, int y,int ix, int iy, int ancho_p, int alto_p)
    {
        masked_blit(load_bitmap("Recursos/nave.bmp",NULL),create_bitmap(600, 600) ,x,y,ix,iy,ancho_p, alto_p);
    }
    void* loadImg(char* dirimg){
        return load_bitmap(dirimg,NULL);
    }
    void* createBit(int x, int y){
        return create_bitmap(x,y);
    }
    //void* clear_Color(void *b_m_p, int x){
    //    return clear_to_color(b_m_p, x);
    //}
};

class IDJuego{
protected:
    ImplementatorNave* INave;
public:
    virtual void IDibujar (void *DNav,void *Imgbuffer,int x, int y,int ix, int iy, int ancho_p, int alto_p){};
    IDJuego(ImplementatorNave* _INave): INave(_INave){};
};

class IDAbstJuego : public IDJuego
{
public:
    IDAbstJuego(ImplementatorNave* _INave): IDJuego(_INave){};
    void IDibujar(void *DNav,void *Imgbuffer,int x, int y,int ix, int iy, int ancho_p, int alto_p){
        INave->INDibujar(DNav, Imgbuffer, x, y, ix, iy, ancho_p, alto_p);
    }
};

#endif // BRIDGE_H_INCLUDED
