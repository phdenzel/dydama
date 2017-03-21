/*
 * ic.c
 *
 * @author: phdenzel
 *
 * Initial conditions for DYDAMA
 *
 */

#include "ic.h"

#include "world.h" // particle_t, universe
#include "graphics.h" // linearMap

#include <stdlib.h>
#include <assert.h>


double randomDouble(double vmin, double vmax) {
  return (double)rand()/RAND_MAX * (vmax-vmin) + vmin;
  
}

int createNatural(universe *u, unsigned char D, double N) {
  // initialize a universe with N particles in D dimensions
  u->N = N;
  u->D = D;
  u->L = 1;
  u->T = 1;
  u->M = 1;
  u->G = 0.004;

  return 0;
  
}

int createSolarSystem(universe *u) {
  // initialize a universe with 9 particles in 3D similiar to our solar system
  u->N = 10;
  u->D = 3;
  u->L = 149597870700; // m = 1 AU
  u->T = 86400; // sec = 1 day //  A.D. = 2454543.5 
  u->M = 1.988435E+30; // kg = 1 Msol
  u->G = 0.0002959122; // k ~ 0.01720209895;

  return 0;
  
}

int ic_1D2DMP(universe *u) {
  // initialize two particles at arbitrary positions
  assert(u->D == 1);
  assert(u->N == 2);

  // allocate space
  u->particles = malloc(u->N * sizeof(particle_t));
  assert(u->particles != NULL);

  // first particle
  init_particleProperties(&u->particles[0], 1, 1, "dm");
  set_particleRVA(&u->particles[0], 1, 0.25, 0, 0);
  set_particleRVA(&u->particles[0], 2, 0, 0, 0);
  set_particleRVA(&u->particles[0], 3, 0, 0, 0);
  // second particle
  init_particleProperties(&u->particles[1], 1, 1, "dm");
  set_particleRVA(&u->particles[1], 1, 0.75, 0, 0);
  set_particleRVA(&u->particles[1], 2, 0, 0, 0);
  set_particleRVA(&u->particles[1], 3, 0, 0, 0);

  set_totalMass(u);
    
  return 0;
  
}

int ic_1D5DMP(universe *u) {
  // initialize five particles at arbitrary positions
  assert(u->D == 1);
  assert(u->N == 5);

  // allocate space
  u->particles = malloc(u->N * sizeof(particle_t));
  assert(u->particles != NULL);
  
  // first particle
  init_particleProperties(&u->particles[0], 1, 1, "dm");
  set_particleRVA(&u->particles[0], 1, 0.00, 0, 0);
  set_particleRVA(&u->particles[0], 2, 0, 0, 0);
  set_particleRVA(&u->particles[0], 3, 0, 0, 0);
  // second particle
  init_particleProperties(&u->particles[1], 1, 1, "dm");
  set_particleRVA(&u->particles[1], 1, 0.25, 0, 0);
  set_particleRVA(&u->particles[1], 2, 0, 0, 0);
  set_particleRVA(&u->particles[1], 3, 0, 0, 0);
  // third particle
  init_particleProperties(&u->particles[2], 1, 1, "dm");
  set_particleRVA(&u->particles[2], 1, 0.50, 0, 0);
  set_particleRVA(&u->particles[2], 2, 0, 0, 0);
  set_particleRVA(&u->particles[2], 3, 0, 0, 0);
  // fourth particle
  init_particleProperties(&u->particles[3], 1, 1, "dm");
  set_particleRVA(&u->particles[3], 1, 0.75, 0, 0);
  set_particleRVA(&u->particles[3], 2, 0, 0, 0);
  set_particleRVA(&u->particles[3], 3, 0, 0, 0);
  // fifth particle
  init_particleProperties(&u->particles[4], 1, 1, "dm");
  set_particleRVA(&u->particles[4], 1, 1.00, 0, 0);
  set_particleRVA(&u->particles[4], 2, 0, 0, 0);
  set_particleRVA(&u->particles[4], 3, 0, 0, 0);

  set_totalMass(u);
  
  return 0;
  
}

