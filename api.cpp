// File: api.cpp
#include "types.h"
#include <nlohmann/json.hpp>  // JSON for Modern C++
#include <curl/curl.h>
#include <iostream>

// Placeholder: implement actual HTTP POST to AI API (OpenAI/Gemini)
Response sendRequestToApi(const Request& req) {
    Response res{};
    // TODO:
    // 1. Encode req.pic to base64 or multipart
    // 2. Build JSON payload with image + req.speechToText
    // 3. Send with libcurl to chosen endpoint
    // 4. Parse JSON response into res.picRes and res.voiceRes
    std::cout << "[API] Sending request to AI..." << std::endl;
    return res;
}
