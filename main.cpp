// File: main.cpp
#include "types.h"
#include <mutex>
#include <thread>
#include <atomic>
#include <iostream>
#include <chrono>
#include <opencv2/opencv.hpp>

// Shared state
std::mutex requestMutex;
std::atomic<bool> running{true};
std::string sharedSpeechText;

// Thread declarations
void speechThread();
Response sendRequestToApi(const Request& req);

int main() {
    const int picIntervalSec = 3;

    // Open camera once
    cv::VideoCapture cap(0);
    if (!cap.isOpened()) {
        std::cerr << "[Camera] Cannot open camera" << std::endl;
        return -1;
    }

    // Start speech thread
    std::thread speech(speechThread);

    while (running) {
        // Wait interval
        std::this_thread::sleep_for(std::chrono::seconds(picIntervalSec));

        // Capture frame just before sending
        cv::Mat frame;
        cap >> frame;
        if (frame.empty()) continue;

        // Prepare request
        Request req;
        req.pic = frame;
        {
            std::lock_guard<std::mutex> lock(requestMutex);
            req.speechToText = sharedSpeechText;
            sharedSpeechText.clear();  // reset after consuming
        }

        // Send to AI API
        Response resp = sendRequestToApi(req);

        // Handle AI response
        if (resp.voiceRes.directCall) {
            std::cout << "AI: " << resp.voiceRes.friendlyResponse << std::endl;
        }
        // TODO: adjust status or take actions based on resp
    }

    // Cleanup
    speech.join();
    return 0;
}
