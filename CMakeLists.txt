cmake_minimum_required(VERSION 3.16)
project(3DsMIN)

set(CMAKE_CXX_STANDARD 14)

if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_definitions(-DDM_DEBUG_MOD=1)
endif (CMAKE_BUILD_TYPE STREQUAL "Debug")

FILE(COPY res DESTINATION "${CMAKE_BINARY_DIR}")
FILE(COPY res/imgui.ini DESTINATION "${CMAKE_BINARY_DIR}")

include_directories(.)
include_directories(src)
include_directories(vendor/GLFW/include)
include_directories(vendor/glm)
include_directories(vendor/glew/include)
include_directories(vendor/imgui)
include_directories(vendor/imgui/backends)
include_directories(vendor/stb_image)
include_directories(vendor/stl_reader)

add_subdirectory(vendor/GLFW)
add_subdirectory(vendor/glm)

find_library(OPENGL_LIBRARY NAMES OpenGL.framework OpenGL opengl32)

add_executable(3DsMIN
        main.cpp
        src/Event/Event.cpp
        src/tests/TestTexture.cpp
        vendor/glew/src/glew.c
        vendor/imgui/backends/imgui_impl_glfw.cpp
        vendor/imgui/backends/imgui_impl_opengl3.cpp
        vendor/imgui/imgui.cpp
        vendor/imgui/imgui_draw.cpp
        vendor/imgui/imgui_widgets.cpp
        src/Camera/Camera.cpp
        src/Entity/CubeObject.cpp
        src/Renderer/IndexBuffer.cpp
        src/Renderer/Renderer.cpp
        src/Renderer/ShaderManager.cpp
        src/Renderer/Texture.cpp
        src/Renderer/VertexArray.cpp
        src/Renderer/VertexBuffer.cpp
        src/Window/Window.cpp
        src/ImGui/ImGuiUI.cpp
        src/Renderer/Framebuffer.cpp
        src/Entity/EntityManager.cpp
        src/Entity/Axises.cpp
        src/Entity/Grid.cpp
        src/Helper/MeshLoader.cpp
        src/Entity/Mesh.cpp
        src/Renderer/Log.cpp
        src/Debug/Debug.cpp
        src/Application.cpp)

target_link_libraries(3DsMIN glfw)
target_link_libraries(3DsMIN ${OPENGL_LIBRARY})
