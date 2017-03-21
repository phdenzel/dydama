/*
 * dydama.c
 *
 * @author: phdenzel
 *
 * DYDAMA - For simulating the DYnamics of DArk MAtter
 *
 */

#include "dydama.h"

#include "world.h"
#include "ic.h"
#include "sort.h"
#include "vector4.h"
#include "graphics.h"

#include <stdio.h>
#include <assert.h>
#include <SDL2/SDL.h>


void printParticles(universe *u) {
  // print r, v, and a vectors of the particles
  for (int i = 0; i < u->N; i++) {
    printf("Particle %d  -  ", i);
    printf("%s\n", u->particles[i].type);
    printf("s: %lf\n", u->particles[i].size);
    printf("m: %lf\n", u->particles[i].m);
    printf("x: "); vector4_print(&u->particles[i].r);
    printf("v: "); vector4_print(&u->particles[i].v);
    printf("a: "); vector4_print(&u->particles[i].a);
  }
  
}

void printTotalMomentum(universe *u, unsigned char dimension) {
  // print the total momentum of all particles
  int i;
  double p = 0;
  switch (dimension) {
  case 1: {
    for (i = 0; i < u->N; i++) {
      p += u->particles[i].v.x*u->particles[i].m;
    }
  } break;
  case 2: {
    for (i = 0; i < u->N; i++) {
      p += u->particles[i].v.y*u->particles[i].m;
    }
  } break;
  case 3: {
    for (i = 0; i < u->N; i++) {
      p += u->particles[i].v.z*u->particles[i].m;
    }
  } break;
  }
  
  printf("Total momentum: %lf\n", p);
  
}


/* MAIN ********************************************************************* */
int main(void/* int argc, char *argv[] */) {
  
  /* Universe ***** */

  // TODO: use options instead
  universe world;
  createNatural(&world, 1, 20000); // 1D w/ 3000 particles
  world.dt = 0.01;  // time resolution
  //createSolarSystem(&world); // 3D w/ 10 celestial bodies
  //world.dt = 7;
  
  //set_projection(&world, -35.0, 35.0, 35.0, -35.0);
  set_projection(&world, -0.5, 1.5, 10, -10);

  /* Initial Conditions ***** */
  
  //world.N = 2;
  //ic_1D2DMP(&world);
  //world.N = 5;
  //ic_1D5DMP(&world);
  //ic_1DAlignment(&world, 1, 1, 0, 1);
  //ic_1DRandDMStar(&world, 1, 100, 5, 1, 1, 0, 1);
  ic_1DRandAlignment(&world, 1, 1, 0, 1);
  //ic_SolarSystem(&world);

  long particleMem = sizeof(particle_t)*world.N;
  long paramMem = 10*sizeof(double)+sizeof(char)+sizeof(int);
  printf("Allocated memory for particles:\n\t%ld = %.3lf MB\n",
         particleMem, particleMem*1.e-6);
  printf("Allocated memory for parameters:\n\t%ld = %.3lf MB\n",
         paramMem, paramMem*1.e-6);
  printf("Total allocated memory:\n\t%ld = %.3lf MB\n",
         (paramMem+particleMem), (paramMem+particleMem)*1.e-6);
  
# if 1
  
  /* Graphics ***** */

  SDL_Window *window;
  SDL_Renderer *renderer;
  int W = 1080;
  int H = 720;

  SDL_Init(SDL_INIT_VIDEO);
  window = SDL_CreateWindow("DYDAMA",
                            SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                            W, H,
                            0);
  renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
  
  /* Runtime Loop ***** */

  int is_running = 1;

  while(is_running) {
    // check for termination
    is_running = processEvents(window, is_running);

    // simulation step
    evolveFast(&world);
    //evolve(&world);
    
    // draw world
    resetBg(renderer);
    sketch(drawInPhaseSpace, &world, 1, renderer, window);
    //sketch(drawInRealSpace, &world, 2, renderer, window);
    
    // Log
    // printTotalMomentum(&world, 1);
    
    // have mercy on CPU
    SDL_RenderPresent(renderer);
    SDL_Delay(1);
    
  }

  SDL_DestroyWindow(window);
  SDL_DestroyRenderer(renderer);
  SDL_Quit();

#endif

  free(world.particles);
  
  return 0;

  
}
