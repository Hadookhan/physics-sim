#pragma once
#include "Particle.hpp"

void integrateEuler(Particle& particle, float dt);
void integrateRK2(Particle& particle, float dt);