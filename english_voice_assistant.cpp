#include <iostream>
#include <cstdlib>
#include <string>
#include <ctime>
#include <chrono>
#include <iomanip>
#include <regex>
#include <fstream>
#include <cpprest/http_client.h>
#include <cpprest/filestream.h>
#include <cpprest/json.h>

using namespace std;
using namespace utility;
using namespace web;
using namespace web::http;
using namespace web::http::client;

void OpenWeatherReport(const string& city);
void FatherOfTheNationOfBangladesh();
void GetIPAddress();
void OpenWikipedia();
void SearchOnWikipedia();
void SearchOnYouTube();
void PlayOnYouTube();
void OpenYouTube();
void GetDateAndTime();
void GetLocalTime();
void GetTodayDate();
void OpenFacebook();
void OpenFacebookProfile();
void OpenFacebookSettings();
void OpenFacebookReel();
void OpenFacebookMessenger();
void OpenFacebookVideo();
void OpenFacebookNotification();
void OpenGoogleBrowser();
void OpenGoogleMail();
void OpenGoogleEarth();
void GoogleEarthSpecifyCity();
void OpenGoogleMap();
void GoogleMapSpecifyCity();
void GoogleTranslateSpecifyWord();
void TellJoke();
void TranslateLanguages();
void AvailableCommands();
void WhoMadeYou();
void WhatIsYourName();
void ComputationalGeographicalQuestion();

int main()
{
    cout << "Sk. Salahuddin - Khulna" << endl;

    while (true)
    {
        cout << "How may I assist you?" << endl;
        string userCommand;
        getline(cin, userCommand);

        transform(userCommand.begin(), userCommand.end(), userCommand.begin(), ::tolower);

        if (userCommand.find("exit") != string::npos || userCommand.find("close") != string::npos || userCommand.find("off") != string::npos ||
            userCommand.find("good bye") != string::npos || userCommand.find("bye") != string::npos || userCommand.find("ok bye") != string::npos ||
            userCommand.find("turn off") != string::npos || userCommand.find("shutdown") != string::npos || userCommand.find("no thanks") != string::npos ||
            userCommand.find("stop") != string::npos)
        {
            cout << "Assistant Shut Down" << endl;
            cout << "Take care and see you later" << endl;
            break;
        }

        cout << "Please wait" << endl;
        performAction(userCommand);
    }

    return 0;
}

