/*
 * world.h
 *
 * @author: phdenzel
 *
 * DYDAMA universe properties
 *
 */

#ifndef WORLD_H
#define WORLD_H

#include "vector4.h"


typedef struct particle {
  vector4_t r;    // spatial position
  vector4_t v;    // velocity
  vector4_t a;    // acceleration
  double m;       // mass
  double size;    // size
  char* type;     // name: 'dm' or 'star'
  
} particle_t;

typedef struct universe {
  particle_t *particles; // particle list
  int N;                 // number of particles
  unsigned char D;       // number of dimenions
  double G;              // gravity constant
  double L;              // length scale
  double T;              // time scale
  double M;              // mass scale
  double Mtot;           // total system mass
  double dt;             // time steps
  double proj[4];        // projection
  
} universe;


void init_particleProperties(particle_t *, double, double, char*);
void set_particleRVA(particle_t *, int, double, double, double);
void set_particleR(particle_t *, double, double, double);
void set_particleV(particle_t *, double, double, double);
void set_particleA(particle_t *, double, double, double);
void set_projection(universe *, double, double, double, double);
void set_totalMass(universe *);
int sgn(double);
void gForceUpdate(universe *);
void gForceFast(universe *);
void drift(particle_t *, double, unsigned char);
void kick(particle_t *, double, unsigned char);
void drift_halfStep(universe *);
void kick_fullStep(universe *);
void evolve(universe *);
void evolveFast(universe *);

#endif
