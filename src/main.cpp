#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <stdio.h>

#include "Theme.h"

#define GL_SILENCE_DEPRECATION
#if defined(IMGUI_IMPL_OPENGL_ES2)
#include <GLES2/gl2.h>
#endif
#include <GLFW/glfw3.h>

#if defined(_MSC_VER) && (_MSC_VER >= 1900) && !defined(IMGUI_DISABLE_WIN32_FUNCTIONS)
#pragma comment(lib, "legacy_stdio_definitions")
#endif

static void glfw_error_callback(int error, const char* description)
{
    fprintf(stderr, "GLFW Error %d: %s\n", error, description);
}

int main(int, char**)
{
    glfwSetErrorCallback(glfw_error_callback);
    if (!glfwInit())
        return 1;

#if defined(IMGUI_IMPL_OPENGL_ES2)
    const char* glsl_version = "#version 100";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_ES_API);
#elif defined(__APPLE__)
    const char* glsl_version = "#version 150";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#else
    const char* glsl_version = "#version 130";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
#endif

    GLFWwindow* window = glfwCreateWindow(1280, 720, "Resizable Folder Manager", nullptr, nullptr);
    if (window == nullptr)
        return 1;
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;


    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init(glsl_version);

    ImVec4 clear_color = ImVec4(0.07f, 0.07f, 0.10f, 1.00f);


    //// ---------------------------------->
    const char* folders[] = { "Documents", "Pictures", "Projects", "Downloads" };
    const char* files[] = { "hueta.txt", "hueta.png", "hueta.docx", "hueta.zip" };
    int selected_folder = -1;
    int selected_file = -1;
    //// ---------------------------------->

    bool show_popup_menu = false;
    bool show_add_folder_popup = false;
    bool show_remove_folder_popup = false;

    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        // Navbar (верхнее меню)
        if (ImGui::BeginMainMenuBar())
        {
            if (ImGui::BeginMenu("File"))
            {
                if (ImGui::MenuItem("Open", "Ctrl+O")) { printf("Open File\n"); }
                if (ImGui::MenuItem("Save", "Ctrl+S")) { printf("Save File\n"); }
                if (ImGui::MenuItem("Text Editor", "Ctrl+E")) { printf("Edit File\n"); }
                ImGui::Separator();
                if (ImGui::MenuItem("Exit", "Alt+F4")) { glfwSetWindowShouldClose(window, true); }
                ImGui::EndMenu();
            }
            if (ImGui::BeginMenu("Edit"))
            {
                if (ImGui::MenuItem("Undo", "Ctrl+Z")) {}
                if (ImGui::MenuItem("Redo", "Ctrl+Y")) {}
                ImGui::EndMenu();
            }
            if (ImGui::BeginMenu("Unreal Engine 5"))
            {
                if (ImGui::MenuItem("Add you're path of UE5 Regenerate Project"))
                {
                    
                }

                ImGui::Separator();
                
                if (ImGui::MenuItem("Regenerate As Windoows"))
                {

                }
                if (ImGui::MenuItem("Regenerate As Linux"))
                {

                }
                if (ImGui::MenuItem("Regenerate As Mac"))
                {

                }

                ImGui::Separator();

                if (ImGui::MenuItem("Open UE5 Project", "Alt+S"))
                {

                }
                ImGui::EndMenu();
            }
            if (ImGui::BeginMenu("Directories"))
            {
                if (ImGui::MenuItem("Add Path"))
                {
                    
                }

                ImGui::Separator();

                if (ImGui::MenuItem("Import Project from ZIP/TAR.GZ"))
                {

                }
                ImGui::EndMenu();
            }
            if (ImGui::BeginMenu("Help"))
            {
                if (ImGui::MenuItem("About")) {}
                ImGui::EndMenu();
            }
            ImGui::EndMainMenuBar();
        }

        // Главное окно с папками
        ImGui::SetNextWindowSize(ImVec2(ImGui::GetIO().DisplaySize.x * 0.3f, ImGui::GetIO().DisplaySize.y * 0.75f), ImGuiCond_Always);
        ImGui::SetNextWindowPos(ImVec2(0, ImGui::GetIO().DisplaySize.y * 0.05f), ImGuiCond_Always);
        ImGui::Begin("Folders", nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse);

        ImGui::Text("Favorite Folders:");
        ImGui::Separator();

        for (int i = 0; i < IM_ARRAYSIZE(folders); i++) {
            if (ImGui::Selectable(folders[i], selected_folder == i)) {
                selected_folder = i;
            }

            // Popup menu на правую кнопку
            if (ImGui::IsItemClicked(ImGuiMouseButton_Right)) {
                show_popup_menu = true;
                selected_folder = i;
            }
        }

        // Добавим несколько кнопок для управления папками
        if (ImGui::Button("Add Folder")) {
            show_add_folder_popup = true;
        }
        ImGui::SameLine();
        if (ImGui::Button("Remove Folder") && selected_folder != -1) {
            show_remove_folder_popup = true;
        }

        ImGui::End();

        // Окно с файлами
        ImGui::SetNextWindowSize(ImVec2(ImGui::GetIO().DisplaySize.x * 0.7f, ImGui::GetIO().DisplaySize.y * 0.75f), ImGuiCond_Always);
        ImGui::SetNextWindowPos(ImVec2(ImGui::GetIO().DisplaySize.x * 0.3f, ImGui::GetIO().DisplaySize.y * 0.05f), ImGuiCond_Always);
        ImGui::Begin("Files in Selected Folder", nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse);

        if (selected_folder != -1) {
            ImGui::Text("Files in folder: %s", folders[selected_folder]);
            ImGui::Separator();

            for (int i = 0; i < IM_ARRAYSIZE(files); i++) {
                if (ImGui::Selectable(files[i], selected_file == i)) {
                    selected_file = i;
                }

                // Popup menu на файлы
                if (ImGui::IsItemClicked(ImGuiMouseButton_Right)) {
                    show_popup_menu = true;
                    selected_file = i;
                }
            }
            ImGui::Separator();
            
            ImGui::Dummy(ImVec2(0.f, 50.f)); // Padding up: 50 px

            if (ImGui::Button("Open file"))
            {
                // Logic
            }
            if (ImGui::Button("Delete file"))
            {
                // Logic 
            }
            if (ImGui::Button("Move file"))
            {
                // Logic
            }
            
        } else {
            ImGui::Text("Select a folder to view its files.");
        }

        ImGui::End();

        // Панель информации
        ImGui::SetNextWindowSize(ImVec2(ImGui::GetIO().DisplaySize.x, ImGui::GetIO().DisplaySize.y * 0.2f), ImGuiCond_Always);
        ImGui::SetNextWindowPos(ImVec2(0, ImGui::GetIO().DisplaySize.y * 0.8f), ImGuiCond_Always);
        ImGui::Begin("Info Panel", nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse);

        if (selected_file != -1) {
            ImGui::Text("Selected File: %s", files[selected_file]);
        } else if (selected_folder != -1) {
            ImGui::Text("Selected Folder: %s", folders[selected_folder]);
        } else {
            ImGui::Text("Select a folder or file to view details.");
        }

        ImGui::End();

        if (show_popup_menu) {
            if (ImGui::BeginPopupContextWindow()) {
                if (selected_folder != -1) {
                    ImGui::Text("Actions for folder: %s", folders[selected_folder]);
                    if (ImGui::MenuItem("Open")) {}
                    if (ImGui::MenuItem("Rename")) {}
                    if (ImGui::MenuItem("Delete")) {}
                } else if (selected_file != -1) {
                    ImGui::Text("Actions for file: %s", files[selected_file]);
                    if (ImGui::MenuItem("Open")) {}
                    if (ImGui::MenuItem("Rename")) {}
                    if (ImGui::MenuItem("Delete")) {}
                }
                ImGui::EndPopup();
            }
            show_popup_menu = false;
        }

        if (show_add_folder_popup) {
            ImGui::OpenPopup("Add Folder");
        }
        if (ImGui::BeginPopupModal("Add Folder", NULL, ImGuiWindowFlags_AlwaysAutoResize)) {
            ImGui::Text("Enter your path for folder:");
            static char path_for_folder[512] = "";
            ImGui::InputText("##newpath", path_for_folder, IM_ARRAYSIZE(path_for_folder));

            ImGui::Text("Enter the name of the folder:");
            static char new_folder_name[128] = "";
            ImGui::InputText("##newfolder", new_folder_name, IM_ARRAYSIZE(new_folder_name));

            if (ImGui::Button("Add")) {
                // Добавление папки (логика будет здесь)
                ImGui::CloseCurrentPopup();
            }
            ImGui::SameLine();
            if (ImGui::Button("Cancel")) {
                ImGui::CloseCurrentPopup();
            }
            ImGui::EndPopup();
            show_add_folder_popup = false;
        }

        // Popup окно для удаления папки
        if (show_remove_folder_popup) {
            ImGui::OpenPopup("Remove Folder");
        }
        if (ImGui::BeginPopupModal("Remove Folder", NULL, ImGuiWindowFlags_AlwaysAutoResize)) {
            ImGui::Text("Are you sure you want to remove the folder: %s?", folders[selected_folder]);

            if (ImGui::Button("Yes")) {
                // Удаление папки (логика будет здесь)
                ImGui::CloseCurrentPopup();
            }
            ImGui::SameLine();
            if (ImGui::Button("No")) {
                ImGui::CloseCurrentPopup();
            }
            ImGui::EndPopup();
            show_remove_folder_popup = false;
        }

        ImGui::Render();
        int display_w, display_h;
        glfwGetFramebufferSize(window, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
        glClearColor(clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w, clear_color.w);
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