#include <GLFW/glfw3.h>
#include <glm/vec2.hpp>
#include <glm/geometric.hpp>

#include "physics/Spring.hpp"

void updateSpringMass(SpringMass& mass, const Spring& spring, float dt, float gravity, bool useGravity)
{
    glm::vec2 displacement = mass.position - spring.anchor;
    float length = glm::length(displacement); // sqrt(x^2 + y^2)

    if (length == 0.0f) return;

    glm::vec2 direction = displacement / length;

    float extension = length - spring.restLength;

    // Hookes Law:
    glm::vec2 springForce =
        -spring.stiffness * extension * direction;

    glm::vec2 dampingForce =
        -spring.damping * mass.velocity;

    mass.force += springForce + dampingForce;

    if (useGravity)
    {
        mass.force += mass.mass * glm::vec2(0.0f, gravity); // Makes spring system obey gravity
    }

    // Eulers integration method on massed spring:
    glm::vec2 acceleration = mass.force / mass.mass;

    mass.velocity += acceleration * dt; // v=u+at
    mass.position += mass.velocity * dt; // x_{n+1} = x_n + vt

    mass.force = glm::vec2(0.0f);
}

void renderSpringMass(const SpringMass& mass, const Spring& spring)
{
    glBegin(GL_LINES);
    glVertex2f(spring.anchor.x, spring.anchor.y);
    glVertex2f(mass.position.x, mass.position.y);
    glEnd();

    glPointSize(12.0f);
    glBegin(GL_POINTS);
    glVertex2f(mass.position.x, mass.position.y);
    glEnd();
}