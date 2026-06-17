#pragma once
#include "Particle.hpp"
#include "physics/PhysicsBody.hpp"

void integrateEuler(PhysicsBody& body, float dt);
void integrateRK2(PhysicsBody& body, float dt);