cmake_minimum_required(VERSION 3.10)

project(imgui_demo_project)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Пути к директориям проекта
set(IMGUI_DIR "${CMAKE_SOURCE_DIR}/imgui")
set(BACKENDS_DIR "${CMAKE_SOURCE_DIR}/backends")
set(SOURCE_DIR "${CMAKE_SOURCE_DIR}/Source")
set(SRC_DIR "${CMAKE_SOURCE_DIR}/src")
set(GLFW_DIR "${CMAKE_SOURCE_DIR}/GLFW")

# Файлы проекта
file(GLOB IMGUI_SOURCES "${IMGUI_DIR}/*.cpp")
file(GLOB BACKENDS_SOURCES "${BACKENDS_DIR}/*.cpp")
file(GLOB SOURCE_PRIVATE_SOURCES "${SOURCE_DIR}/Private/*.cpp")
file(GLOB SOURCE_PUBLIC_HEADERS "${SOURCE_DIR}/Public/*.h")
file(GLOB SRC_FILES "${SRC_DIR}/main.cpp")

# Инклуды
include_directories(
    ${IMGUI_DIR}
    ${BACKENDS_DIR}
    ${GLFW_DIR}/include
    ${SOURCE_DIR}/Public
)

# Создание исполняемого файла
add_executable(imgui_demo WIN32
    ${IMGUI_SOURCES}
    ${BACKENDS_SOURCES}
    ${SOURCE_PRIVATE_SOURCES}
    ${SRC_FILES}
)

# Линковка с библиотеками
target_link_libraries(imgui_demo
    ${GLFW_DIR}/lib/glfw3.dll.a  # MinGW версия библиотеки glfw3
    -lopengl32                   # OpenGL для MinGW
    -lgdi32                      # Для MinGW нужно линковать GDI32 для работы с окнами
)

# Копирование необходимых файлов после сборки
add_custom_command(TARGET imgui_demo POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy
    ${GLFW_DIR}/include/GLFW/glfw3.dll
    $<TARGET_FILE_DIR:imgui_demo>
)

add_custom_command(TARGET imgui_demo POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy
    ${SRC_DIR}/imgui.ini
    $<TARGET_FILE_DIR:imgui_demo>
)
