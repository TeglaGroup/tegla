#include "TeglaServer/Game/World.h"
#include "TeglaServer/NetworkServer.h"

#include "TeglaCore/ScriptingCore.h"

#include <atomic>
#include <iostream>
#include <thread>

int main(int argc, char** argv) {
	NetworkServer server(4000);
	World gameWorld;
	ScriptingCore scripting;

	server.Start();

	std::atomic<bool> isRunning{true};
	
	// console input thread, rn it's just a lambda that waits for "quit" command
	std::thread console([&]() {
        std::string cmd;

        while (isRunning) {
			std::cout << "> " << std::flush;
            if (std::getline(std::cin, cmd)) {
                if (cmd == "quit" || cmd == "exit") {
                    isRunning = false;
                } else if (cmd.rfind("eval ", 0) == 0) {
					std::string code = cmd.substr(5);
					scripting.RunEval(code);
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