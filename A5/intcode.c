#include <stdio.h>
#include <stdlib.h>
#include "aux.c"

int main() 
{
	int R[12];
	int MEM[65536];

	MEM[0] = -11;
	mprn(MEM, 0);

	R[1] = MEM[0];
	R[2] = 8 - R[1];
	MEM[1] = R[2];
	mprn(MEM, 1);

	R[0] = MEM[0];
	R[2] = R[0] - 1;
	MEM[2] = R[2];
	mprn(MEM, 2);

	R[0] = MEM[2];
	R[2] = R[0] / 3;
	MEM[2] = R[2];
	mprn(MEM, 2);

	R[0] = MEM[0];
	MEM[3] = R[0];
	mprn(MEM, 3);

	R[0] = MEM[0];
	R[2] = pwr(R[0], 2);
	R[0] = MEM[1];
	R[3] = pwr(R[0], 2);
	R[0] = MEM[2];
	R[4] = pwr(R[0], 2);
	R[0] = MEM[3];
	R[1] = MEM[2];
	R[5] = R[0] - R[1];
	R[0] = MEM[1];
	R[5] = R[0] * R[5];
	R[0] = MEM[3];
	R[1] = MEM[2];
	R[6] = R[0] * R[1];
	R[5] = R[5] - R[6];
	R[5] = 2 * R[5];
	R[4] = R[4] + R[5];
	R[3] = R[3] + R[4];
	R[2] = R[2] + R[3];
	R[0] = MEM[2];
	R[3] = pwr(R[0], 2);
	R[2] = R[2] / R[3];
	eprn(R, 2);

	exit(0);
}
