#include <iostream>
#include <vector>
#include <sstream>
#include <regex>

struct WifiProfile {
    std::string ssid;
    std::string password;
};

std::vector<WifiProfile> getWifiProfiles() {
    std::vector<WifiProfile> wifiList;
    
    std::string command = "netsh wlan show profiles";
    std::array<char, 128> buffer;
    std::string result;
    FILE* pipe = _popen(command.c_str(), "r");
    
    if (pipe) {
        while (fgets(buffer.data(), buffer.size(), pipe) != nullptr) {
            result += buffer.data();
        }
        _pclose(pipe);
    }
    
    std::regex profileRegex(R"(    All User Profile     : (.*)\r\n)");
    std::smatch match;
    
    auto profileBegin = std::sregex_iterator(result.begin(), result.end(), profileRegex);
    auto profileEnd = std::sregex_iterator();
    
    for (std::sregex_iterator i = profileBegin; i != profileEnd; ++i) {
        std::string profileName = (*i)[1].str();
        
        std::string profileCommand = "netsh wlan show profile \"" + profileName + "\" key=clear";
        std::string profileResult;
        FILE* profilePipe = _popen(profileCommand.c_str(), "r");
        
        if (profilePipe) {
            while (fgets(buffer.data(), buffer.size(), profilePipe) != nullptr) {
                profileResult += buffer.data();
            }
            _pclose(profilePipe);
        }
        
        std::regex passwordRegex(R"(Key Content            : (.*)\r\n)");
        std::smatch passwordMatch;
        
        if (!std::regex_search(profileResult, passwordMatch, passwordRegex))
            continue;
        
        std::string password = passwordMatch[1].str();
        
        WifiProfile wifiProfile;
        wifiProfile.ssid = profileName;
        wifiProfile.password = password;
        
        wifiList.push_back(wifiProfile);
    }
    
    return wifiList;
}

int main() {
    std::vector<WifiProfile> wifiList = getWifiProfiles();
    
    for (const auto& wifiProfile : wifiList) {
        std::cout << "SSID: " << wifiProfile.ssid << ", Password: " << wifiProfile.password << std::endl;
    }
    
    return 0;
}
