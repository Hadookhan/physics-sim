#include "data/State.hpp"

#include "gui/StatePanel.hpp"

#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"
#include "imgui.h"

void StatePanel::createPanel(SimulationState& state)
{
    ImGui::Begin("Initial Conditions");

    ImGui::SliderFloat("Time step", &state.dt, 0.001f, 0.05f);
    ImGui::SliderFloat("X position", &state.initPos.x, -1.0f, 1.0f);
    ImGui::SliderFloat("Y position", &state.initPos.y, -1.0f, 1.0f);
    ImGui::SliderFloat("X velocity", &state.initVel.x, 0.0f, 1.0f);
    ImGui::SliderFloat("Y velocity", &state.initVel.y, 0.0f, 1.0f);
    ImGui::Checkbox("Show Velocity", &state.showVelocityVector);
    ImGui::Checkbox("Show Force", &state.showForceVector);

    ImGui::End();
}