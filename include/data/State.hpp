#pragma once
#include <glm/vec2.hpp>

struct SimulationState
{
    float dt;

    glm::vec2 initPos;
    glm::vec2 initVel;
    float initForce;

    float gravity;
    float dragCoeff;
    float horizontalForce;

    bool useDrag;
    bool useGravity;

    bool showVelocityVector;
    bool showForceVector;

    float particleMass;

    float elapsed;
    float logTimer;
};