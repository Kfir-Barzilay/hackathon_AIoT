// File: types.h
#pragma once

#include <string>
#include <chrono>
#include <opencv2/opencv.hpp>  // For cv::Mat and camera capture

// Enumerations for items held and objects looked at
enum class HoldItem {
    Pen, Pencil, ApplePencil, TabletPencil, Calipers, Ruler,
    KeyboardOrMouse, Drink, Food, Phone, None
};

enum class LookItem {
    PC, Tablet, Phone, Wall, Window,
    Book, Folder, Furniture, Picture, Pet, None
};

// Response after analyzing a picture
struct PictureResponse {
    bool isPerson;              // true if a person is detected
    bool isFocus;               // true if the person appears focused
    HoldItem holdItem;
    LookItem lookItem;
    std::chrono::system_clock::time_point timestamp;
};

// Overall status/configuration
struct Status {
    int sensitivityLevel;       // 0=low,1=moderate,2=high
    bool silentMode;            // true=don't speak
};

// Response after analyzing speech
struct VoiceResponse {
    bool directCall;            // e.g., contains "Hello duck"
    bool changeSensitivity;     // whether to change sensitivity
    int sensitivityLevel;       // -1=irrelevant,0=low,1=moderate,2=high
    bool changeSilentMode;      // whether to change silent mode
    bool silentModeOn;          // true=silent mode on
    std::string friendlyResponse;
};

// Combined request structure
struct Request {
    cv::Mat pic;               // Captured frame
    std::string speechToText;  // Transcribed speech, if any
};

// Combined response from AI API
struct Response {
    PictureResponse picRes;
    VoiceResponse voiceRes;
};
