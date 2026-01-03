#ifndef PSO_H
#define PSO_H

#include "structures.h"
#include <stdlib.h>
#include <stdio.h>

//get signal strength at position pos
double get_signal(map *mp, vector *pos);

//calculate new speed and position
void next_iteration(particle *ptcl, double w, double c1, double c2, double r1, double r2);

void save_state(particle *partictles, int p, FILE *out);

#endif