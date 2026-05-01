#include "imageviewer.h"

#include "backends/imgui_impl_opengl3.h"
#include "backends/imgui_impl_win32.h"

static constexpr GLint INTERNAL_FMT = sizeof(Color) == 3 * sizeof(float) ? GL_RGB : GL_RGBA;

// Forward declaration
extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND, UINT, WPARAM, LPARAM);

static LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    if (ImGui_ImplWin32_WndProcHandler(hWnd, msg, wParam, lParam)) {
        return true;
    }
    switch (msg) {
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    }
    return DefWindowProc(hWnd, msg, wParam, lParam);
}

ImageViewer::ImageViewer() : height(0), width(0), pixels(), texture(0), hwnd(NULL), hdc(NULL), glrc(NULL)
{
    static_assert(sizeof(Color) == (3 * sizeof(float)) || sizeof(Color) == (4 * sizeof(float)));
}

ImageViewer::~ImageViewer()
{
    if (texture) {
        glDeleteTextures(1, &texture);
    }
}

bool ImageViewer::Load(const std::vector<Color>& pixels, int h)
{
    if (pixels.size() % h != 0) {
        return false;
    }
    height = h;
    width = pixels.size() / h;
    this->pixels = pixels;
    return true;
}

void ImageViewer::CreateTexture()
{
    if (texture) {
        glDeleteTextures(1, &texture);
    }

    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexImage2D(GL_TEXTURE_2D, 0, INTERNAL_FMT, width, height, 0, INTERNAL_FMT, GL_FLOAT, pixels.data());
}

void ImageViewer::CreateWindowAndContext(const std::string& title)
{
    HINSTANCE hInstance = GetModuleHandle(NULL);

    WNDCLASS wc = {};
    wc.lpfnWndProc = WndProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = "PPMViewerClass";
    RegisterClass(&wc);

    hwnd = CreateWindow(wc.lpszClassName, title.c_str(), WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, width + 100,
                        height + 100, NULL, NULL, hInstance, NULL);

    ShowWindow(hwnd, SW_SHOW);

    hdc = GetDC(hwnd);

    PIXELFORMATDESCRIPTOR pfd = {sizeof(PIXELFORMATDESCRIPTOR), 1,
                                 PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER, PFD_TYPE_RGBA, 32};

    int pf = ChoosePixelFormat(hdc, &pfd);
    SetPixelFormat(hdc, pf, &pfd);

    glrc = wglCreateContext(hdc);
    wglMakeCurrent(hdc, glrc);

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();

    ImGui_ImplWin32_Init(hwnd);
    ImGui_ImplOpenGL3_Init("#version 130");
}

void ImageViewer::DestroyWindowAndContext()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplWin32_Shutdown();
    ImGui::DestroyContext();

    wglMakeCurrent(NULL, NULL);
    wglDeleteContext(glrc);
    ReleaseDC(hwnd, hdc);
}

void ImageViewer::RenderLoop(const std::string& title)
{
    MSG msg;
    bool open = true;

    while (open) {
        while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
            if (msg.message == WM_QUIT)
                open = false;

            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplWin32_NewFrame();
        ImGui::NewFrame();

        ImGui::Begin(title.c_str(), &open, ImGuiWindowFlags_AlwaysAutoResize);
        ImGui::Text("Resolution: %dx%d", width, height);
        ImGui::Text("FPS: %.1f", ImGui::GetIO().Framerate);
        ImGui::Image((void*)(intptr_t)texture, ImVec2((float)width, (float)height));
        if (ImGui::Button("Close"))
            open = false;
        ImGui::End();

        ImGui::Render();
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        SwapBuffers(hdc);
    }
}

void ImageViewer::Show(const std::string& title)
{
    CreateWindowAndContext(title);
    CreateTexture();
    RenderLoop(title);
    DestroyWindowAndContext();
}
