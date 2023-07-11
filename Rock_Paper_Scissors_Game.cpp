#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

string userInputChecker();
int* gameLogic(string computerChoice, string userChoice, int userScore, int computerScore);

int main() {
    srand(time(NULL));
    string choices[] = { "rock", "paper", "scissors" };

    cout << "Welcome to the game!" << endl;
    cout << "Enter:" << endl;
    cout << "r for rock" << endl;
    cout << "p for paper" << endl;
    cout << "s for scissors" << endl;

    cout << "Enter your name: ";
    string playerName;
    getline(cin, playerName);

    int userScoreTotal = 0;
    int computerScoreTotal = 0;
    int i = 1;

    while (i == 1) {
        string userChoice = userInputChecker();
        while (userChoice == "") {
            userChoice = userInputChecker();
        }

        string computerChoice = choices[rand() % 3];
        cout << "Computer chooses: " << computerChoice << endl;

        int* scores = gameLogic(computerChoice, userChoice, userScoreTotal, computerScoreTotal);
        i = scores[0];
        userScoreTotal = scores[1];
        computerScoreTotal = scores[2];

        if (i == 0) {
            cout << "Scores for this match are as follows:" << endl;
            cout << playerName << "'s score: " << userScoreTotal << endl;
            cout << "Computer's score: " << computerScoreTotal << endl;
            cout << "Thank you for playing the game." << endl;
            cout << "Have a nice day!" << endl;
        }
        else if (i != 0 && i != 1) {
            cout << "Invalid Input!" << endl;
            cout << "Please enter 1 to continue or 0 to leave the game: ";
            cin >> i;
            cin.ignore();
        }
    }

    return 0;
}

string userInputChecker() {
    cout << "Enter your choice: ";
    string userChoice;
    getline(cin, userChoice);
    if (userChoice == "r" || userChoice == "p" || userChoice == "s") {
        return userChoice;
    }
    else {
        cout << "Wrong Input!!" << endl;
        return "";
    }
}

int* gameLogic(string computerChoice, string userChoice, int userScore, int computerScore) {
    static int scores[3];
    if (computerChoice == "rock" && userChoice == "p") {
        cout << "Player Wins" << endl;
        cout << "Enter 1 to continue and 0 to leave the game" << endl;
        userScore += 1;
        cin >> scores[0];
        cin.ignore();
        scores[1] = userScore;
        scores[2] = computerScore;
        return scores;
    }
    else if (computerChoice == "rock" && userChoice == "s") {
        cout << "Computer Wins" << endl;
        cout << "Enter 1 to continue and 0 to leave the game" << endl;
        computerScore += 1;
        cin >> scores[0];
        cin.ignore();
        scores[1] = userScore;
        scores[2] = computerScore;
        return scores;
    }
    else if (computerChoice == "paper" && userChoice == "r") {
        cout << "Computer Wins" << endl;
        cout << "Enter 1 to continue and 0 to leave the game" << endl;
        computerScore += 1;
        cin >> scores[0];
        cin.ignore();
        scores[1] = userScore;
        scores[2] = computerScore;
        return scores;
    }
    else if (computerChoice == "paper" && userChoice == "s") {
        cout << "Player Wins" << endl;
        cout << "Enter 1 to continue and 0 to leave the game" << endl;
        userScore += 1;
        cin >> scores[0];
        cin.ignore();
        scores[1] = userScore;
        scores[2] = computerScore;
        return scores;
    }
    else if (computerChoice == "scissors" && userChoice == "r") {
        cout << "Player Wins" << endl;
        cout << "Enter 1 to continue and 0 to leave the game" << endl;
        userScore += 1;
        cin >> scores[0];
        cin.ignore();
        scores[1] = userScore;
        scores[2] = computerScore;
        return scores;
    }
    else if (computerChoice == "scissors" && userChoice == "p") {
        cout << "Computer Wins" << endl;
        cout << "Enter 1 to continue and 0 to leave the game" << endl;
        computerScore += 1;
        cin >> scores[0];
        cin.ignore();
        scores[1] = userScore;
        scores[2] = computerScore;
        return scores;
    }
    else if (computerChoice == userChoice) {
        cout << "Draw" << endl;
        cout << "Enter 1 to continue and 0 to leave the game" << endl;
        userScore += 1;
        computerScore += 1;
        cin >> scores[0];
        cin.ignore();
        scores[1] = userScore;
        scores[2] = computerScore;
        return scores;
    }

    return scores;
}