void performAction(const string& userCommand)
{
    if (userCommand.find("weather") != string::npos || userCommand.find("weather report") != string::npos || userCommand.find("today's weather report") != string::npos)
    {
        cout << "Sure, which city?" << endl;
        string city;
        getline(cin, city);
        transform(city.begin(), city.end(), city.begin(), ::tolower);
        OpenWeatherReport(city);
    }
    else if (userCommand.find("bangabandhu sheikh mujibur rahman") != string::npos || userCommand.find("bangabandhu") != string::npos ||
        userCommand.find("sheikh mujibur rahman") != string::npos || userCommand.find("father of the nation of bangladesh") != string::npos ||
        userCommand.find("father of the nation") != string::npos)
    {
        FatherOfTheNationOfBangladesh();
    }
    else if (userCommand.find("ip address") != string::npos || userCommand.find("internet protocol") != string::npos || userCommand.find("ip") != string::npos)
    {
        GetIPAddress();
    }
    else if (userCommand.find("opening wikipedia") != string::npos)
    {
        OpenWikipedia();
    }
    else if (userCommand.find("search on wikipedia") != string::npos)
    {
        SearchOnWikipedia();
    }
    else if (userCommand.find("search on youtube") != string::npos)
    {
        SearchOnYouTube();
    }
    else if (userCommand.find("play on youtube") != string::npos || userCommand.find("play from youtube") != string::npos ||
             userCommand.find("play a song from youtube") != string::npos || userCommand.find("play a movie from youtube") != string::npos ||
             userCommand.find("play something on youtube") != string::npos || userCommand.find("play something from youtube") != string::npos)
    {
        PlayOnYouTube();
    }
    else if (userCommand.find("open youtube") != string::npos || userCommand.find("opening youtube") != string::npos)
    {
        OpenYouTube();
    }
    else if (userCommand.find("date and time") != string::npos)
    {
        GetDateAndTime();
    }
    else if (userCommand.find("today's time") != string::npos || userCommand.find("local time") != string::npos || userCommand.find("time") != string::npos)
    {
        GetLocalTime();
    }
    else if (userCommand.find("today's date") != string::npos || userCommand.find("today date") != string::npos || userCommand.find("date") != string::npos)
    {
        GetTodayDate();
    }
    else if (userCommand.find("opening facebook") != string::npos)
    {
        OpenFacebook();
    }
    else if (userCommand.find("facebook profile") != string::npos)
    {
        OpenFacebookProfile();
    }
    else if (userCommand.find("facebook settings") != string::npos)
    {
        OpenFacebookSettings();
    }
    else if (userCommand.find("facebook reels") != string::npos)
    {
        OpenFacebookReel();
    }
    else if (userCommand.find("facebook messenger") != string::npos)
    {
        OpenFacebookMessenger();
    }
    else if (userCommand.find("facebook video") != string::npos)
    {
        OpenFacebookVideo();
    }
    else if (userCommand.find("facebook notification") != string::npos)
    {
        OpenFacebookNotification();
    }
    else if (userCommand.find("opening google") != string::npos)
    {
        OpenGoogleBrowser();
    }
    else if (userCommand.find("opening gmail") != string::npos)
    {
        OpenGoogleMail();
    }
    else if (userCommand.find("google earth") != string::npos)
    {
        OpenGoogleEarth();
    }
    else if (userCommand.find("google city") != string::npos || userCommand.find("city on google") != string::npos ||
             userCommand.find("city from earth") != string::npos || userCommand.find("city on earth") != string::npos)
    {
        GoogleEarthSpecifyCity();
    }
    else if (userCommand.find("google map") != string::npos || userCommand.find("map") != string::npos || userCommand.find("map on google") != string::npos)
    {
        OpenGoogleMap();
    }
    else if (userCommand.find("city from map") != string::npos || userCommand.find("map city") != string::npos ||
             userCommand.find("city on map") != string::npos || userCommand.find("google map city") != string::npos)
    {
        GoogleMapSpecifyCity();
    }
    else if (userCommand.find("translate to english") != string::npos || userCommand.find("translate into english") != string::npos || userCommand.find("word translate") != string::npos || userCommand.find("translate a sentence") != string::npos)
    {
        GoogleTranslateSpecifyWord();
    }
    else if (userCommand.find("listen a joke") != string::npos || userCommand.find("tell me a joke") != string::npos)
    {
        TellJoke();
    }
    else if (userCommand.find("translation between two language") != string::npos || userCommand.find("translated language") != string::npos ||
             userCommand.find("translate from google") != string::npos || userCommand.find("language translation") != string::npos ||
             userCommand.find("language") != string::npos)
    {
        TranslateLanguages();
    }
    else if (userCommand.find("what can you do") != string::npos || userCommand.find("available commands") != string::npos || userCommand.find("help") != string::npos)
    {
        AvailableCommands();
    }
    else if (userCommand.find("who made you") != string::npos)
    {
        WhoMadeYou();
    }
    else if (userCommand.find("what is your name") != string::npos || userCommand.find("your name") != string::npos)
    {
        WhatIsYourName();
    }
    else if (userCommand.find("ask") != string::npos)
    {
        ComputationalGeographicalQuestion();
    }
    else
    {
        cout << "Sorry, I didn't understand that command. Please try again!" << endl;
    }
}

