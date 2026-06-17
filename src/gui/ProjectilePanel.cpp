#include <glm/vec2.hpp>

#include "data/State.hpp"

#include "gui/ProjectilePanel.hpp"

#include "physics/Particle.hpp"

#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"
#include "imgui.h"

void ProjectilePanel::createPanel(std::vector<Particle>& particles, SimulationState& state)
{
    ImGui::SliderFloat("Gravity", &state.gravity, -10.0f, 0.0f);
    ImGui::SliderFloat("Mass", &state.particleMass, 0.1f, 10.0f);
    ImGui::SliderFloat("Horizontal force", &state.horizontalForce, -10.0f, 10.0f);
    ImGui::Checkbox("Enable Drag", &state.useDrag);

    if (state.useDrag)
    {
        ImGui::SliderFloat("Drag", &state.dragCoeff, 0.0f, 1.0f);
    }

    if (ImGui::Button("Reset Particle"))
    {
        particles[0].position = state.initPos;
        particles[0].velocity = state.initVel;
        particles[0].force = glm::vec2(state.initForce);
        particles[0].mass = state.particleMass;
        state.elapsed = 0.0f;
        state.logTimer = 0.0f;
    }
}