/*
 * ic.h
 *
 * @author: phdenzel
 *
 * Initial conditions for DYDAMA
 *
 */

#ifndef IC_H
#define IC_H

#include "world.h"


double randomDouble(double, double);
int createNatural(universe *, unsigned char, double);
int createSolarSystem(universe *);
int ic_1D2DMP(universe *);
int ic_1D5DMP(universe *);
int ic_1DAlignment(universe *, double, double, double, double);
int ic_1DRandAlignment(universe *, double, double, double, double);
int ic_1DRandDMStar(universe *, int, double, double, double ,double,
                    double, double);
int ic_SolarSystem(universe *);


#endif
