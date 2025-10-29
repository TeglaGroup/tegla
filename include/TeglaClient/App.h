#pragma once

#include <Mw/Milsko.h>
#include <thread>
#include <atomic>
#include <mutex>

class App {
public:
	void Initialize();
	void Run();
	void Shutdown();

	void GameLoop();
	static void TickHandler(void* widget, void* event, void* userdata);
	std::mutex  stateMutex;

private:
	MwWidget mainWindow;
	MwWidget openGLWidget;

	std::thread	logicThread;
	std::atomic<bool> isRunning{false};
};
