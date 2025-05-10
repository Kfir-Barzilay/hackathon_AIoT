// File: camera.cpp
#include "types.h"
#include <mutex>
#include <thread>
#include <iostream>

extern Request currentRequest;
extern std::mutex requestMutex;
extern std::atomic<bool> running;

void cameraThread(int picIntervalSec) {
    cv::VideoCapture cap(0);
    if (!cap.isOpened()) {
        std::cerr << "[Camera] Cannot open camera" << std::endl;
        running = false;
        return;
    }
    while (running) {
        cv::Mat frame;
        cap >> frame;
        if (frame.empty()) continue;
        {
            std::lock_guard<std::mutex> lock(requestMutex);
            currentRequest.pic = frame;
        }
        std::this_thread::sleep_for(std::chrono::seconds(picIntervalSec));
    }
}
