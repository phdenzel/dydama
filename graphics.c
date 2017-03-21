/*
 * graphics.c
 *
 * @author: phdenzel
 *
 * Graphics components of DYDAMA
 *
 */

#include "graphics.h"

#include "world.h"

#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <SDL2/SDL.h>


pcolor_t DMCOLOR =     { 61, 170, 119, 255};
pcolor_t STARCOLOR =   {253, 183,  96, 255};
pcolor_t BGCOLOR_L =   { 42,  47,  56, 255};
pcolor_t BGCOLOR_D =   { 22,  26,  32, 255};
pcolor_t EARTHCOLOR =  { 61, 170, 119, 255};
pcolor_t ICYPCOLOR_L = {112, 191, 255, 255};
pcolor_t ICYPCOLOR_D = { 95, 138, 247, 255};
pcolor_t GASPCOLOR_L = {234, 227, 183, 255};
pcolor_t GASPCOLOR_D = {201, 190, 168, 255};
pcolor_t DUSTPCOLOR_L ={222, 175, 122, 255};
pcolor_t DUSTPCOLOR_D ={222,  68,  21, 255};


double linearMap(double v, double A, double B, double a, double b) {
  // linearly map a value in [A, B] -> [a, b]
  return (v-A)*(b-a)/(B-A) + a;
  
}

void SDL_RenderFillCircle(SDL_Renderer *rend, int x0, int y0, int radius) {
  // Uses the midpoint circle algorithm to draw a filled
  int x = radius;
  int y = 0;
  int radiusError = 1 - x;
  while (x >= y) {
    SDL_RenderDrawLine(rend,  x + x0,  y + y0, -x + x0,  y + y0);
    SDL_RenderDrawLine(rend,  y + x0,  x + y0, -y + x0,  x + y0);
    SDL_RenderDrawLine(rend, -x + x0, -y + y0,  x + x0, -y + y0);
    SDL_RenderDrawLine(rend, -y + x0, -x + y0,  y + x0, -x + y0);
    y++;
    if (radiusError < 0)
      radiusError += 2 * y + 1;
    else {
      x--;
      radiusError += 2 * (y - x + 1);
    }
  }
}

int processEvents(SDL_Window *window, int is_running) {
  // close in certain situations
  SDL_Event event;
  while(SDL_PollEvent(&event)) {
    switch (event.type) {
    case SDL_WINDOWEVENT_CLOSE: {
      if (window) {
        SDL_DestroyWindow(window);
        window = NULL;
        is_running = 0;
      }
    } break;
    case SDL_QUIT: {
      is_running = 0;
    } break;   
    }
  }
  
  return is_running;
  
}

void resetBg(SDL_Renderer *renderer) {
  SDL_SetRenderDrawColor(renderer, BGCOLOR_L.r, BGCOLOR_L.g, BGCOLOR_L.b,
                         BGCOLOR_L.alpha);
  SDL_RenderClear(renderer);
  
}

void drawInRealSpace(particle_t *p, unsigned char dimensions,
                     double xmin, double xmax, double ymin, double ymax,
                     SDL_Renderer *renderer, SDL_Window *window) {
  // draw the particle p in dimensions as points with color r,g,b
  assert(dimensions == 1 || dimensions == 2 || dimensions == 3);
  // choose color depending on particle
  pcolor_t c;
  if (!strcmp("dm", p->type)) {
    c = DMCOLOR;
  } else if (!strcmp("star", p->type)) {
    c = STARCOLOR;
  } else if (!strcmp("mercury", p->type) || !strcmp("mars", p->type) || \
             !strcmp("pluto", p->type)) {
    c = DUSTPCOLOR_L;
  } else if (!strcmp("venus", p->type)) {
    c = DUSTPCOLOR_D;
  } else if (!strcmp("earth", p->type)) {
    c = EARTHCOLOR;
  } else if (!strcmp("jupiter", p->type)) {
    c = GASPCOLOR_L;
  } else if (!strcmp("saturn", p->type)) {
    c = GASPCOLOR_D;
  } else if (!strcmp("uranus", p->type)) {
    c = ICYPCOLOR_L;
  } else if (!strcmp("neptun", p->type)) {
    c = ICYPCOLOR_D;
  } else {
    c.r = 222; c.g = 222; c.b = 222; c.alpha = 255;
  }
  SDL_SetRenderDrawColor(renderer, c.r, c.g, c.b, c.alpha);
  // get window size
  int w;
  int h;
  SDL_GetWindowSize(window, &w, &h);
  // projection
  double xproj = 0;
  double yproj = 0;
  switch (dimensions) {
  case 1: {
    xproj = linearMap(p->r.x, xmin, xmax, 0, w);
    yproj = h/2;
  } break;
  case 2: {
    xproj = linearMap(p->r.x, xmin, xmax, 0, w);
    yproj = linearMap(p->r.y, ymin, ymax, 0, h);
  } break;
  case 3: {
    printf("3D particle drawing - not yet implemented!\n");
  } break;
  }
  SDL_RenderFillCircle(renderer, xproj, yproj, p->size);
  
}