void OpenWeatherReport(const string& city)
{
    cout << "Opening the weather report for " << city << "." << endl;
    try
    {
        http_client client(U("https://www.weather-forecast.com"));
        uri_builder builder(U("/locations/" + city + "/forecasts/latest"));
        pplx::task<http_response> response = client.request(methods::GET, builder.to_string());

        response.then([=](http_response response)
        {
            if (response.status_code() == status_codes::OK)
            {
                response.extract_string().then([=](string body)
                {
                    smatch match;
                    regex pattern("<span class=\"phrase\">(.*?)</span>");
                    while (regex_search(body, match, pattern))
                    {
                        cout << match.str(1) << endl;
                        body = match.suffix().str();
                    }
                });
            }
            else
            {
                cout << "Failed to fetch weather information. Please try again later." << endl;
            }
        }).wait();
    }
    catch (const exception& e)
    {
        cout << "Failed to fetch weather information. Please try again later." << endl;
    }
}

void FatherOfTheNationOfBangladesh()
{
    cout << "The Father of the Nation Bangabandhu Sheikh Mujibur Rahman is the architect of independent Bangladesh." << endl;
    cout << "He played a vital role in the liberation movement and is revered as a national hero." << endl;
}

void GetIPAddress()
{
    try
    {
        http_client client(U("https://checkip.amazonaws.com"));
        pplx::task<http_response> response = client.request(methods::GET);

        response.then([=](http_response response)
        {
            if (response.status_code() == status_codes::OK)
            {
                response.extract_string().then([=](string body)
                {
                    cout << "Your IP address is: " << body << endl;
                });
            }
            else
            {
                cout << "Failed to retrieve IP address. Please try again later." << endl;
            }
        }).wait();
    }
    catch (const exception& e)
    {
        cout << "Failed to retrieve IP address. Please try again later." << endl;
    }
}

void OpenWikipedia()
{
    try
    {
        system("start https://www.wikipedia.org/");
    }
    catch (const exception& e)
    {
        cout << "Failed to open Wikipedia. Please try again later." << endl;
    }
}

void SearchOnWikipedia()
{
    cout << "What would you like to search on Wikipedia?" << endl;
    string query;
    getline(cin, query);
    try
    {
        system(("start https://en.wikipedia.org/wiki/" + query).c_str());
    }
    catch (const exception& e)
    {
        cout << "Failed to search on Wikipedia. Please try again later." << endl;
    }
}

void SearchOnYouTube()
{
    cout << "What would you like to search on YouTube?" << endl;
    string query;
    getline(cin, query);
    try
    {
        system(("start https://www.youtube.com/results?search_query=" + query).c_str());
    }
    catch (const exception& e)
    {
        cout << "Failed to search on YouTube. Please try again later." << endl;
    }
}

void PlayOnYouTube()
{
    cout << "What would you like to play on YouTube?" << endl;
    string query;
    getline(cin, query);
    try
    {
        system(("start https://www.youtube.com/results?search_query=" + query).c_str());
    }
    catch (const exception& e)
    {
        cout << "Failed to play on YouTube. Please try again later." << endl;
    }
}

void OpenYouTube()
{
    try
    {
        system("start https://www.youtube.com/");
    }
    catch (const exception& e)
    {
        cout << "Failed to open YouTube. Please try again later." << endl;
    }
}

void GetDateAndTime()
{
    auto now = chrono::system_clock::now();
    time_t time = chrono::system_clock::to_time_t(now);
    tm localTime;
    localtime_s(&localTime, &time);

    char formattedTime[100];
    strftime(formattedTime, sizeof(formattedTime), "%d-%m-%Y %H:%M:%S", &localTime);

    cout << "The current date and time is: " << formattedTime << endl;
}

void GetLocalTime()
{
    auto now = chrono::system_clock::now();
    time_t time = chrono::system_clock::to_time_t(now);
    tm localTime;
    localtime_s(&localTime, &time);

    char formattedTime[100];
    strftime(formattedTime, sizeof(formattedTime), "%H:%M:%S", &localTime);

    cout << "The current local time is: " << formattedTime << endl;
}

