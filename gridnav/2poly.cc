// © 2013 the Search Authors under the MIT license. See AUTHORS for the list of authors.

#include "gridmap.hpp"
#include "../visnav/polymap.hpp"
#include <cstdio>

int main(int argc, char *argv[]) {
	GridMap map(stdin);
	bool *blkd = new bool[map.sz];
	for (unsigned int i = 0; i < map.sz; i++)
		blkd[i] = true;
	for (unsigned int i = 0; i < map.w; i++) {
		unsigned int base = i * map.w;

		for (unsigned int j = 0; j < map.h; j++)
			blkd[base + j] = map.blkd(map.index(i, j));
	}

	PolyMap polys(blkd, map.w, map.h);
	polys.output(stdout);

	return 0;
}