int ic_1DAlignment(universe *u, double mass, double size,
                     double rmin, double rmax) {
  // initialize particles evely spaced along the x-coordinate
  assert(u->D == 1);
  assert(u->N > 0);

  // allocate space
  u->particles = malloc(u->N * sizeof(particle_t));
  assert(u->particles != NULL);

  // initialize all particles evenly spaced between rmin and rmax
  int N = u->N;
  double proj = 0;
  for (int i = 0; i < N; i++) {
    proj = linearMap(i, 0, N, rmin, rmax);
    init_particleProperties(&u->particles[i], mass, size, "dm");
    set_particleRVA(&u->particles[i], 1, proj, 0, 0);
    set_particleRVA(&u->particles[i], 2, 0, 0, 0);
    set_particleRVA(&u->particles[i], 3, 0, 0, 0);
  }
  set_totalMass(u);
  
  return 0;
  
};

int ic_1DRandAlignment(universe *u, double mass, double size,
                       double rmin, double rmax) {
  // initialize particles evenly spaced along the x-coordinate
  // with small random initial velocity
  assert(u->D == 1);
  assert(u->N > 0);

  // allocate space
  u->particles = malloc(u->N * sizeof(particle_t));
  assert(u->particles != NULL);

  // initialize all particles evenly spaced between rmin and rmax
  double proj = 0;
  for (int i = 0; i < u->N; i++) {
    proj = linearMap(i, 0, u->N, rmin, rmax);
    init_particleProperties(&u->particles[i], mass, size, "dm");
    set_particleRVA(&u->particles[i], 1, proj, randomDouble(-0.05, 0.05), 0); // x
    set_particleRVA(&u->particles[i], 2, 0, 0, 0); // y
    set_particleRVA(&u->particles[i], 3, 0, 0, 0); // z
  }
  set_totalMass(u);
  
  return 0;
  
}

int ic_1DRandDMStar(universe *u, int numberOfStars,
                double star_mass, double star_size,
                double dm_mass, double dm_size,
                double rmin, double rmax) {
  // initialize particles (dm+star) evenly spaced along the x-coordinate
  // with small random initial velocity
  // # of dm particles = N - numberOfStars
  assert(u->D == 1);
  assert(u->N > 0);

  // allocate space
  u->particles = malloc(u->N * sizeof(particle_t));
  assert(u->particles != NULL);

  // initialize all particles evenly spaced between rmin and rmax
  int nos = 0; // number of stars already placed
  double proj;
  double ratio = ((double)numberOfStars)/u->N;
  printf("Ratio: %lf", ratio);
  double randm;
  for (int i = 0; i < u->N; i++) {
    proj = linearMap(i, 0, u->N, rmin, rmax);
    randm = randomDouble(0, 1);
    if (nos < numberOfStars && randm < ratio) {
      init_particleProperties(&u->particles[i], star_mass, star_size, "star");
      set_particleRVA(&u->particles[i], 1, proj, randomDouble(-0.05, 0.05), 0);
      set_particleRVA(&u->particles[i], 2, 0, 0, 0);
      set_particleRVA(&u->particles[i], 3, 0, 0, 0);
      ++nos;
    } else {
      init_particleProperties(&u->particles[i], dm_mass, dm_size, "dm");
      set_particleRVA(&u->particles[i], 1, proj, randomDouble(-0.05, 0.05), 0);
      set_particleRVA(&u->particles[i], 2, 0, 0, 0);
      set_particleRVA(&u->particles[i], 3, 0, 0, 0);
    }
  }
  set_totalMass(u);
  
  return 0;
  
}


