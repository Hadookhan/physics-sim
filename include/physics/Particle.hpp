#pragma once
#include <glm/vec2.hpp>
#include <vector>

// Particle definition: a particle to be generated in space
// It has a current position x, velocity v, force F, and mass m.

struct Particle
{
    glm::vec2 position;
    glm::vec2 velocity;
    glm::vec2 force;
    glm::vec2 netForce;
    float mass;
};

void updateProjectile(std::vector<Particle>& particles, float dt, float gravity, float horizontalForce, float dragCoeff, float particleMass, const glm::vec2& velocity, const glm::vec2& pos, glm::vec2 force, bool useDrag);
void renderParticles(const std::vector<Particle>& particles, bool showVelocityVector, bool showForceVector);
void resetProjectile(Particle& p, glm::vec2 position, glm::vec2 velocity, float mass);