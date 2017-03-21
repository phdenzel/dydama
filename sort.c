/*
 * sort.c
 *
 * @author: phdenzel
 *
 * Quicksort algorithms for DYAMA
 *
 * Parallel quicksort can cause bus error 10, because
 * some systems set the non-main stack size to < 1MB,
 * which is reached at N ~ 4096
 *
 */

#include "sort.h"

#include "world.h"


void swapP(particle_t *p1, particle_t *p2) {
  // swap particle pointers
  particle_t temp;
  temp = *p1;
  *p1 = *p2;
  *p2 = temp;
  
}

void swap(universe *u, int i, int j) {
  // swap elements i and j in particles
  particle_t temp;
  temp = u->particles[i];
  u->particles[i] = u->particles[j];
  u->particles[j] = temp;
  
}


int xpartition(universe *u, int left, int right) {
  // partition particles from left to right in x
  double pivot = u->particles[left].r.x;
  int i = left;
  int j = right+1;
  while (1) {
    do ++i; while (u->particles[i].r.x <= pivot && i <= right);
    do --j; while (u->particles[j].r.x > pivot);
    if (i >= j) break;
    swap(u, i, j);
  }
  swap(u, left, j);
  return j;
  
}

int ypartition(universe *u, int left, int right) {
  // partition particles from left to right in y
  double pivot = u->particles[left].r.y;
  int i = left;
  int j = right+1;
  while (1) {
    do ++i; while (u->particles[i].r.y <= pivot && i <= right);
    do --j; while (u->particles[j].r.y > pivot);
    if (i >= j) break;
    swap(u, i, j);
  }
  swap(u, left, j);
  return j;
  
}

int zpartition(universe *u, int left, int right) {
  // partition particles from left to right in y
  double pivot = u->particles[left].r.z;
  int i = left;
  int j = right+1;
  while (1) {
    do ++i; while (u->particles[i].r.z <= pivot && i <= right);
    do --j; while (u->particles[j].r.z > pivot);
    if (i >= j) break;
    swap(u, i, j);
  }
  swap(u, left, j);
  return j;
  
}

void xQuickSort(universe *u, int left, int right) {
  // sort particles quickly though
   int j;
   if (left < right) {
     // divide and conquer
     j = xpartition(u, left, right);
#pragma omp parallel sections
     {
#pragma omp section
       {
         xQuickSort(u, left, j-1);
       }
#pragma omp section
       {
         xQuickSort(u, j+1, right);
       }
     }
   }

}

void yQuickSort(universe *u, int left, int right) {
  // sort particles quickly though
   int j;
   if (left < right) {
     // divide and conquer
     j = ypartition(u, left, right);
     #pragma omp parallel sections
     {
#pragma omp section
       {
         yQuickSort(u, left, j-1);
       }
#pragma omp section
       {
         yQuickSort(u, j+1, right);
       }
     }
   }

}

void zQuickSort(universe *u, int left, int right) {
  // sort particles quickly though
   int j;
   if (left < right) {
     // divide and conquer
     j = zpartition(u, left, right);
     #pragma omp parallel sections
     {
#pragma omp section
       {
         zQuickSort(u, left, j-1);
       }
#pragma omp section
       {
         zQuickSort(u, j+1, right);
       }
     }
   }

}
