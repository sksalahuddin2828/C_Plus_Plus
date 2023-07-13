#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <cmath>
#include <curl/curl.h>
#include <nlohmann/json.hpp>

#include "skyfield/almanac.h"
#include "skyfield/api.h"
#include "skyfield/position.h"

using json = nlohmann::json;
using namespace std;
using namespace skyfield;
using namespace skyfield::almanac;
using namespace skyfield::api;
using namespace skyfield::positions;

struct SatelliteData {
    string name;
    string tle_line1;
    string tle_line2;
    double angle;
};

struct SatelliteDbEntry {
    string name;
    string country;
};

size_t WriteCallback(void* contents, size_t size, size_t nmemb, string* response) {
    response->append((char*)contents, size * nmemb);
    return size * nmemb;
}

string SendGetRequest(const string& url) {
    string response;
    CURL* curl = curl_easy_init();
    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);
        CURLcode res = curl_easy_perform(curl);
        if (res != CURLE_OK) {
            cout << "Error in SendGetRequest: " << curl_easy_strerror(res) << endl;
        }
        curl_easy_cleanup(curl);
    }
    return response;
}

int main() {
    try {
        // Step 1: Retrieve satellite data from the API
        string satelliteDataApiUrl = "API_URL_HERE";
        string satelliteDataJson = SendGetRequest(satelliteDataApiUrl);
        vector<SatelliteData> satelliteData = json::parse(satelliteDataJson);

        // Step 2: Parse TLE data using Skyfield
        vector<string[2]> tleData;
        for (const auto& satellite : satelliteData) {
            string line1 = satellite.tle_line1;
            string line2 = satellite.tle_line2;
            tleData.push_back({ line1, line2 });
        }

        // Step 3: Visualize satellite orbits in 3D
        Loader loader("path_to_data_directory");
        auto ephemeris = loader.load("de421.bsp");
        auto satellites = loader.parse_tle_file(tleData);

        auto fig = plt::figure();
        auto ax = fig.add_subplot(111, projection='3d');

        for (const auto& satellite : satellites) {
            // Calculate the satellite's position over time
            auto ts = loader.make_timescale();
            auto t = ts.utc(2023, 7, 11, 0, vector<int>(3600, 0));
            auto geocentric = satellite.at(t);
            auto subpoint = geocentric.subpoint();

            // Extract latitude, longitude, and altitude
            auto latitude = subpoint.latitude().degrees();
            auto longitude = subpoint.longitude().degrees();
            auto altitude = subpoint.elevation().km();

            // Plot the satellite's trajectory in 3D
            ax.plot(longitude, latitude, altitude);
        }

        ax.set_xlabel("Longitude");
        ax.set_ylabel("Latitude");
        ax.set_zlabel("Altitude (km)");

        // Step 4: Map satellites to countries using the satellite database API
        string satelliteDbApiUrl = "SATELLITE_DB_API_URL_HERE";
        string satelliteDbJson = SendGetRequest(satelliteDbApiUrl);
        vector<SatelliteDbEntry> satelliteDb = json::parse(satelliteDbJson);

        // Mapping satellite names to countries
        map<string, string> satelliteCountryMap;
        for (const auto& satellite : satelliteData) {
            string name = satellite.name;
            for (const auto& entry : satelliteDb) {
                if (entry.name == name) {
                    string country = entry.country;
                    satelliteCountryMap[name] = country;
                    break;
                }
            }
        }

        // Printing satellite information
        for (const auto& satellite : satelliteData) {
            string name = satellite.name;
            double angle = satellite.angle;
            string country = satelliteCountryMap[name];

            cout << "Satellite Name: " << name << endl;
            cout << "Orbital Angle: " << angle << " degrees" << endl;
            cout << "Country: " << country << endl;
            cout << endl;
        }

        // Show the 3D plot
        plt::show();
    }
    catch (const exception& e) {
        cout << "Error: " << e.what() << endl;
    }

    return 0;
}
