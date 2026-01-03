#include "pso.h"


double
get_signal(map *mp, vector *pos) {
	return mp->signal[pos->x*mp->size->x + pos->y];
}

void
next_iteration(particle *ptcl, double w, double c1, double c2, double r1, double r2) {

	//the equation goes here

	if (ptcl->nxt != NULL)
		next_iteration(ptcl -> nxt, w, c1, c2, r1, r2);
}

void save_state(particle *particles, int p, FILE *out) {
	int i;
	for (i=0;i<p;i++)
		fprintf(out, "Particle %d: %d, %d\n", i+1, particles -> position -> x, particles -> position -> y);
}