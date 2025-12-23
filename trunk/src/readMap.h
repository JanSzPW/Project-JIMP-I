#ifndef READ_MAP
#define READ_MAP

#include "structures.h"
#include <stdio.h>
#include <stdlib.h>

//create map based on file in
map *readMap(FILE *in);

void dropMap(map *mp);

#endif