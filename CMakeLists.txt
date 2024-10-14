cmake_minimum_required(VERSION 3.10)

project(imgui_demo_project)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(IMGUI_DIR "${CMAKE_SOURCE_DIR}/imgui")
set(BACKENDS_DIR "${CMAKE_SOURCE_DIR}/backends")
set(SOURCE_DIR "${CMAKE_SOURCE_DIR}/Source")
set(SRC_DIR "${CMAKE_SOURCE_DIR}/src")
set(GLFW_DIR "${CMAKE_SOURCE_DIR}/GLFW")

file(GLOB IMGUI_SOURCES "${IMGUI_DIR}/*.cpp")
file(GLOB BACKENDS_SOURCES "${BACKENDS_DIR}/*.cpp")
file(GLOB SOURCE_PRIVATE_SOURCES "${SOURCE_DIR}/Private/*.cpp")
file(GLOB SOURCE_PUBLIC_HEADERS "${SOURCE_DIR}/Public/*.h")
file(GLOB SRC_FILES "${SRC_DIR}/main.cpp")

include_directories(
    ${IMGUI_DIR}
    ${BACKENDS_DIR}
    ${GLFW_DIR}/include
    ${SOURCE_DIR}/Public
)

if (WIN32)
    add_executable(imgui_demo WIN32
        ${IMGUI_SOURCES}
        ${BACKENDS_SOURCES}
        ${SOURCE_PRIVATE_SOURCES}
        ${SRC_FILES}
    )
    
    target_link_libraries(imgui_demo
        ${GLFW_DIR}/lib/glfw3.dll.a
        -lopengl32
        -lgdi32
    )
    
    add_custom_command(TARGET imgui_demo POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
        ${GLFW_DIR}/include/GLFW/glfw3.dll
        $<TARGET_FILE_DIR:imgui_demo>
    )
    
else()
    add_executable(imgui_demo
        ${IMGUI_SOURCES}
        ${BACKENDS_SOURCES}
        ${SOURCE_PRIVATE_SOURCES}
        ${SRC_FILES}
    )
    
    target_link_libraries(imgui_demo
        glfw
        GL
        dl
        pthread
        X11
    )
    
    add_custom_command(TARGET imgui_demo POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
        ${SRC_DIR}/imgui.ini
        $<TARGET_FILE_DIR:imgui_demo>
    )
endif()