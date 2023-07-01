#include <iostream>
#include <Windows.h>
#include <sapi.h>
#include <string>
#include <unordered_map>
#include <vector>
#include <algorithm>
#include <ctime>
#include <chrono>
#include <iomanip>
#include <sstream>
#include <wininet.h>
#include <json/json.h>
#include <cpprest/http_client.h>
#include <cpprest/filestream.h>
#include <cpprest/uri.h>

#pragma comment(lib, "wininet.lib")
#pragma comment(lib, "ole32.lib")
#pragma comment(lib, "sapi.lib")

using namespace std;
using namespace std::chrono;
using namespace web::http;
using namespace web::http::client;

ISpVoice* voice;

void speak(const string& text) {
    voice->Speak(CString(text.c_str()), 0, NULL);
}

void initializeVoice() {
    CoInitialize(NULL);
    CoCreateInstance(CLSID_SpVoice, NULL, CLSCTX_ALL, IID_ISpVoice, (void**)&voice);
    voice->SetRate(185);
}

void takeCommand(string& user_input) {
    ISpRecognizer* recognizer;
    CoCreateInstance(CLSID_SpRecognizer, NULL, CLSCTX_ALL, IID_ISpRecognizer, (void**)&recognizer);
    recognizer->SetInput(NULL, TRUE);

    ISpAudio* audio;
    SpCreateDefaultObjectFromCategoryId(SPCAT_AUDIOIN, &audio);

    ISpStream* stream;
    recognizer->CreateStream(NULL, &stream);
    recognizer->SetInput(stream, FALSE);
    recognizer->SetRecoState(SPRST_ACTIVE_ALWAYS);

    stream->SetBaseStream(audio, SPDFID_WAVEFORM, FALSE, FALSE);
    audio->SetState(SPAUDIOSTATE_ACTIVE);

    cout << "Listening..." << endl;

    SPRECOGNIZEINFO info = { 0 };
    info.cbSize = sizeof(info);
    info.pvEngineContext = NULL;

    HRESULT hr;
    while (true) {
        hr = recognizer->Recognize(NULL, info);
        if (hr == S_OK) {
            ISpRecoResult* result;
            recognizer->GetResult(&result);

            SPPHRASE* phrase;
            result->GetPhrase(&phrase);

            wchar_t* text = phrase->pProperties->pszValue;
            string user_input_text = CW2A(text);

            user_input = user_input_text;
            break;
        }
        else if (hr == S_FALSE) {
            continue;
        }
        else {
            cout << "Error occurred while recognizing speech." << endl;
            break;
        }
    }

    stream->Release();
    audio->SetState(SPAUDIOSTATE_INACTIVE);
    audio->Release();
    recognizer->SetRecoState(SPRST_INACTIVE);
    recognizer->Release();
}

string getCurrentDateTime() {
    auto now = system_clock::now();
    auto time = system_clock::to_time_t(now);
    stringstream ss;
    ss << put_time(localtime(&time), "%Y-%m-%d %H:%M:%S");
    return ss.str();
}

void getWeatherReport(const string& city) {
    string url = "https://api.openweathermap.org/data/2.5/weather?q=" + city + "&appid=99e68c086c34059f58d3349bd4fb694c&units=metric";

    http_client client(U(url));

    client.request(methods::GET).then([](http_response response) {
        if (response.status_code() == 200) {
            auto body = response.extract_json().get();
            double temperature = body["main"]["temp"].as_double();
            double humidity = body["main"]["humidity"].as_double();
            double wind_speed = body["wind"]["speed"].as_double();

            cout << "Temperature: " << temperature << "°C" << endl;
            cout << "Humidity: " << humidity << "%" << endl;
            cout << "Wind Speed: " << wind_speed << "m/s" << endl;
        }
        else {
            cout << "Error occurred while fetching weather data." << endl;
        }
    }).wait();
}

int main() {
    initializeVoice();

    string user_input;

    while (true) {
        takeCommand(user_input);

        transform(user_input.begin(), user_input.end(), user_input.begin(), ::tolower);

        if (user_input == "exit") {
            speak("Goodbye!");
            break;
        }
        else if (user_input == "time") {
            string current_time = getCurrentDateTime();
            speak("The current time is " + current_time);
        }
        else if (user_input.substr(0, 5) == "weather") {
            string city = user_input.substr(7);
            getWeatherReport(city);
        }
        else {
            speak("Sorry, I didn't understand that.");
        }
    }

    voice->Release();
    CoUninitialize();

    return 0;
}
