#include "physics/Integrator.hpp"
#include "physics/PhysicsBody.hpp"

void integrateEuler(PhysicsBody& body, float dt)
{
    glm::vec2 acceleration = body.force / body.mass;

    // Using eulers numerical method to approx a physical bodies velocity and position at the next time interval
    body.velocity += acceleration * dt;
    body.position += body.velocity * dt;

    body.force = glm::vec2(0.0f);
}

void integrateRK2(PhysicsBody& body, float dt)
{
    float step = 0.5f;

    glm::vec2 acceleration = body.force / body.mass;

    glm::vec2 midVelocity = body.velocity + acceleration * (dt*step);
    // glm::vec2 midPosition = body.position + body.velocity * (dt*step);

    body.position += midVelocity * dt;
    body.velocity += acceleration * dt;

    body.force = glm::vec2(0.0f);

}