#include <iostream>
#include <vector>

int main() {
    int array[] = {1, 2, 3, 4};
    int length = 1 << sizeof(array) / sizeof(array[0]);

    for (int var = 0; var < length; var++) {
        int number = var;
        int position = 0;
        std::vector<int> storeArray;
        
        while (number != 0) {
            if ((number & (1 << 0)) != 0) {
                storeArray.push_back(array[position]);
            }
            number = number >> 1;
            position = position + 1;
        }
        
        for (int i = 0; i < storeArray.size(); i++) {
            std::cout << storeArray[i] << " ";
        }
        std::cout << std::endl;
    }

    return 0;
}
