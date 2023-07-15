#include <iostream>
#include <algorithm>
#include <cctype>

bool is_palindrome(std::string s) {
    s.erase(std::remove_if(s.begin(), s.end(), [](char c) {
        return !std::isalnum(c);
    }), s.end());
    std::transform(s.begin(), s.end(), s.begin(), ::tolower);
    std::string reversed(s.rbegin(), s.rend());
    return s == reversed;
}

int main() {
    std::string str;
    std::cout << "Enter a string: ";
    std::getline(std::cin, str);
    if (is_palindrome(str)) {
        std::cout << "'" << str << "' is a palindrome." << std::endl;
    } else {
        std::cout << "'" << str << "' is not a palindrome." << std::endl;
    }
    return 0;
}
