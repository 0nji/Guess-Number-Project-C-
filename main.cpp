#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>
#include <cstdlib>
#include <fstream>
#include <limits>
#include <string>

using namespace std;

struct Score{
    string name;
    int points;
    string difficulty;
};

vector<Score> scores;

vector<string> Low = {
    "Number too low! Try again.",
    "Your guess is below the target number.",
    "Try a higher number!"
};
vector<string> High = {
    "Number too high! Try again.",
    "Your guess exceeds the target number.",
    "Try a lower number!"
};

void loadScores(){
    ifstream file("scores.txt");
    if (!file) return;

    Score s;
    while (file >> s.name >> s.points >> s.difficulty) {
        scores.push_back(s);
    }
    file.close();
}

void saveScore(const Score& s) {
    ofstream file("scores.txt" , ios::app);
    for (const auto& s : scores) {
        file << s.name << " " << s.points << " " << s.difficulty << endl;
    }
    file.close();
}

void displayScores() {
    if (scores.empty()){
        cout << "No high scores available." << endl;
        return;
    }
    sort(scores.begin(), scores.end(), [](const Score& a, const Score& b) {
        return a.points < b.points;
    });

    cout << "_____High Scores_____" << endl;
    for (int i = 0; i < scores.size() && i < 5; ++i) {
        cout << i+1 << ". " << scores[i].name << " " << scores[i].points << " (" << scores[i].difficulty << ")" << endl;
    }
    cout << "_____________________" << endl;
}

int getValidInt() {
    int value;

    while (true) {
        cin >> value;

        if (cin.fail()) {
            cin.clear();                
            cin.ignore(10000, '\n'); 
            cout << "Invalid input. Enter a number: ";
        } else {
            return value;
        }
    }
}

void playGame(){
    int level;
    int maxNumber;
    string difficulty;

    cout << "Select difficulty: \n";
    cout << "1. Easy (1-50)\n";
    cout << "2. Medium (1-100)\n";
    cout << "3. Hard (1-250)\n";
    cout << "Enter choice: ";
    level = getValidInt();

    if (level == 1) {
        maxNumber = 50;
        difficulty = "Easy";
    } else if (level == 2) {
        maxNumber = 100;
        difficulty = "Medium";
    } else {
        maxNumber = 250;
        difficulty = "Hard";
    }

    int target = rand() % maxNumber + 1;
    int guess;
    int attempts = 0;

    cout << "Guess the number between 1 and " << maxNumber << "!" << endl;

    while (true)
    {
        cout << "Attempt " << attempts + 1 << ": ";
        guess = getValidInt();
        attempts++;

        if (guess < target) {
            cout << Low[rand() % Low.size()] << endl;
        } else if (guess > target) {
            cout << High[rand() % High.size()] << endl;
        } else {
            cout << "Congratulations! You've guessed the number " << target << " in " << attempts << " attempts!" << endl;
            string name;
            cout << "Enter your name: ";
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            getline(cin, name);

            scores.push_back({name, attempts, difficulty});
            saveScore({name, attempts, difficulty});
            break;
        }


    }
    

}

int main() {
    srand(time(nullptr));
    loadScores();

    int choice;
    do {
        cout << "1. Start Game\n";
        if (!scores.empty()){
            cout << "2. High Scores\n";
        }
        cout << "3. Exit\n";
        cout << "Enter choice: ";
        choice = getValidInt();

        switch (choice) {
            case 1:
                playGame();
                break;
            case 2:
                if (!scores.empty())
                    displayScores();
            case 3:
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 3);
    return 0;
}