void GetTodayDate()
{
    auto now = chrono::system_clock::now();
    time_t time = chrono::system_clock::to_time_t(now);
    tm localTime;
    localtime_s(&localTime, &time);

    char formattedDate[100];
    strftime(formattedDate, sizeof(formattedDate), "%d-%m-%Y", &localTime);

    cout << "Today's date is: " << formattedDate << endl;
}

void OpenFacebook()
{
    try
    {
        system("start https://www.facebook.com/");
    }
    catch (const exception& e)
    {
        cout << "Failed to open Facebook. Please try again later." << endl;
    }
}

void OpenFacebookProfile()
{
    try
    {
    system("start https://www.facebook.com/profile.php");
    }
    catch (const exception& e)
    {
        cout << "Failed to open Facebook profile. Please try again later." << endl;
    }
}

void OpenFacebookSettings()
{
    try
    {
        system("start https://www.facebook.com/settings");
    }
    catch (const exception& e)
    {
        cout << "Failed to open Facebook settings. Please try again later." << endl;
    }
}

void OpenFacebookReel()
{
    try
    {
        system("start https://www.facebook.com/reels");
    }
    catch (const exception& e)
    {
        cout << "Failed to open Facebook Reels. Please try again later." << endl;
    }
}

void OpenFacebookMessenger()
{
    try
    {
        system("start https://www.messenger.com/");
    }
    catch (const exception& e)
    {
        cout << "Failed to open Facebook Messenger. Please try again later." << endl;
    }
}

void OpenFacebookVideo()
{
    try
    {
        system("start https://www.facebook.com/videos");
    }
    catch (const exception& e)
    {
        cout << "Failed to open Facebook videos. Please try again later." << endl;
    }
}

void OpenFacebookNotification()
{
    try
    {
        system("start https://www.facebook.com/notifications");
    }
    catch (const exception& e)
    {
        cout << "Failed to open Facebook notifications. Please try again later." << endl;
    }
}

void OpenGoogleBrowser()
{
    try
    {
        system("start https://www.google.com/");
    }
    catch (const exception& e)
    {
        cout << "Failed to open Google. Please try again later." << endl;
    }
}

void OpenGoogleMail()
{
    try
    {
        system("start https://mail.google.com/");
    }
    catch (const exception& e)
    {
        cout << "Failed to open Google Mail. Please try again later." << endl;
    }
}

void OpenGoogleEarth()
{
    try
    {
        system("start https://www.google.com/earth/");
    }
    catch (const exception& e)
    {
        cout << "Failed to open Google Earth. Please try again later." << endl;
    }
}

void GoogleEarthSpecifyCity()
{
    cout << "Which city do you want to see on Google Earth?" << endl;
    string city;
    getline(cin, city);
    transform(city.begin(), city.end(), city.begin(), ::tolower);
    try
    {
        system(("start https://www.google.com/earth/geo/" + city + "/").c_str());
    }
    catch (const exception& e)
    {
        cout << "Failed to open Google Earth for the specified city. Please try again later." << endl;
    }
}

void OpenGoogleMap()
{
    try
    {
        system("start https://www.google.com/maps/");
    }
    catch (const exception& e)
    {
        cout << "Failed to open Google Map. Please try again later." << endl;
    }
}

void GoogleMapSpecifyCity()
{
    cout << "Which city do you want to see on Google Map?" << endl;
    string city;
    getline(cin, city);
    transform(city.begin(), city.end(), city.begin(), ::tolower);
    try
    {
        system(("start https://www.google.com/maps/place/" + city + "/").c_str());
    }
    catch (const exception& e)
    {
        cout << "Failed to open Google Map for the specified city. Please try again later." << endl;
    }
}

