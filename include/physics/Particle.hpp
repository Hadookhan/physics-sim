#pragma once
#include <glm/vec2.hpp>
#include <vector>

#include "physics/PhysicsBody.hpp"

#include "data/State.hpp"

// Particle definition: a particle to be generated in space
// It has a current position x, velocity v, force F, and mass m.

struct Particle : public PhysicsBody
{
};

glm::vec2 calcGravityForce(Particle& p, float gravity);
glm::vec2 calcHorizontalForce(float horizontalForce);
glm::vec2 calcDragForce(Particle& p, float dragCoeff);

void updateProjectile(std::vector<Particle>& particles, float particleMass, const glm::vec2& velocity, const glm::vec2& pos, glm::vec2 force, SimulationState& state);
void renderParticles(const std::vector<Particle>& particles, SimulationState& state);
void resetProjectile(Particle& p, glm::vec2 position, glm::vec2 velocity, float mass);