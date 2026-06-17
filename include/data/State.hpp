#pragma once

struct SimulationState
{
    float dt;

    float xPos;
    float yPos;
    float xVel;
    float yVel;
    float initForce;

    float gravity;
    float dragCoeff;
    float horizontalForce;

    bool useDrag;
    bool useGravity;

    bool showVelocityVector;
    bool showForceVector;
};