void GoogleTranslateSpecifyWord()
{
    cout << "Which word or sentence do you want to translate to English?" << endl;
    string text;
    getline(cin, text);
    try
    {
        system(("start https://translate.google.com/#auto/en/" + text).c_str());
    }
    catch (const exception& e)
    {
        cout << "Failed to open Google Translate. Please try again later." << endl;
    }
}

void TellJoke()
{
    try
    {
        http_client client(U("https://www.jokes4us.com"));
        uri_builder builder(U("/miscellaneousjokes/cleanjokes.html"));
        pplx::task<http_response> response = client.request(methods::GET, builder.to_string());

        response.then([=](http_response response)
        {
            if (response.status_code() == status_codes::OK)
            {
                response.extract_string().then([=](string body)
                {
                    smatch match;
                    regex pattern("<div style=\"font-size:medium;\">(.*?)</div>");
                    while (regex_search(body, match, pattern))
                    {
                        cout << match.str(1) << endl;
                        body = match.suffix().str();
                    }
                });
            }
            else
            {
                cout << "Failed to fetch a joke. Please try again later." << endl;
            }
        }).wait();
    }
    catch (const exception& e)
    {
        cout << "Failed to fetch a joke. Please try again later." << endl;
    }
}

void TranslateLanguages()
{
    cout << "Which language would you like to translate from?" << endl;
    string fromLanguage;
    getline(cin, fromLanguage);

    cout << "Which language would you like to translate to?" << endl;
    string toLanguage;
    getline(cin, toLanguage);

    cout << "What would you like to translate?" << endl;
    string text;
    getline(cin, text);

    try
    {
        system(("start https://translate.google.com/#" + fromLanguage + "/" + toLanguage + "/" + text).c_str());
    }
    catch (const exception& e)
    {
        cout << "Failed to translate languages. Please try again later." << endl;
    }
}

void AvailableCommands()
{
    cout << "The available commands are:" << endl;
    cout << "- Weather report" << endl;
    cout << "- Father of the Nation of Bangladesh" << endl;
    cout << "- IP address" << endl;
    cout << "- Opening Wikipedia" << endl;
    cout << "- Search on Wikipedia" << endl;
    cout << "- Search on YouTube" << endl;
    cout << "- Play on YouTube" << endl;
    cout << "- Open YouTube" << endl;
    cout << "- Date and time" << endl;
    cout << "- Today's time" << endl;
    cout << "- Today's date" << endl;
    cout << "- Opening Facebook" << endl;
    cout << "- Facebook profile" << endl;
    cout << "- Facebook settings" << endl;
    cout << "- Facebook reels" << endl;
    cout << "- Facebook messenger" << endl;
    cout << "- Facebook video" << endl;
    cout << "- Facebook notification" << endl;
    cout << "- Opening Google" << endl;
    cout << "- Opening Gmail" << endl;
    cout << "- Google Earth" << endl;
    cout << "- Google city" << endl;
    cout << "- Google Map" << endl;
    cout << "- City from Map" << endl;
    cout << "- Translate to English" << endl;
    cout << "- Listen a joke" << endl;
    cout << "- Translation between two languages" << endl;
    cout << "- What can you do?" << endl;
    cout << "- Who made you?" << endl;
    cout << "- What is your name?" << endl;
    cout << "- Ask a computational geographical question" << endl;
}

void WhoMadeYou()
{
    cout << "I was created by a team of developers." << endl;
}

void WhatIsYourName()
{
    cout << "I am an AI language model developed by OpenAI, commonly known as ChatGPT." << endl;
}

void ComputationalGeographicalQuestion()
{
    cout << "Please ask a computational geographical question." << endl;
    string question;
    getline(cin, question);
    try
    {
        system(("start https://www.google.com/search?q=" + question).c_str());
    }
    catch (const exception& e)
    {
        cout << "Failed to process the geographical question. Please try again later." << endl;
    }
}
