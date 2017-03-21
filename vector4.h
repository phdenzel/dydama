/*
 * vector4.h
 *
 * @author: phdenzel
 *
 * A geometrical and physical 4-vector struct of type double
 *
 */

#ifndef VECTOR4_H
#define VECTOR4_H

// Macros
#define vector4_create(v, vec) vector4_t v; \
    vector4_init(&v); vector4_set(&v, vec)
#define VECTOR4_CREATE(v, vec) \
  vector4_create(v, vec)
#define VECTOR4_SET(v, vec) \
  vector4_set(&v, vec)
#define VECTOR4_SETINDEX(v, i, val) \
  vector_setIndex(&v, i, val)
#define VECTOR4_GET(v, i) \
  vector4_get(&v, i)
#define VECTOR4_PRINT(v) \
  vector4_print(&v)
#define VECTOR4_INCREASE(v, s) \
  vector4_increase(&v, s)
#define VECTOR4_INCREASECPY(v, s) \
  vector4_increasecpy(&v, s)
#define VECTOR4_SCALE(v, s) \
  vector4_scale(&v, s)
#define VECTOR4_SCALECPY(v, s) \
  vector4_scalecpy(&v, s)
#define VECTOR4_LENGTH(v) \
  vector4_length(&v)
#define VECTOR4_LENGTH2(v) \
  vector4_length2(&v)
#define VECTOR4_NORMALIZE(v) \
  vector4_normalize(&v)
#define VECTOR4_NOMRALIZECPY(v) \
  vector4_normalizecpy(&v)
#define VECTOR4_ADD(v1, v2) \
  vector4_add(&v1, &v2)
#define VECTOR4_ADDCPY(v1, v2) \
  vector4_addcpy(&v1, &v2)
#define VECTOR4_SUBTRACT(v1, v2) \
  vector4_subtract(&v1, &v2)
#define VECTOR4_SUBTRACTCPY(v1, v2) \
  vector4_subtractcpy(&v1, &v2)


typedef struct vector4 {
  double t;
  double x;
  double y;
  double z;

} vector4_t;


void vector4_init(vector4_t *);
void vector4_set(vector4_t *, double, double, double, double);
void vector4_setIndex(vector4_t *, int, double);
double vector4_get(vector4_t *, int);
void vector4_print(vector4_t *);
double vector4_length(vector4_t *);
double vector4_length2(vector4_t *);
void vector4_increase(vector4_t *, double);
vector4_t vector4_increasecpy(vector4_t *, double);
void vector4_scale(vector4_t *, double);
vector4_t vector4_scalecpy(vector4_t *, double);
void vector4_normalize(vector4_t *);
vector4_t vector4_normalizecpy(vector4_t *);
void vector4_add(vector4_t *, vector4_t *);
vector4_t vector4_addcpy(vector4_t *, vector4_t *);
void vector4_subtract(vector4_t *, vector4_t *);
vector4_t vector4_subtractcpy(vector4_t *, vector4_t *);
double vector4_dist(vector4_t *, vector4_t *);
double vector4_dist2(vector4_t *, vector4_t *);


#endif
