/*
 * vector4.c
 *
 * @author: phdenzel
 *
 * A geometrical and physical 4-vector struct of type double
 *
 */

#include "vector4.h"

#include <stdio.h>
#include <math.h>


void vector4_init(vector4_t *v) {
  // initialize 4-vector v
  v->t = v->z = v->y = v->x = 0;

}

void vector4_set(vector4_t *v, double t, double x, double y, double z) {
  // set the 4-vector with array a (0->t  1->x  2->y  3->z)
  v->t = t;
  v->x = x;
  v->y = y;
  v->z = z;

}

void vector4_setIndex(vector4_t *v, int index, double value) {
  // set index of the 4-vector v to value
  switch (index) {
  case 0: v->t = value; break;
  case 1: v->x = value; break;
  case 2: v->y = value; break;
  case 3: v->z = value; break;
  }

}

double vector4_get(vector4_t *v, int index) {
  // get index of 4-vector v
  switch (index) {
  case 0: return v->t; break;
  case 1: return v->x; break;
  case 2: return v->y; break;
  case 3: return v->z; break;
  }
  return 0;

}

void vector4_print(vector4_t *v) {
  // print the 4-vector v
  for (int i=0; i < 4; i++) {
    printf("%lf ", vector4_get(v, i));
  }
  printf("\n");

}

double vector4_length2(vector4_t *v) {
  // get the squared spatial length of the 4-vector v
  return v->x*v->x + v->y*v->y + v->z*v->z;

}

double vector4_length(vector4_t *v) {
  // get the spatial length of the 4-vector v
  return sqrt(v->x*v->x + v->y*v->y + v->z*v->z);

}

void vector4_increase(vector4_t *v, double scalar) {
  // increase every element of the spatial part of a 4-vector
  v->x += scalar;
  v->y += scalar;
  v->z += scalar;

}

vector4_t vector4_increasecpy(vector4_t *v, double scalar) {
  // increase every element of the spatial part of a 4-vector
  // return a cpoy of the increasing's result
  vector4_t increased;
  increased.t = v->t;
  increased.x = v->x + scalar;
  increased.y = v->y + scalar;
  increased.z = v->z + scalar;
  return increased;

}

void vector4_scale(vector4_t *v, double scalar) {
  // scale the spatial part of the 4-vector v w/ a scalar
  v->x *= scalar;
  v->y *= scalar;
  v->z *= scalar;

}

vector4_t vector4_scalecpy(vector4_t *v, double scalar) {
  // scale the spatial part of the 4-vector v w/ a scalar
  // return a copy of the scaling's result
  vector4_t scaled;
  scaled.t = v->t;
  scaled.x = v->x*scalar;
  scaled.y = v->y*scalar;
  scaled.z = v->z*scalar;
  return scaled;

}

void vector4_normalize(vector4_t *v) {
  // normalize the spatial part of the 4-vector v
  double invl = 1/vector4_length(v);
  v->x *= invl;
  v->y *= invl;
  v->z *= invl;

}

vector4_t vector4_normalizecpy(vector4_t *v) {
  // normalize the spatial part of the 4-vector v
  // return a copy of the normalization's result
  vector4_t n;
  double invl = 1/vector4_length(v);
  n.t = v->t;
  n.x = v->x*invl;
  n.y = v->y*invl;
  n.z = v->z*invl;
  return n;

}

void vector4_add(vector4_t *v1, vector4_t *v2) {
  // add the spatial part of 4-vector v2 to v1
  v1->x += v2->x;
  v1->y += v2->y;
  v1->z += v2->z;

}

vector4_t vector4_addcpy(vector4_t *v1, vector4_t *v2) {
  // add the spatial part of two 4-vectors v1, v2
  // return a copy of the addition's result
  vector4_t v;
  v.t = v1->t; // only spatial addition is of interest
  v.x = v1->x+v2->x;
  v.y = v1->y+v2->y;
  v.z = v1->z+v2->z;
  return v;

}

void vector4_subtract(vector4_t *v1, vector4_t *v2) {
  // add the spatial part of 4-vector v2 to v1
  v1->x -= v2->x;
  v1->y -= v2->y;
  v1->z -= v2->z;

}

vector4_t vector4_subtractcpy(vector4_t *v1, vector4_t *v2) {
  // add the spatial part of two 4-vectors v1, v2
  // return a copy of the addition's result
  vector4_t v;
  v.t = v2->t; // only spatial addition is of interest
  v.x = v2->x-v1->x;
  v.y = v2->y-v1->y;
  v.z = v2->z-v1->z;
  return v;

}

double vector4_dist(vector4_t *v1, vector4_t *v2) {
  // calculate the absolute distance between v1 and v2
  vector4_t v = vector4_subtractcpy(v1, v2);
  return sqrt(v.x*v.x + v.y*v.y + v.z*v.z);
  
}

double vector4_dist2(vector4_t *v1, vector4_t *v2) {
  // calculate the absolute squared distance between v1 and v2
  vector4_t v = vector4_subtractcpy(v1, v2);
  return v.x*v.x + v.y*v.y + v.z*v.z;
  
}
