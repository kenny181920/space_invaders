#ifndef ESCENARIO_H_INCLUDED
#define ESCENARIO_H_INCLUDED
#include <allegro.h>

class Fondo
{
public:
  static Fondo *getInstance()
  {
    if (instance == NULL)
      instance = new Fondo();

    return instance;
  }

protected:
  Fondo()
  {
    masked_blit(fondo, buffer, 0, 0, 0, 0, 600, 600);

  }

  virtual ~Fondo()
  {
  }

  Fondo(Fondo const&);
  Fondo& operator=(Fondo const&);

private:
  static Fondo *instance;
  BITMAP* fondo = load_bitmap("Recursos/fondo.bmp",NULL);
  BITMAP* buffer = create_bitmap(600, 600);
};

Fondo* Fondo::instance=NULL;

class Portada
{
public:
  static Portada *getInstance()
  {
    if (instance == NULL)
      instance = new Portada();

    return instance;
  }

protected:
  Portada()
  {
    int parpadeo = 0;
    int y = 0;
    int cont = 0;
    bool salida = false;
    bool carga = false;

    while(!salida){
        if(parpadeo < 25) blit(p, screen, 0, y, 0, 100, 600, 400);
        else blit(p, screen, 600, y, 0, 100, 600, 400);

        if(key[KEY_ENTER]){
            y = 400;
            carga = true;
        }

        if(carga) cont++;
        if(cont > 400) salida = true;

        rest(5);
        if(++parpadeo == 50) parpadeo = 0;
    }

    clear_to_color(screen, 0x000000);
  }

  virtual ~Portada()
  {
  }

  Portada(Portada const&);
  Portada& operator=(Portada const&);

private:
  static Portada *instance;
  BITMAP* p = load_bitmap("Recursos/portada.bmp",NULL);
};

Portada* Portada::instance=NULL;




#endif // ESCENARIO_H_INCLUDED
