#include <bits/stdc++.h>
using namespace std;

// ANSI color codes
const string RESET = "\033[0m";
const string RED = "\033[31m";
const string GREEN = "\033[32m";
const string YELLOW = "\033[33m";
const string BLUE = "\033[34m";
const string MAGENTA = "\033[35m";
const string CYAN = "\033[36m";
const string WHITE = "\033[37m";


const vector<string> colors = {RED, GREEN, YELLOW, BLUE, MAGENTA, CYAN, WHITE};


void place_word_horizontal(vector<vector<string>>& crossworld, const string& word, int row, int col) {
    for (int j = 0; j < word.size(); j++) {
        crossworld[row][col + j] = string(1, word[j]);
    }
}


void place_word_vertical(vector<vector<string>>& crossworld, const string& word, int row, int col) {
    for (int i = 0; i < word.size(); i++) {
        crossworld[row + i][col] = string(1, word[i]);
    }
}


void place_word_diagonal(vector<vector<string>>& crossworld, const string& word, int row, int col) {
    for (int i = 0; i < word.size(); i++) {
        crossworld[row + i][col + i] = string(1, word[i]);
    }
}


bool can_place_horizontal(const vector<vector<string>>& crossworld, const string& word, int row, int col) {
    if (col + word.size() > crossworld[0].size()) return false;
    for (int j = 0; j < word.size(); j++) {
        if (crossworld[row][col + j] != "*" && crossworld[row][col + j] != string(1, word[j])) return false;
    }
    return true;
}


bool can_place_vertical(const vector<vector<string>>& crossworld, const string& word, int row, int col) {
    if (row + word.size() > crossworld.size()) return false;
    for (int i = 0; i < word.size(); i++) {
        if (crossworld[row + i][col] != "*" && crossworld[row + i][col] != string(1, word[i])) return false;
    }
    return true;
}


bool can_place_diagonal(const vector<vector<string>>& crossworld, const string& word, int row, int col) {
    if (row + word.size() > crossworld.size() || col + word.size() > crossworld[0].size()) return false;
    for (int i = 0; i < word.size(); i++) {
        if (crossworld[row + i][col + i] != "*" && crossworld[row + i][col + i] != string(1, word[i])) return false;
    }
    return true;
}


void print_crossword(const vector<vector<string>>& crossworld) {
    int rows = crossworld.size();
    int cols = crossworld[0].size();

    cout << "---------------------" << endl; 
    for (int i = 0; i < rows; i++) {
        cout << "| "; 
        for (int j = 0; j < cols; j++) {
          
            string color = colors[i % colors.size()]; 
            if (crossworld[i][j] == "*") {
                cout << color << crossworld[i][j] << RESET << " "; 
            } else {
               
                color = colors[j % colors.size()];
                cout << color << crossworld[i][j] << RESET << " "; 
            }
        }
        cout << "|" << endl; 
    }
    cout << "---------------------" << endl; 
}

int main() {
    int n;
    cout << "Enter the number of words in Crossworld: ";
    cin >> n;
    cout << "Enter the words to be added to the Crossworld:" << endl;
    
    vector<string> words(n);
    for (int i = 0; i < n; i++) {
        cin >> words[i];
    }
    
    int r = n * 2, c = n * 2;
    vector<vector<string>> crossworld(r, vector<string>(c, "*"));

    for (int i = 0; i < n; i++) {
        bool placed = false;

        
        for (int row = 0; row < r && !placed; row++) {
            for (int col = 0; col < c && !placed; col++) {
                if (i % 3 == 0 && can_place_horizontal(crossworld, words[i], row, col)) {
                    place_word_horizontal(crossworld, words[i], row, col);
                    placed = true;
                } else if (i % 3 == 1 && can_place_vertical(crossworld, words[i], row, col)) {
                    place_word_vertical(crossworld, words[i], row, col);
                    placed = true;
                } else if (i % 3 == 2 && can_place_diagonal(crossworld, words[i], row, col)) {
                    place_word_diagonal(crossworld, words[i], row, col);
                    placed = true;
                }
            }
        }

      
        if (!placed) {
            cout << "Could not place the word: " << words[i] << endl;
        }
    }

    print_crossword(crossworld); 
    
    return 0;
}
