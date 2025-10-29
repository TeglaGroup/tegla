#include "TeglaServer/Game/World.h"
#include "TeglaServer/NetworkServer.h"

#include "TeglaCore/ScriptingCore.h"

#include <atomic>
#include <iostream>
#include <queue>
#include <thread>

int main(int argc, char** argv) {
	NetworkServer server(4000);
	World gameWorld;
	ScriptingCore scripting;

	server.Start();

	std::atomic<bool> isRunning{true};

	std::queue<std::string> evalQueue;
	std::mutex evalMutex;
	
	// console input thread, rn it's just a lambda that waits for "quit" command
	std::thread console([&]() {
        std::string cmd;

        while (isRunning) {
			std::cout << "> " << std::flush;
            if (std::getline(std::cin, cmd)) {
                if (cmd == "quit" || cmd == "exit") {
                    isRunning = false;
                } else if (cmd.rfind("eval ", 0) == 0) {
					std::lock_guard<std::mutex> lock(evalMutex);
					evalQueue.push(cmd.substr(5));
				} else {
					std::cout << "unknown command: " << cmd << std::endl;
				}
            }
        }
    });

	const float TICK_RATE = 60.0f;
    const float deltaTime = 1.0f / TICK_RATE;

    while (isRunning) {
        auto start = std::chrono::high_resolution_clock::now();

        server.Poll();

		// TODO: this does nothing yet, just there for structure
        gameWorld.Update(deltaTime);
        gameWorld.BroadcastState();

		{
			// run queued evals
			std::lock_guard<std::mutex> lock(evalMutex);
			while (!evalQueue.empty()) {
				scripting.RunEval(evalQueue.front());
				evalQueue.pop();
			}
		}			

		// fire scripting events
		JSValue arg2 = JS_NewFloat64(scripting.context, deltaTime);
		scripting.FireEvent("onServerTick", 1, &arg2);
		JS_FreeValue(scripting.context, arg2);

		// sleep until next tick
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<float> elapsed = end - start;

		float sleepTime = deltaTime - elapsed.count();

		if (sleepTime > 0)
            std::this_thread::sleep_for(std::chrono::duration<float>(sleepTime));
    }

    server.Stop();
    console.join();

	return 0;
}