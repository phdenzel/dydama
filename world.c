/*
 * world.c
 *
 * @author: phdenzel
 *
 * DYDAMA universe properties
 *
 */

#include "world.h"

#include "sort.h"

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>


void init_particleProperties(particle_t *p, double m, double size, char* type) {
  // initialize particle properties
  p->m = m;
  p->size = size;
  p->type = type;
  
}

void set_particleRVA(particle_t *p, int dimension,
                     double x, double v, double a) {
  // initialize particle position/velocity/acceleration in dimension
  vector4_setIndex(&p->r, dimension, x);
  vector4_setIndex(&p->v, dimension, v);
  vector4_setIndex(&p->a, dimension, a);
  
}

void set_particleR(particle_t *p, double x, double y, double z) {
  // set the particles position r
  vector4_set(&p->r, 0, x, y, z);
  
}

void set_particleV(particle_t *p, double vx, double vy, double vz) {
  // set the particles velocity v
  vector4_set(&p->v, 0, vx, vy, vz);
  
}

void set_particleA(particle_t *p, double ax, double ay, double az) {
  // set the particles acceleration a
  vector4_set(&p->a, 0, ax, ay, az);
  
}

void set_totalMass(universe *u) {
  // set the total mass parameter of u
  assert(u->N > 0 || u->particles != NULL);
  double totalMass = 0;
  for (int i = 0; i < u->N; i++) {
    totalMass += u->particles[i].m;
  }
  u->Mtot = totalMass;
  
}

void set_projection(universe *u,
                    double xmin, double xmax, double ymin, double ymax) {
  // set the projection parameters of u
  u->proj[0] = xmin;
  u->proj[1] = xmax;
  u->proj[2] = ymin;
  u->proj[3] = ymax;
  
}

inline int sgn(double val) {
  return (val > 0) - (val < 0);
  
}

inline void gForceUpdate(universe *u) {
  // calculate gravitational force and update particle accelerations
  double G = u->G;
  switch (u->D) {
  case 1: { // 1D gravity
    int this, other;
    double a, this_x;
#pragma omp simd
    for (this = 0; this < u->N; this++) {
      u->particles[this].a.x = 0;
    }
#pragma omp simd
    for (this = 0; this < u->N-1; this++) {
      this_x = u->particles[this].r.x;
      for (other = this+1; other < u->N; other++) {
        // copysign seems to be faster than the sgn function
        a = G * copysign(1, u->particles[other].r.x - this_x);
        u->particles[this].a.x += a*u->particles[other].m;
        u->particles[other].a.x -= a*u->particles[this].m;
      }
    }
  } break;
  case 2: { // 2D gravity
    printf("2D gravity not yet implemented!\n");
  } break;
  case 3: { // 3D gravity
    int this, other;
    // reset forces
    for (this = 0; this < u->N; this++) {
      vector4_set(&u->particles[this].a, 0, 0, 0, 0);
    }
    double n;
    vector4_t r;
    #pragma omp simd
    for (this = 0; this < u->N-1; this++) {
      for (other = this+1; other < u->N; other++) {
        r = vector4_subtractcpy(&u->particles[this].r, &u->particles[other].r);
        n = 1./vector4_length(&r);
        n = n*n*n;
        n *= u->G;
        vector4_scale(&r, n*u->particles[other].m);
        vector4_add(&u->particles[this].a, &r);
        vector4_scale(&r, -1*u->particles[this].m/u->particles[other].m);
        vector4_add(&u->particles[other].a, &r);
      }
    }
  } break;
  }

}

inline void gForceFast(universe *u) {
  // sort the particles first and then calculate accelerations
  // only possible if particle masses are all equal
  double G = u->G;
  switch (u->D) {
  case 1: { // 1D gravity
    int i;
    double Meff = u->Mtot;
    xQuickSort(u, 0, u->N-1);
#pragma omp simd
    for (i = 0; i < u->N/2; i++) {
      Meff -= u->particles[i].m;
      u->particles[i].a.x = G*Meff;
      u->particles[u->N-i-1].a.x = -G*Meff;
      Meff -= u->particles[i].m;
    }
  } break;
  case 2: { // 2D gravity
    printf("2D gravity not yet implemented!\n");
  } break;
  case 3: { // 3D gravity
    printf("3D gravity not yet implemented!\n");
  } break;
  }
  
}



void drift(particle_t *p, double dt, unsigned char dimensions) {
  // perform a drift step for particle p of amount dt
  switch (dimensions) {
  case 1: { // 1D x-coordinate drift
    p->r.x += p->v.x * dt;
  } break;
  case 2: { // 2D x and y-coordinate drift
    p->r.x += p->v.x * dt;
    p->r.y += p->v.y * dt;
    //vector4_t vdt = vector4_scalecpy(&p->v, dt);
    //p->r = vector4_addcpy(&p->r, &vdt);
  } break;
  case 3: { // full 3D drift
    vector4_t vdt = vector4_scalecpy(&p->v, dt);
    vector4_add(&p->r, &vdt);
  } break;
  }
  
}

void kick(particle_t *p, double dt, unsigned char dimensions) {
  // perform a drift step for particle p of amount dt
  switch (dimensions) {
  case 1: { // 1D x-coordinate drift
    p->v.x += p->a.x * dt;
  } break;
  case 2: { // 2D x and y-coordinate drift
    p->v.x += p->a.x * dt;
    p->v.y += p->a.y * dt;
    //vector4_t adt = vector4_scalecpy(&p->a, dt);
    //p->v = vector4_addcpy(&p->v, &adt);
  } break;
  case 3: { // full 3D drift
    vector4_t adt = vector4_scalecpy(&p->a, dt);
    vector4_add(&p->v, &adt);
  } break;
  }
  
}

void drift_halfStep(universe *u) {
  // perform a half drift step for all particles in universe u
  for (int i = 0; i < u->N; i++) {
    drift(&u->particles[i], u->dt/2, u->D);
  }

}

void kick_fullStep(universe *u) {
  // perform a full kick step of all particles in universe u
  for (int i = 0; i < u->N; i++) {
    kick(&u->particles[i], u->dt, u->D);
  }

}

inline void evolve(universe *u) {
  // perform a leap frog step for all particles in universe u
  drift_halfStep(u);
  gForceUpdate(u);
  kick_fullStep(u);
  drift_halfStep(u);

}

inline void evolveFast(universe *u) {
  // perform a leap frog step with improved force calculation
  drift_halfStep(u);
  gForceFast(u);
  kick_fullStep(u);
  drift_halfStep(u);
  
}
