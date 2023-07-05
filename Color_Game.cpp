#include <iostream>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <vector>
#include <windows.h>

using namespace std;

vector<string> colors = {"Red", "Orange", "White", "Black", "Green", "Blue", "Brown", "Purple", "Cyan", "Yellow", "Pink", "Magenta"};

int score = 0;
string displayedWordColor = "";
bool gameRunning = false;

void gotoxy(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void printScore() {
    gotoxy(0, 2);
    cout << "Your Score: " << score;
}

void printTimeLeft(int secondsLeft) {
    gotoxy(0, 3);
    cout << "Game Ends in: " << secondsLeft << "s";
}

void printGameDescription() {
    cout << "Game Description: Enter the color of the words displayed below.\nAnd keep in mind not to enter the word text itself" << endl;
}

void startGame() {
    if (!gameRunning) {
        gameRunning = true;
        score = 0;
        system("cls");
        printGameDescription();
        printScore();
        printTimeLeft(60);
        displayedWordColor = colors[rand() % colors.size()];
    }
}

void stopGame() {
    gameRunning = false;
    system("cls");
    cout << "Game Over!" << endl;
}

void nextWord() {
    if (gameRunning) {
        string displayedWordText = colors[rand() % colors.size()];
        gotoxy(0, 5);
        cout << displayedWordText;
        gotoxy(0, 6);
        cout << "Enter the color: ";
        displayedWordColor = colors[rand() % colors.size()];
    }
}

void checkWord(string userInput) {
    if (gameRunning) {
        transform(userInput.begin(), userInput.end(), userInput.begin(), ::tolower);
        if (userInput == displayedWordColor) {
            score++;
            printScore();
        }
        nextWord();
    }
}

int main() {
    srand(static_cast<unsigned int>(time(0)));

    while (true) {
        if (GetAsyncKeyState(VK_SPACE)) {
            startGame();
        }
        if (GetAsyncKeyState(VK_RETURN)) {
            string userInput;
            getline(cin, userInput);
            checkWord(userInput);
        }
        Sleep(10);
    }

    return 0;
}
