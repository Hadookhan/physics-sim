#include "physics/Integrator.hpp"

void integrateEuler(Particle& particle, float dt)
{
    glm::vec2 acceleration = particle.force / particle.mass;

    // Using eulers numerical method to approx a particles velocity and position at the next time interval
    particle.velocity += acceleration * dt;
    particle.position += particle.velocity * dt;

    particle.force = glm::vec2(0.0f);
}

void integrateRK2(Particle& particle, float dt)
{
    float step = 0.5f;

    glm::vec2 acceleration = particle.force / particle.mass;

    glm::vec2 midVelocity = particle.velocity + acceleration * (dt*step);
    glm::vec2 midPosition = particle.position + particle.velocity * (dt*step);

    particle.position += midVelocity * dt;
    particle.velocity += acceleration * dt;

    particle.force = glm::vec2(0.0f);

}