// File: speech.cpp
#include "types.h"
#include <mutex>
#include <thread>
#include <iostream>

extern Request currentRequest;
extern std::mutex requestMutex;
extern std::atomic<bool> running;

// Placeholder: implement with your preferred speech-to-text library
std::string speechToTextCapture() {
    // TODO: capture from microphone and transcribe
    return "";
}

void speechThread() {
    while (running) {
        std::string text = speechToTextCapture();
        if (!text.empty()) {
            std::lock_guard<std::mutex> lock(requestMutex);
            currentRequest.speechToText = text;
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }
}

