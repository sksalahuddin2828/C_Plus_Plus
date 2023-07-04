#include <iostream>
#include <unordered_map>
#include <vector>

void findMostOccChar(const std::string& str) {
std::unordered_map<char, int> charCount;
// Count the occurrence of each character in the string
for (char c : str) {
    charCount[c]++;
}

int maxCount = 0;
// Finding the maximum occurrence of a character
for (const auto& entry : charCount) {
    if (entry.second > maxCount) {
        maxCount = entry.second;
    }
}

// Collect the most occurring character(s)
std::vector<char> mostOccChars;
for (const auto& entry : charCount) {
    if (entry.second == maxCount) {
        mostOccChars.push_back(entry.first);
    }
}

// Printing the most occurring character(s) and its count
for (char c : mostOccChars) {
    std::cout << "Character: " << c << ", Count: " << maxCount << std::endl;
}
}

int main() {
std::string inputString = "helloworldmylovelypython";
findMostOccChar(inputString);
return 0;
}


// Answer: /tmp/Y4XZ1a4DwQ.o
//         Character: l, Count: 5
