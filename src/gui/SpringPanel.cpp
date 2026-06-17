#include <glm/vec2.hpp>

#include "data/State.hpp"

#include "gui/SpringPanel.hpp"

#include "physics/Spring.hpp"

#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"
#include "imgui.h"

void SpringPanel::createPanel(SpringMass& springMass, Spring& spring, SimulationState& state)
{
    ImGui::SliderFloat("Spring stiffness", &spring.stiffness, 0.1f, 50.0f);
    ImGui::SliderFloat("Spring damping", &spring.damping, 0.0f, 5.0f);
    ImGui::SliderFloat("Rest length", &spring.restLength, 0.1f, 1.0f);
    ImGui::SliderFloat("Spring mass", &springMass.mass, 0.1f, 20.0f);
    ImGui::Checkbox("Enable Gravity", &state.useGravity);

    if (state.useGravity)
    {
        ImGui::SliderFloat("Gravity", &state.gravity, -10.0f, 0.0f);
    }

    if (ImGui::Button("Reset Spring"))
    {
        springMass.position = state.initPos;
        springMass.velocity = glm::vec2(0.0f, 0.0f);
        springMass.force = glm::vec2(0.0f);
        state.elapsed = 0.0f;
        state.logTimer = 0.0f;
    }
}