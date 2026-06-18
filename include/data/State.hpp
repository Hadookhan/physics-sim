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

    bool isStatic;

    float particleMass;

    float elapsed;
    float logTimer;

    float G;
    float orbitVelocity;
    bool showOrbitLine;

    glm::vec2 chargePos1;
    glm::vec2 chargePos2;
};