// RK4 implementation

#include <stdio.h>
#include <math.h>

struct State
{
	float x;	// position
	float v; 	// velocity
};

struct Derivative
{	
	float dx;	// derivative of position: velocity
	float dv;	// derivative of velocity: acceleration
};


