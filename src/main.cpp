#include <iostream>
#include <vector>

#include <GLFW/glfw3.h>
#include <glm/vec2.hpp>

#include "physics/Particle.hpp"
#include "physics/Integrator.hpp"
#include "physics/Spring.hpp"

#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"
#include "imgui.h"

int main()
{
    std::vector<Particle> particles;
    float dt = 0.016f;
    float gravity = -0.5f;
    float particleMass = 1.0f;
    float horizontalForce = 1.0f;
    float dragCoeff = 0.5f;

    float init_X_velo = 0.2f;
    float init_Y_velo = 0.7f;
    float init_X_pos = 0.0f;
    float init_Y_pos = 0.2f;
    float init_F = 0.0f;

    glm::vec2 anchor = glm::vec2(0.0f, 0.6f);
    float restLength = 0.4f;
    float stiffness = 5.0f;
    float damping = 0.5f;

    bool useGravity = true;
    bool useDrag = true;
    bool showVelocityVector = false;
    bool showForceVector = false;

    SpringMass springMass{
        glm::vec2(init_X_pos,init_Y_pos),
        glm::vec2(init_X_velo, init_Y_velo),
        glm::vec2(init_F),
        10.0f
    };

    Spring spring{
        anchor,
        restLength,
        stiffness,
        damping
    };

    enum class SimMode
    {
        Projectile,
        Spring
    };

    SimMode mode = SimMode::Projectile;


    // First vec = position, second vec = velocity, third vec = force, float represents force.
    // These are the initial conditions to the equation F=ma
    particles.push_back({
        glm::vec2(init_X_pos, init_Y_pos), // (x pos, y pos)
        glm::vec2(init_X_velo, init_Y_velo), // (x velo, y velo)
        glm::vec2(init_F),
        glm::vec2(0.0f),
        particleMass
    });

    if (!glfwInit())
    {
        std::cerr << "Failed to initialise GLFW\n";
        return -1;
    }

    GLFWwindow* window = glfwCreateWindow(
        1800,
        1000,
        "Physics Sim",
        nullptr,
        nullptr
    );

    if (!window)
    {
        std::cerr << "Failed to create window\n";
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    ImGui::CreateContext();

    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 130");

    glClearColor(0.05f, 0.05f, 0.08f, 1.0f);

    while (!glfwWindowShouldClose(window))
    {

        glfwPollEvents();

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        ImGui::Begin("Initial Conditions");

        ImGui::SliderFloat("Time step", &dt, 0.001f, 0.05f);
        ImGui::SliderFloat("X position", &init_X_pos, -1.0f, 1.0f);
        ImGui::SliderFloat("Y position", &init_Y_pos, -1.0f, 1.0f);
        ImGui::SliderFloat("X velocity", &init_X_velo, 0.0f, 1.0f);
        ImGui::SliderFloat("Y velocity", &init_Y_velo, 0.0f, 1.0f);
        ImGui::Checkbox("Show Velocity", &showVelocityVector);
        ImGui::Checkbox("Show Force", &showForceVector);

        ImGui::End();

        ImGui::Begin("Simulation Controls");

        if (ImGui::Button("Projectile"))
        {
            mode = SimMode::Projectile;
        }

        if (ImGui::Button("Spring"))
        {
            mode = SimMode::Spring;
        }

        if (mode == SimMode::Projectile)
        {
            ImGui::SliderFloat("Gravity", &gravity, -10.0f, 0.0f);
            ImGui::SliderFloat("Mass", &particleMass, 0.1f, 10.0f);
            ImGui::SliderFloat("Horizontal force", &horizontalForce, -10.0f, 10.0f);
            ImGui::Checkbox("Enable Drag", &useDrag);

            if (useDrag)
            {
                ImGui::SliderFloat("Drag", &dragCoeff, 0.0f, 1.0f);
            }

            if (ImGui::Button("Reset Particle"))
            {
                particles[0].position = glm::vec2(init_X_pos, init_Y_pos);
                particles[0].velocity = glm::vec2(init_X_velo, init_Y_velo);
                particles[0].force = glm::vec2(init_F);
                particles[0].mass = particleMass;
            }
            updateProjectile(particles, dt, gravity, horizontalForce, dragCoeff, particleMass, glm::vec2(init_X_velo, init_Y_velo), glm::vec2(init_X_pos, init_Y_pos), glm::vec2(init_F), useDrag);
            glClear(GL_COLOR_BUFFER_BIT);
            renderParticles(particles, showVelocityVector, showForceVector);
        }
        else if (mode == SimMode::Spring)
        {
            ImGui::SliderFloat("Spring stiffness", &spring.stiffness, 0.1f, 50.0f);
            ImGui::SliderFloat("Spring damping", &spring.damping, 0.0f, 5.0f);
            ImGui::SliderFloat("Rest length", &spring.restLength, 0.1f, 1.0f);
            ImGui::SliderFloat("Spring mass", &springMass.mass, 0.1f, 20.0f);
            ImGui::Checkbox("Enable Gravity", &useGravity);

            if (useGravity)
            {
                ImGui::SliderFloat("Gravity", &gravity, -10.0f, 0.0f);
            }

            if (ImGui::Button("Reset Spring"))
            {
                springMass.position = glm::vec2(init_X_pos, init_Y_pos);
                springMass.velocity = glm::vec2(0.0f, 0.0f);
                springMass.force = glm::vec2(0.0f);
            }

            updateSpringMass(springMass, spring, dt, gravity, useGravity);
            glClear(GL_COLOR_BUFFER_BIT);
            renderSpringMass(springMass, spring);
        }

        ImGui::End();

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window);
    }

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}