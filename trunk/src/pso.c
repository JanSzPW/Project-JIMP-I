#include "pso.h"


double
get_signal(map *mp, vector *pos) {
	return mp->signal[(int)pos->x*(int)mp->size->x + (int)pos->y];
}

void
next_iteration(particle *ptcl, double w, double c1, double c2, double r1, double r2, map *mp) {
	double s;

	//the equation goes here

	if ((s = get_signal(mp, ptcl -> position)) > ptcl -> p_best -> val) {
		printf("New p best %lf for particle %d\n", s, &ptcl);
		ptcl -> p_best -> val = s;
		ptcl -> p_best -> x = ptcl -> position -> x;
		ptcl -> p_best -> y = ptcl -> position -> y;
	}
	if (s > mp -> g_best -> val) {
		printf("New global best %lf\n", s);
		mp -> g_best -> val = s;
		mp -> g_best -> x = ptcl -> position -> x;
		mp -> g_best -> y = ptcl -> position -> y;
	}

	if (ptcl->nxt != NULL)
		next_iteration(ptcl -> nxt, w, c1, c2, r1, r2, mp);
}

void save_state(particle *particles, int p, FILE *out) {
	int i;
	for (i=0;i<p;i++) {
		fprintf(out, "Particle %d: %lf, %lf\n", i+1, particles -> position -> x, particles -> position -> y);
		particles = particles->nxt;
	}
}