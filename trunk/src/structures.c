#include "structures.h"
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>


vector*
createVector(int x, int y) {
	vector *vec = malloc( sizeof(vector) );
	vec -> x = x;
	vec -> y = y;

	return vec;
}

void
dropVector(vector *v) {
	free(v);
}

particle*
createParticle(particle *tl, vector *map_size) {
	particle *ptcl = malloc( sizeof(particle) );
	ptcl -> position = createVector(rand()%map_size->x, rand()%map_size->y);
	ptcl -> velocity = createVector(0,0);
	ptcl -> p_best = createVector(ptcl -> position -> x, ptcl -> position -> y);

	return ptcl;
}

void
dropParticle(particle *p) {
	free(p->position);
	free(p->velocity);
	free(p->p_best);

	particle *tmp = p;
	p = p->nxt;

	free(tmp);
}