void drawInPhaseSpace(particle_t *p, unsigned char dimension,
                      double xmin, double xmax, double ymin, double ymax,
                      SDL_Renderer *renderer, SDL_Window *window) {
  // draw the particle p in the dimension as point with color r,g,b
  assert(dimension == 1 || dimension == 2 || dimension == 3);
  // choose color depending on particle
  pcolor_t c;
  if (!strcmp("dm", p->type)) {
    c = DMCOLOR;
  } else if (!strcmp("star", p->type)) {
    c = STARCOLOR;
  } else {
    c.r = 222; c.g = 222; c.b = 222; c.alpha = 255;
  }
  SDL_SetRenderDrawColor(renderer, c.r, c.g, c.b, c.alpha);
  // get window size
  int w;
  int h;
  SDL_GetWindowSize(window, &w, &h);
  // projection
  double xproj = 0;
  double yproj = 0;
  switch (dimension) {
  case 1: {
    xproj = linearMap(p->r.x, xmin, xmax, 0, w);
    yproj = linearMap(p->v.x, ymin, ymax, 0, h);
  } break;
  case 2: {
    xproj = linearMap(p->r.y, xmin, xmax, 0, w);
    yproj = linearMap(p->v.y, ymin, ymax, 0, h);
  } break;
  case 3: {
    xproj = linearMap(p->r.z, xmin, xmax, 0, w);
    yproj = linearMap(p->v.z, ymin, ymax, 0, h);
  } break;
  }
  SDL_RenderFillCircle(renderer, xproj, yproj, p->size);
  
}

void drawInSpaceTime(particle_t *p, unsigned char dimension,
                     double xmin, double xmax, double ymin, double ymax,
                     SDL_Renderer *renderer, SDL_Window *window) {
  // draw the particle p in spacetime dimenion as point with color r,g,b
  assert(dimension == 1 || dimension == 2 || dimension == 3);
  // choose color depending on particle
  pcolor_t c;
  if (!strcmp("dm", p->type)) {
    c = DMCOLOR;
  } else if (!strcmp("star", p->type)) {
    c = STARCOLOR;
  } else if (!strcmp("mercury", p->type) || !strcmp("mars", p->type) || \
             !strcmp("pluto", p->type)) {
    c = DUSTPCOLOR_L;
  } else if (!strcmp("venus", p->type)) {
    c = DUSTPCOLOR_D;
  } else if (!strcmp("earth", p->type)) {
    c = EARTHCOLOR;
  } else if (!strcmp("jupiter", p->type)) {
    c = GASPCOLOR_L;
  } else if (!strcmp("saturn", p->type)) {
    c = GASPCOLOR_D;
  } else if (!strcmp("uranus", p->type)) {
    c = ICYPCOLOR_L;
  } else if (!strcmp("neptun", p->type)) {
    c = ICYPCOLOR_D;
  } else {
    c.r = 222; c.g = 222; c.b = 222; c.alpha = 255;
  }
  SDL_SetRenderDrawColor(renderer, c.r, c.g, c.b, c.alpha);
  // get window size
  int w;
  int h;
  SDL_GetWindowSize(window, &w, &h);
  // projection
  double xproj = 0;
  double yproj = 0;
  xproj = linearMap(p->r.t, xmin, xmax, 0, w);
  switch (dimension) {
  case 1: {
    yproj = linearMap(p->r.x, ymin, ymax, 0, h);
  } break;
  case 2: {
    yproj = linearMap(p->r.y, ymin, ymax, 0, h);
  } break;
  case 3: {
    yproj = linearMap(p->r.z, ymin, ymax, 0, h);
  } break;
  }
  SDL_RenderFillCircle(renderer, xproj, yproj, p->size);
  
}

void sketch(void (*drawingFunction)(particle_t *, unsigned char,
                                    double, double, double, double,
                                    SDL_Renderer *, SDL_Window *),
            universe *u, unsigned char dimensionality,
            SDL_Renderer *renderer, SDL_Window *window) {
  // draw the entire universe
  double xmin, xmax, ymin, ymax;
  xmin = u->proj[0];
  xmax = u->proj[1];
  ymin = u->proj[2];
  ymax = u->proj[3];
  for (int i=0; i < u->N; i++) {
    drawingFunction(&u->particles[i], dimensionality,
                    xmin, xmax, ymin, ymax,
                    renderer, window);
  }
  
}
