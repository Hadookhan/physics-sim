#include <iostream>
#include <vector>

#include <GLFW/glfw3.h>
#include <glm/vec2.hpp>

#include "data/CSVLogger.hpp"
#include "data/State.hpp"

#include "gui/StatePanel.hpp"
#include "gui/SpringPanel.hpp"
#include "gui/ProjectilePanel.hpp"
#include "gui/OrbitPanel.hpp"

#include "physics/Particle.hpp"
#include "physics/Integrator.hpp"
#include "physics/Spring.hpp"
#include "physics/Orbit.hpp"

#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"
#include "imgui.h"

int main()
{
    std::vector<Particle> particles;

    float dt = 0.0001f;
    float totalTime = 0.0f;
    float logTimer = 0.0f;
    const float logInterval = 1.0f; // Logs will be made every time logTimer = logInterval

    float gravity = -0.5f;
    float particleMass = 1.0f;
    float horizontalForce = 1.0f;
    float dragCoeff = 0.5f;

    float G = 0.01f; // gravitational constant
    float orbitVelocity = 1.0f;
    bool showOrbitLine = true;

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
    bool isStatic = false;

    SimulationState state{
        dt,
        glm::vec2(init_X_pos, init_Y_pos),
        glm::vec2(init_X_velo, init_Y_velo),
        init_F,
        gravity,
        dragCoeff,
        horizontalForce,
        useDrag,
        useGravity,
        showVelocityVector,
        showForceVector,
        isStatic,
        particleMass,
        totalTime,
        logTimer,
        G,
        orbitVelocity,
        showOrbitLine
    };

    // All panels which will be rendered in the GUI
    StatePanel statePanel;
    ProjectilePanel projectilePanel;
    SpringPanel springPanel;
    OrbitPanel orbitPanel;

    // Spring system initialisation
    SpringMass springMass{
        state.initPos,
        state.initVel,
        glm::vec2(state.initForce),
        glm::vec2(0.0f),
        10.0f
    };

    Spring spring{
        anchor,
        restLength,
        stiffness,
        damping
    };

    OrbitBody central{
        glm::vec2(0.0f, 0.0f),
        glm::vec2(0.0f),
        glm::vec2(0.0f),
        glm::vec2(0.0f),
        100.0f,
        true
    };

    OrbitBody satellite{
        glm::vec2(0.6f, 0.0f),
        glm::vec2(0.0f, 1.29f),
        glm::vec2(0.0f),
        glm::vec2(0.0f),
        1.0f,
        false
    };

    OrbitSystem orbitSystem{
        central,
        satellite,
        state.G
    };

    // Using this section to log data to respective csv files:
    CSVLogger particleLogger("data/Particle.csv");
    particleLogger.writeParticleHeader();
    CSVLogger springLogger("data/Spring.csv");
    springLogger.writeSpringHeader();
    CSVLogger orbitLogger("data/Orbit.csv");
    orbitLogger.writeOrbitHeader();

    enum class SimMode
    {
        Projectile,
        Spring,
        Orbit
    };

    SimMode mode = SimMode::Projectile;


    // First vec = position, second vec = velocity, third vec = force, float represents force.
    // These are the initial conditions to the equation F=ma
    particles.push_back({
        state.initPos, // (x pos, y pos)
        state.initVel, // (x velo, y velo)
        glm::vec2(state.initForce),
        glm::vec2(0.0f), // net force
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
        glClear(GL_COLOR_BUFFER_BIT);

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        // Creates panel of initial states which the user can toggle
        statePanel.createPanel(state);

        ImGui::Begin("Simulation Controls");

        if (ImGui::Button("Projectile"))
        {
            mode = SimMode::Projectile;
        }

        if (ImGui::Button("Spring"))
        {
            mode = SimMode::Spring;
        }
        if (ImGui::Button("Orbit"))
        {
            mode = SimMode::Orbit;
        }

        if (mode == SimMode::Projectile)
        {

            // Adds projectile toggles to simulation controls panel
            projectilePanel.createPanel(particles, state);

            updateProjectile(particles, state);
            renderParticles(particles, state);

            state.elapsed += state.dt;
            state.logTimer += state.dt;

            if (state.logTimer >= logInterval)
            {
                particleLogger.logParticle(state.elapsed, particles[0]);
                state.logTimer = 0.0f;
            }
        }
        else if (mode == SimMode::Spring)
        {
            // Adds spring toggles to simulation controls panel
            springPanel.createPanel(springMass, spring, state);

            updateSpringMass(springMass, spring, state);
            renderSpringMass(springMass, spring, state);

            state.elapsed += state.dt;
            state.logTimer += state.dt;

            if (state.logTimer >= logInterval)
            {
                springLogger.logSpring(state.elapsed, springMass);
                state.logTimer = 0.0f;
            }
        }
        else if (mode == SimMode::Orbit)
        {
            orbitPanel.createPanel(orbitSystem, state);

            orbitSystem.G = state.G;

            updateOrbit(orbitSystem, state);
            renderOrbit(orbitSystem, state);

            state.elapsed += state.dt;
            state.logTimer += state.dt;

            if (state.logTimer >= logInterval)
            {
                orbitLogger.logOrbit(state.elapsed, orbitSystem);
                state.logTimer = 0.0f;
            }
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