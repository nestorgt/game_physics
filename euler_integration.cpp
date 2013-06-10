#include <stdio.h>
#include <math.h>

int main () 
{
    float t = 0;
    float dt = 1;

    float acceleration = 0;
    float velocity = 0;
    float position = 0;
    float force = 10;
    float mass = 1;
    
    while ( t <= 10 )
    {
        // acceleration = force divided by mass
        acceleration = force / mass;
        // change in position = velocity times delta time
        position = position + velocity * dt;
        // change in velocity = acceleration times delta time
        velocity = velocity + acceleration * dt;
        t = t + dt;
        
        printf("velocity=%2.f, position=%2.f, t=%2.f, dt=%2.f \n",velocity,position,t,dt);
    }
    
    return 0;
}