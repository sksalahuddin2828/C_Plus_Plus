#include <iostream>
#include <ctime>
#include <chrono>
#include <thread>
#include <string>
#include <Windows.h>
#include <sapi.h>

// Function declarations
void clockTime();
std::string getCurrentDate();
std::string getCurrentTime();
std::string getIpAddress();
void openWebPage(const std::string& url);
std::string translateToEnglish(const std::string& text);
void speak(const std::string& text);

int main() {
    clockTime();
    speak("हैलो मेरा नाम शेख सलाहुद्दीन है, बताइये में आपकी क्या मदद कर सकता हूँ");

    while (true) {
        std::cout << "बोलिए और क्या मदद चाहिए: ";
        std::string command;
        std::getline(std::cin, command);
        std::string translated = translateToEnglish(command);

        if (translated.find("time") != std::string::npos || translated.find("date") != std::string::npos) {
            std::string date = getCurrentDate();
            std::string clock = getCurrentTime();
            speak("आज की तिथि है " + date + " और वर्तमान समय है " + clock);
        } else if (translated.find("ip address") != std::string::npos) {
            std::string ipAddress = getIpAddress();
            speak("आपका इंटरनेट प्रोटोकॉल (आईपी) है: " + ipAddress);
        } else if (translated.find("youtube") != std::string::npos) {
            openWebPage("https://www.youtube.com/");
        } else if (translated.find("google") != std::string::npos) {
            openWebPage("https://www.google.com/");
        } else if (translated.find("wikipedia") != std::string::npos) {
            openWebPage("https://wikipedia.org/");
        } else if (translated.find("who made you") != std::string::npos || translated.find("creator") != std::string::npos) {
            speak("नाम: शेख सलाहुद्दीन ने मुझे बनाया।");
            speak("Full Name: Sk. Salahuddin, Address: House/Holding No. 173, Village/Road: Maheshwar Pasha Kalibari, Post Office: KUET, Postal Code: 9203, Police Station: Daulatpur, District: Khulna, Country: Bangladesh, Mobile No. +8801767902828, Email: sksalahuddin2828@gmail.com");
            openWebPage("https://github.com/sksalahuddin2828");
        } else if (translated.find("close") != std::string::npos || translated.find("exit") != std::string::npos || translated.find("goodbye") != std::string::npos || translated.find("ok bye") != std::string::npos || translated.find("turn off") != std::string::npos || translated.find("shut down") != std::string::npos) {
            speak("अपना ध्यान रखना, बाद में मिलते हैं! धन्यवाद");
            std::cout << "Stopping Program" << std::endl;
            break;
        } else {
            std::cout << "Command not recognized. Please try again." << std::endl;
        }
    }

    return 0;
}

void clockTime() {
    auto now = std::chrono::system_clock::now();
    std::time_t currentTime = std::chrono::system_clock::to_time_t(now);
    std::tm* localTime = std::localtime(&currentTime);
    int hour = localTime->tm_hour;

    if (hour >= 0 && hour < 12) {
        speak("शुभ प्रभात");
    } else if (hour >= 12 && hour < 18) {
        speak("अभी दोपहर");
    } else if (hour >= 18 && hour < 20) {
        speak("अभी शाम");
    } else {
        speak("शुभ रात्रि");
    }
}

std::string getCurrentDate() {
    auto now = std::chrono::system_clock::now();
    std::time_t currentTime = std::chrono::system_clock::to_time_t(now);
    std::tm* localTime = std::localtime(&currentTime);
    char buffer[80];
    std::strftime(buffer, sizeof(buffer), "%c", localTime);
    return std::string(buffer);
}

std::string getCurrentTime() {
    auto now = std::chrono::system_clock::now();
    std::time_t currentTime = std::chrono::system_clock::to_time_t(now);
    std::tm* localTime = std::localtime(&currentTime);
    char buffer[80];
    std::strftime(buffer, sizeof(buffer), "%H:%M", localTime);
    return std::string(buffer);
}

std::string getIpAddress() {
    std::string ipAddress;
    char buffer[256];
    FILE* stream = _popen("curl -s https://api.ipify.org", "r");

    if (stream) {
        while (!feof(stream)) {
            if (fgets(buffer, 256, stream) != NULL)
                ipAddress += buffer;
        }
        _pclose(stream);
    }

    return ipAddress;
}

void openWebPage(const std::string& url) {
    ShellExecute(NULL, "open", url.c_str(), NULL, NULL, SW_SHOWNORMAL);
}

std::string translateToEnglish(const std::string& text) {
    // Replace this with your translation logic using a translation API or library
    // This is just a placeholder
    return text;
}

void speak(const std::string& text) {
    CoInitialize(NULL);

    ISpVoice* voice;
    HRESULT hr = CoCreateInstance(CLSID_SpVoice, NULL, CLSCTX_ALL, IID_ISpVoice, (void**)&voice);
    if (SUCCEEDED(hr)) {
        wchar_t* wText = new wchar_t[text.size() + 1];
        mbstowcs(wText, text.c_str(), text.size() + 1);
        voice->Speak(wText, 0, NULL);
        delete[] wText;
        voice->Release();
    }

    CoUninitialize();
}


#-------------------------------------------------// Code END Here::-----------------------------------------------


//  ------------------------------------------>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//  if you have difficulty understanding, note the following codes ----------->>>>>>>>>>>>>>>>>


#-------------------------------------------------// Code for understand::-----------------------------------------------


#include <sapi.h>

void speak(const std::string& text) {
    CoInitialize(NULL);

    ISpVoice* voice;
    HRESULT hr = CoCreateInstance(CLSID_SpVoice, NULL, CLSCTX_ALL, IID_ISpVoice, (void**)&voice);
    if (SUCCEEDED(hr)) {
        wchar_t* wText = new wchar_t[text.size() + 1];
        mbstowcs(wText, text.c_str(), text.size() + 1);
        voice->Speak(wText, 0, NULL);
        delete[] wText;
        voice->Release();
    }

    CoUninitialize();
}


#---------------------------------------------------------------------------------------------------------------------


#include <cpprest/http_client.h>
#include <cpprest/filestream.h>
#include <cpprest/json.h>

using namespace utility;
using namespace web;
using namespace web::http;
using namespace web::http::client;
using namespace web::json;
using namespace concurrency::streams;

std::string translateToEnglish(const std::string& text) {
    const std::string apiKey = "YOUR_API_KEY";  // Replace with your Google Translate API key
    const std::string baseUrl = "https://translation.googleapis.com/language/translate/v2";

    http_client client(baseUrl);

    uri_builder builder(U("/translate"));
    builder.append_query(U("key"), apiKey);
    builder.append_query(U("q"), conversions::to_string_t(text));
    builder.append_query(U("target"), U("en"));

    return client.request(methods::GET, builder.to_string())
        .then([](http_response response) {
            return response.extract_json();
        })
        .then([](json::value jsonValue) {
            auto translations = jsonValue[U("data")][U("translations")];
            if (!translations.is_array() || translations.size() == 0) {
                throw std::runtime_error("Translation not available.");
            }
            return conversions::to_utf8string(translations[0][U("translatedText")].as_string());
        })
        .get();
}



  
