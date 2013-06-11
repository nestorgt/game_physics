// RK4 implementation

#include <stdio.h>
#include <math.h>

// current location and velocity
struct State
{
	float x;	// position
	float v; 	// velocity
};

// derivative storage
struct Derivative
{	
	float dx;	// derivative of position: velocity
	float dv;	// derivative of velocity: acceleration
};

#define FORCE 10
#define MASS 1
// calculate acceleration for the current state at the time t + dt
float acceleration(const State &state, float t)
{
	const float k = FORCE;
	const float b = MASS;
	return - k * state.x - b * state.v;
}

// recalculate derivatives with new location (for first derivate)
Derivative evaluate(const State &initial, float t)
{
	Derivative output;
	output.dx = initial.v;
	output.dv = acceleration(initial, t);
	return output;
}

// advance the physics state and recalculate derivatives with new location
Derivative evaluate(const State &initial, float t, float dt, const Derivative &d)
{
	// state with new values, from t to t + dt
	State state;
	state.x = initial.x + d.dx * dt;
	state.v = initial.v + d.dv * dt;
	// recalculate the derivatives using new state
	Derivative output;
	output.dx = state.v;
	output.dv = acceleration(state, t + dt);

	return output;
}

// integrate the state ahead from t to t + dt using RK4
void integrate(State &state, float t, float dt)
{
	// RK4 samples derivates four times to detect curvature (Euler just once)
	// uses previous derivative to calculate the next one
	Derivative a = evaluate(state, t);
	Derivative b = evaluate(state, t, dt * 0.5f, a);
	Derivative c = evaluate(state, t, dt * 0.5f, b);
	Derivative d = evaluate(state, t, dt, c);
	// calculate best overall derivative using a weighted sum (Taylor series)
	const float dxdt = 1.0f/6.0f * (a.dx + 2.0f * (b.dx + c.dx) + d.dx);
	const float dvdt = 1.0f/6.0f * (a.dv + 2.0f * (b.dv + c.dv) + d.dv);
	// use previous derivative to advance the position and velocity over dt
	state.x = state.x + dxdt * dt;
	state.v = state.v + dvdt * dt;
}

int main()
{
	// create a state
	State state;
	state.x = 1000;	// position
	state.v = 0;	// velocity
	
	float t = 0;
	float dt = 0.1f;
	
	// loop until loc=0 & v=0
	while (fabs(state.x) > 0.001f || fabs(state.v) > 0.001f)
	{
		printf("x=%.2f, v=%.2f, t=%.2f, dt=%.2f\n", state.x, state.v, t, dt);
		integrate(state, t, dt);
		t += dt;
	}

	//getc(stdin);
	return 0;
}