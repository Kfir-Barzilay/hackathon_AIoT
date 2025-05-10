// File: main.cpp
#include "types.h"
#include <mutex>
#include <thread>
#include <atomic>
#include <iostream>
#include <chrono>

// Shared state
Request currentRequest;
std::mutex requestMutex;
std::atomic<bool> running{true};

// Thread declarations
void cameraThread(int picIntervalSec);
void speechThread();
Response sendRequestToApi(const Request& req);

int main() {
    const int picIntervalSec = 3;

    // Start sensor threads
    std::thread cam(cameraThread, picIntervalSec);
    std::thread speech(speechThread);

    // Main loop: batch and send requests every picIntervalSec
    while (running) {
        std::this_thread::sleep_for(std::chrono::seconds(picIntervalSec));

        Request reqCopy;
        {
            std::lock_guard<std::mutex> lock(requestMutex);
            reqCopy = currentRequest;
            currentRequest = Request{}; // reset
        }

        Response resp = sendRequestToApi(reqCopy);
        // Handle AI response
        if (resp.voiceRes.directCall) {
            std::cout << "AI: " << resp.voiceRes.friendlyResponse << std::endl;
        }
        // Adjust status based on resp.voiceRes if needed
    }

    // Cleanup
    cam.join();
    speech.join();
    return 0;
}
