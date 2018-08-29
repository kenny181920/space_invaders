#ifndef BRIDGE_H_INCLUDED
#define BRIDGE_H_INCLUDED

#include <allegro.h>

class ImplementatorNave
{
public:
    virtual void INDibujar(void *DNav,void *Imgbuffer,int x, int y,int ix, int iy, int ancho_p, int alto_p){};
    virtual void* loadImg(char* dirimg)=0;
    virtual void createBit()=0;
    //virtual void* clear_Color(void *b_m_p, int x)=0;
};

class ImpNaveAll : public ImplementatorNave
{
public:
    BITMAP * buffer = create_bitmap(600,600);
public:
    void INDibujar(void * DNav,void * Imgbuffer,int x, int y,int ix, int iy, int ancho_p, int alto_p)
    {
        masked_blit((BITMAP *)DNav, (BITMAP *)Imgbuffer ,x,y,ix,iy,ancho_p, alto_p);
    }
    void* loadImg(char* dirimg){
        return load_bitmap(dirimg,NULL);
    }
    void createBit(){
        allegro_init();
    }
    //void* clear_Color(void *b_m_p, int x){
    //    return clear_to_color(b_m_p, x);
    //}
};

class IDJuego{
public:
    static ImplementatorNave* INave;
public:
    virtual void IDibujar (void *DNav,void *Imgbuffer,int x, int y,int ix, int iy, int ancho_p, int alto_p){};
    //IDJuego(ImplementatorNave* _INave): INave(_INave){};
    IDJuego(ImplementatorNave* _INave){
        INave=_INave;
    }
    virtual void createB()=0;
};

ImplementatorNave* IDJuego::INave=0;

class IDAbstJuego : public IDJuego
{
public:
    IDAbstJuego(ImplementatorNave* _INave): IDJuego(_INave){};
    void IDibujar(void *DNav,void *Imgbuffer,int x, int y,int ix, int iy, int ancho_p, int alto_p){
        INave->INDibujar(DNav, Imgbuffer, x, y, ix, iy, ancho_p, alto_p);
    }
    virtual void createB(){
        INave->createBit();
    }
};

#endif // BRIDGE_H_INCLUDED
