#include "structures.h"
#include "readMap.h"

int main(int argc, char *argv[]) {

    FILE *in = fopen("FILENAME","r");

    map *main_map = readMap(in);


}