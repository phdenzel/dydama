/*
 * sort.h
 *
 * @author: phdenzel
 *
 * Quicksort algorithms for DYAMA
 *
 */

#ifndef SORT_H
#define SORT_H

#include "world.h"


//void swap(universe *, int, int);
void swapP(particle_t *, particle_t *);
void swap(universe *, int, int);
int xpartition(universe *, int, int);
int ypartition(universe *, int, int);
int zpartition(universe *, int, int);
void xQuickSort(universe *, int, int);
void yQuickSort(universe *, int, int);
void zQuickSort(universe *, int, int);


#endif
