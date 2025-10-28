#include "TeglaClient/App.h"

#include <Mw/Milsko.h>
#include <Mw/Widget/OpenGL.h>

// TODO: everything

void App::Initialize() {
    mainWindow = MwVaCreateWidget(MwWindowClass, "main", nullptr, MwDEFAULT, MwDEFAULT, 800, 600,
        MwNtitle, "Tegla",
        nullptr);

    openGLWidget = MwCreateWidget(MwOpenGLClass, "gl", mainWindow,
                                  MwDEFAULT, MwDEFAULT, 800, 600);

    MwOpenGLMakeCurrent(openGLWidget);
    MwAddUserHandler(openGLWidget, MwNtickHandler, TickHandler, this);

    isRunning = true;
    logicThread = std::thread(&App::GameLoop, this);
}

void App::TickHandler(void *widget, void *event, void *userdata) {

}


void App::GameLoop() {
    while (isRunning) {
        std::this_thread::sleep_for(std::chrono::milliseconds(16));
    }
}

void App::Run() {
    MwLoop(mainWindow);

    isRunning = false;

    if (logicThread.joinable())
        logicThread.join();
}

void App::Shutdown() {
    isRunning = false;

    if (logicThread.joinable())
        logicThread.join();

    if (mainWindow)
        MwDestroyWidget(mainWindow);
}
