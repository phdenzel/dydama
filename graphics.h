/*
 * graphics.h
 *
 * @author: phdenzel
 *
 * Graphics components of DYDAMA
 *
 */

#ifndef GRAPHICS_H
#define GRAPHICS_H

#include "world.h"

#include <SDL2/SDL.h>


typedef struct pcolor {
  unsigned char r;
  unsigned char g;
  unsigned char b;
  unsigned char alpha;
} pcolor_t;


double linearMap(double, double, double, double, double);
void SDL_RenderFillCircle(SDL_Renderer *, int, int, int);
int processEvents(SDL_Window *, int);
void resetBg(SDL_Renderer *);
void drawInRealSpace(particle_t *, unsigned char,
                     double, double, double, double,
                     SDL_Renderer *, SDL_Window *);
void drawInPhaseSpace(particle_t *, unsigned char,
                      double, double, double, double,
                      SDL_Renderer *, SDL_Window *);
void drawInSpaceTime(particle_t *, unsigned char,
                     double, double, double, double,
                     SDL_Renderer *, SDL_Window *);

void sketch(void (*drawingFunction)(particle_t *, unsigned char,
                                    double, double, double, double,
                                    SDL_Renderer *, SDL_Window *),
            universe *, unsigned char, SDL_Renderer *, SDL_Window *);


#endif
