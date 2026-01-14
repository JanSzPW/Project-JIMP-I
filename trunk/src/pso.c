#include "pso.h"


//get signal at a specific location
double
get_signal(map *mp, vector *pos) {
	if (pos->x < 0 || pos->y < 0 || pos->x>mp -> size->x || pos->y > mp->size->y)
	return mp->signal[(int)pos->x*(int)mp->size->x + (int)pos->y];
}

//update state of the swarm
void
next_iteration(particle *ptcl, double w, double c1, double c2, double r1, double r2, map *mp) {
	double s;

	//random r1 and r2 - don't quite understand why they are in the config file
	r1 = (double)rand()/RAND_MAX;
	r2 = (double)rand()/RAND_MAX;

	//the equation goes here
	ptcl -> velocity -> x = w * ptcl->velocity->x + c1*r1 * (ptcl->p_best->x - ptcl->position->x) + c2*r2 * (mp->g_best->x - ptcl->position->x);
	ptcl -> velocity -> y = w * ptcl->velocity->y + c1*r1 * (ptcl->p_best->y - ptcl->position->y) + c2*r2 * (mp->g_best->y - ptcl->position->y);
	double p = ptcl -> position -> x;
	ptcl -> position -> x = p + ptcl->velocity->x;
	p = ptcl->position->y;
	ptcl -> position -> y = p + ptcl->velocity->y;

	//update personal best
	if ((s = get_signal(mp, ptcl -> position)) > ptcl -> p_best -> val) {
		// printf("New p best %lf for particle %d\n", s, &ptcl);
		ptcl -> p_best -> val = s;
		ptcl -> p_best -> x = ptcl -> position -> x;
		ptcl -> p_best -> y = ptcl -> position -> y;
	}
	//update global best
	if (s > mp -> g_best -> val) {
		printf("New global best %lf\n", s);
		mp -> g_best -> val = s;
		mp -> g_best -> x = ptcl -> position -> x;
		mp -> g_best -> y = ptcl -> position -> y;
	}

	//call on the next particle
	if (ptcl->nxt != NULL)
		next_iteration(ptcl -> nxt, w, c1, c2, r1, r2, mp);
}

//save current state of the swarm
void save_state(particle *particles, int p, FILE *out, double size_x, double size_y) {
	int i;
	//opening line of an svg
    fprintf(out, "<svg width=\"800\" height=\"800\" fill=\"none\">\n");
	//every particle's position
	for (i=0;i<p;i++) {
		// fprintf(out, "Particle %d: %lf, %lf\n", i+1, particles -> position -> x, particles -> position -> y);
		fprintf(out, "\t<circle cx=\"%d\" cy=\"%d\" r=\"3\" fill=\"black\" />\n", (int)(particles -> position -> x * 800 / size_x), (int)(particles -> position -> y * 800 / size_y));
		particles = particles->nxt;
	}
	fprintf(out, "</svg>");
}