int ic_SolarSystem(universe *u) {
  // initialize particles in the solar system
  // state of date = 18.03.08 00:00:00
  assert(u->D == 3);
  assert(u->N > 9);

  double msol = 1.0;
  double ssize = 10.0;

  // allocate space
  u->particles = malloc(u->N * sizeof(particle_t));
  assert(u->particles != NULL);

  // initialize particles in solar system
  // Star
  init_particleProperties(&u->particles[0], msol, ssize,
                          "star");
  set_particleR(&u->particles[0],
                -3.402962055191472E-04,
                 4.973801475460748E-03,
                -6.230136454608636E-05);
  set_particleV(&u->particles[0],
                -6.477668621023070E-06,
                -1.292580409219799E-07,
                 1.154585032962209E-07);
  set_particleA(&u->particles[0], 0, 0, 0);

  // Planet - Mercury
  init_particleProperties(&u->particles[1], msol/6023600, ssize*0.25,
                          "mercury");
  set_particleR(&u->particles[1],
                 3.704735169720974E-02,
                -4.529211095852149E-01,
                -4.090255306376755E-02);
  set_particleV(&u->particles[1],
                 2.239183874467135E-02,
                 3.736008439029809E-03,
                -1.750026916388115E-03);
  set_particleA(&u->particles[1], 0, 0, 0);

  // Planet - Venus
  init_particleProperties(&u->particles[2], msol/408523.61, ssize*0.25,
                          "venus");
  set_particleR(&u->particles[2],
                 4.272157290820016E-01,
                -5.835752726996720E-01,
                -3.279422047835795E-02);
  set_particleV(&u->particles[2],
                 1.622328987696207E-02,
                 1.181629954076840E-02,
                -7.748242818668279E-04);
  set_particleA(&u->particles[2], 0, 0, 0);

  // Planet - Earth
  init_particleProperties(&u->particles[3], msol/332946.050895, ssize*0.25,
                          "earth");
  set_particleR(&u->particles[3],
                -9.948486972722731E-01,
                 4.564231864395614E-02,
                -6.099525188647536E-05);
  set_particleV(&u->particles[3],
                -9.901408163678924E-04,
                -1.725450198017297E-02,
                 4.346241632445323E-07);
  set_particleA(&u->particles[3], 0, 0, 0);

  // Planet - Mars
  init_particleProperties(&u->particles[4], msol/3098708, ssize*0.25,
                          "mars");
  set_particleR(&u->particles[4],
                -1.093539305796724E+00,
                 1.240381444357973E+00,
                 5.266905384900308E-02);
  set_particleV(&u->particles[4],
                -9.958470942542191E-03,
                -8.082316351751016E-03,
                7.520708651107539E-05);
  set_particleA(&u->particles[4], 0, 0, 0);

  // Planet - Jupiter
  init_particleProperties(&u->particles[5], msol/1047.3486, ssize*0.5,
                          "jupiter");
  set_particleR(&u->particles[5],
                 7.199075962861715E-01,
                -5.164765414047316E+00,
                 5.281301305052329E-03);
  set_particleV(&u->particles[5],
                 7.380707839356994E-03,
                 1.399344086177555E-03,
                -1.710023430451413E-04);
  set_particleA(&u->particles[5], 0, 0, 0);

  // Planet - Saturn
  init_particleProperties(&u->particles[6], msol/3497.898, ssize*0.5,
                          "saturn");
  set_particleR(&u->particles[6],
                -8.469664737705321E+00,
                 3.804527121928150E+00,
                 2.708474727487031E-01);
  set_particleV(&u->particles[6],
                -2.583089539225567E-03,
                -5.101976771205786E-03,
                 1.915567842416982E-04);
  set_particleA(&u->particles[6], 0, 0, 0);

  // Planet - Uranus
  init_particleProperties(&u->particles[7], msol/22902.98, ssize*0.4,
                          "uranus");
  set_particleR(&u->particles[7],
                 1.970001443062262E+01,
                -3.956376098536538E+00,
                -2.699288868040702E-01);
  set_particleV(&u->particles[7],
                 7.457402740600397E-04,
                 3.672797797089092E-03,
                 3.988780204062304E-06);
  set_particleA(&u->particles[7], 0, 0, 0);

  // Planet - Neptun
  init_particleProperties(&u->particles[8], msol/19412.24, ssize*0.4,
                          "neptun");
  set_particleR(&u->particles[8],
                 2.361441531200179E+01,
                -1.856288724958460E+01,
                -1.619425696998957E-01);
  set_particleV(&u->particles[8],
                 1.919278314221217E-03,
                 2.486348363416270E-03,
                -9.543324154983418E-05);
  set_particleA(&u->particles[8], 0, 0, 0);

  // Planet - Pluto
  init_particleProperties(&u->particles[9], msol/135200000, ssize*0.25,
                          "pluto");
  set_particleR(&u->particles[9],
                -4.656585770964581E-01,
                -3.123136435608064E+01,
                 3.476634650132539E+00);
  set_particleV(&u->particles[9],
                 3.195935187090267E-03,
                -6.368370346118488E-04,
                -8.563102596919757E-04);
  set_particleA(&u->particles[9], 0, 0, 0);
  
  return 0;
  
}
