// C++
#include <iostream>
#include <fstream>
#include <vector>
#include "src/collatz.h"
#include "external/implot/implot.h"
#include "external/imgui/imgui.h"
#include "external/imgui/imgui_impl_glfw.h"
#include "external/imgui/imgui_impl_opengl3.h"
#include <GLFW/glfw3.h>

constexpr int MAX_NUMBER = 1000;

void exportCSV(const std::vector<std::pair<int,int>>& data) {
    std::ofstream csvFile("../scatter_data.csv");
    if (!csvFile) {
        std::cerr << "Error opening CSV file for writing.\n";
        return;
    }
    csvFile << "Number,Iterations\n";
    for (const auto&[fst, snd] : data)
        csvFile << fst << "," << snd << "\n";
    csvFile.close();
    std::cout << "CSV export successful.\n";
}

int main(int argc, char* argv[]) {
    if (!glfwInit())
        return 1;

    GLFWwindow* window = glfwCreateWindow(1280, 720, "Collatz Visualization", nullptr, nullptr);
    if (!window) {
        glfwTerminate();
        return 1;
    }

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImPlot::CreateContext();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 130");

    for (int number = 1; number <= MAX_NUMBER; ++number) {
        CollatzData::collatz_iterations(number);
    }

    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        ImGui::SetNextWindowPos(ImVec2(0, 0));
        ImGui::SetNextWindowSize(ImGui::GetIO().DisplaySize);
        ImGui::Begin("Collatz Conjecture Visualization", nullptr,
            ImGuiWindowFlags_NoTitleBar |
            ImGuiWindowFlags_NoResize |
            ImGuiWindowFlags_NoMove |
            ImGuiWindowFlags_NoScrollbar |
            ImGuiWindowFlags_NoScrollWithMouse);

        if (ImPlot::BeginPlot("Collatz Iterations")) {
            const auto& data = CollatzData::get_iteration_data();
            std::vector<float> numbers;
            std::vector<float> iterations;
            for (const auto& [n, iter] : data) {
                numbers.push_back(static_cast<float>(n));
                iterations.push_back(static_cast<float>(iter));
            }
            ImPlot::SetupAxes("Number", "Iterations");
            ImPlot::PushStyleVar(ImPlotStyleVar_MarkerSize, 2.0f);
            ImPlot::PlotScatter("Steps to reach 1", numbers.data(), iterations.data(), static_cast<int>(numbers.size()));
            ImPlot::PopStyleVar();
            ImPlot::EndPlot();
        }

        // Add a button to export CSV when clicked.
        if (ImGui::Button("Export CSV")) {
            exportCSV(CollatzData::get_iteration_data());
        }

        ImGui::End();

        ImGui::Render();
        int display_w;
        int display_h;
        glfwGetFramebufferSize(window, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
        glClearColor(0.45f, 0.55f, 0.60f, 1.00f);
        glClear(GL_COLOR_BUFFER_BIT);
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