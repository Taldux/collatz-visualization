cmake_minimum_required(VERSION 3.30)
project(Collatz)

set(CMAKE_CXX_STANDARD 20)

# Define libraries directories
set(GLFW_DIR "C:/glfw/glfw-3.4.bin.WIN64") # Change this to your GLFW directory
set(IMGUI_DIR "${CMAKE_SOURCE_DIR}/external/imgui")
set(IMPLOT_DIR "${CMAKE_SOURCE_DIR}/external/implot")

# List ImGui source files including backends
set(IMGUI_SOURCES
        ${IMGUI_DIR}/imgui.cpp
        ${IMGUI_DIR}/imgui_demo.cpp
        ${IMGUI_DIR}/imgui_draw.cpp
        ${IMGUI_DIR}/imgui_tables.cpp
        ${IMGUI_DIR}/imgui_widgets.cpp
        ${IMGUI_DIR}/imgui_impl_glfw.cpp
        ${IMGUI_DIR}/imgui_impl_opengl3.cpp
)

# Use glob for ImPlot sources
file(GLOB IMPLOT_SOURCES ${IMPLOT_DIR}/*.cpp)

# Create executable with all required sources
add_executable(Collatz
        main.cpp
        src/collatz.cpp
        ${IMGUI_SOURCES}
        ${IMPLOT_SOURCES}
)

# Set include directories for GLFW, ImGui, ImPlot and our source files
target_include_directories(Collatz PRIVATE
        src
        ${IMGUI_DIR}
        ${IMGUI_DIR}/backends
        ${IMPLOT_DIR}
        ${GLFW_DIR}/include
)

# Find OpenGL package
find_package(OpenGL REQUIRED)

# Link libraries: OpenGL and GLFW (using the MinGW static library)
target_link_libraries(Collatz PRIVATE
        OpenGL::GL
        ${GLFW_DIR}/lib-mingw-w64/libglfw3.a
)