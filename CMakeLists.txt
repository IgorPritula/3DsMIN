cmake_minimum_required(VERSION 3.16)
project(3DsMIN)

set(CMAKE_CXX_STANDARD 14)

FILE(COPY res DESTINATION "${CMAKE_BINARY_DIR}")

include_directories(.)
include_directories(vendor/GLFW/include)
include_directories(vendor/glm)
include_directories(vendor/glew/include)
include_directories(vendor/imgui)
include_directories(vendor/imgui/backends)
include_directories(vendor/stb_image)

add_subdirectory(vendor/GLFW)
add_subdirectory(vendor/glm)

if (APPLE)
    find_library(OPENGL_LIBRARY NAMES OpenGL.framework OpenGL)
endif()

add_executable(3DsMIN
        Event/Event.cpp
        Event/KeyEvent.cpp
        Event/MouseEvent.cpp
        Event/WindowEvent.cpp
        tests/TestTexture.cpp
        vendor/glew/src/glew.c
        vendor/imgui/backends/imgui_impl_glfw.cpp
        vendor/imgui/backends/imgui_impl_opengl3.cpp
        vendor/imgui/imgui.cpp
        vendor/imgui/imgui_draw.cpp
        vendor/imgui/imgui_widgets.cpp
        Camera.cpp
        Entity/CubeObject.cpp
        functions.cpp
        IndexBuffer.cpp
        main.cpp
        Renderer.cpp
        ShaderManager.cpp
        Texture.cpp
        VertexArray.cpp
        VertexBuffer.cpp
        VertexBufferLayout.cpp
        Window.cpp)

target_link_libraries(3DsMIN glfw)

if (APPLE)
    target_link_libraries(3DsMIN ${OPENGL_LIBRARY})
endif()