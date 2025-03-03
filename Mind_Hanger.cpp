#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <map>
using namespace std;

const map<string, string> WORDS = {
    {"apple", "A popular red or green fruit"},
    {"banana", "A long, yellow fruit"},
    {"grapes", "Small, round, purple or green fruit"},
    {"mango", "A tropical fruit known as the king of fruits"},
    {"orange", "A citrus fruit with a name that is also a color"},
    {"strawberry", "A small, red fruit with tiny seeds on the outside"},
    {"pineapple", "A tropical fruit with spiky skin and sweet yellow flesh"}
};

pair<string, string> getRandomWord() {
    srand(time(0));
    auto it = next(WORDS.begin(), rand() % WORDS.size());
    return *it;
}

void displayWord(const string &word, const vector<bool> &guessed) {
    for (size_t i = 0; i < word.size(); i++) {
        if (guessed[i])
            cout << word[i] << " ";
        else
            cout << "_ ";
    }
    cout << endl;
}

void displayHangman(int attempts) {
    vector<string> hangman = {
        "  +---+\n  |   |\n      |\n      |\n      |\n      |\n=========",
        "  +---+\n  |   |\n  O   |\n      |\n      |\n      |\n=========",
        "  +---+\n  |   |\n  O   |\n  |   |\n      |\n      |\n=========",
        "  +---+\n  |   |\n  O   |\n /|   |\n      |\n      |\n=========",
        "  +---+\n  |   |\n  O   |\n /|\  |\n      |\n      |\n=========",
        "  +---+\n  |   |\n  O   |\n /|\  |\n /    |\n      |\n=========",
        "  +---+\n  |   |\n  O   |\n /|\  |\n / \  |\n      |\n========="
    };
    cout << hangman[6 - attempts] << endl;
}

int main() {
    auto[word, hint] = getRandomWord();
    int attempts = 6;
    vector<bool> guessed(word.size(), false);
    vector<char> wrongGuesses;
    
    cout << "\nWelcome to Hangman!\n";
    cout << "Hint: " << hint << "\n";
    
    while (attempts > 0) {
        displayHangman(attempts);
        displayWord(word, guessed);
        cout << "Wrong Guesses: ";
        for (char c : wrongGuesses) cout << c << " ";
        cout << "\nAttempts left: " << attempts << "\n";

        char guess;
        cout << "Enter your guess: ";
        cin >> guess;

        bool found = false;
        for (size_t i = 0; i < word.size(); i++) {
            if (word[i] == guess && !guessed[i]) {
                guessed[i] = true;
                found = true;
            }
        }

        if (!found) {
            wrongGuesses.push_back(guess);
            attempts--;
        }

        if (all_of(guessed.begin(), guessed.end(), [](bool g) { return g; })) {
            cout << "\nCongratulations! You guessed the word: " << word << "\n";
            return 0;
        }
    }

    displayHangman(0);
    cout << "\nGame Over! The correct word was: " << word << "\n";
    return 0;
}
