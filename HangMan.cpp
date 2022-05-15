// CPP program to illustrate substr()
#include <string.h>
#include <iostream>
#include <map>
#include<cstdlib>
#include<dos.h> 
#include<vector>
#include<Windows.h>
#include<conio.h>
using namespace std;

string get_user_word() {
    string user_word;
    cout << "Please input your secret word: ";
    cin >> user_word;
    return user_word;
}

int get_count_number() {
    int guess_count;
    cout << "Guess_count: ";
    cin >> guess_count;
    return guess_count;
}

int update_guess_count(int &guess_count) {
    return guess_count - 1;
}

void print_guess_count(int& guess_count) {
    cout << "computer have " << guess_count << " guess left" << endl;
}
int get_word_length(string secret_word) {
    return secret_word.length();
}

string init_secret_word(int word_length) {
    string current_word;
    for (int i = 0; i < word_length; i++) {
        current_word += '-';
   }
    return current_word;
}

void update_current_word(char computer_guess, string secert_word,string& current_word) {
    for (int i = 0; i < secert_word.length(); i++) {
        if (computer_guess == secert_word[i]) {
            current_word[i] = computer_guess;
        }
    }
    cout << current_word << endl;
}

void init_simple_ai(vector<int>&char_list) {
    for (int i = 97; i <= 122; i++) {
        char_list.push_back(i);
    }
}

int get_random_number(int char_list_size) {
    srand(time(0));
    int random_index = rand() % char_list_size;
    return random_index;
}
char simple_ai(vector<int> &char_list) {
    int max = char_list.size()-1;
    int random_number = get_random_number(max);
    char computer_guess = char(char_list[random_number]);
    char_list.erase(char_list.begin() + random_number);
    return computer_guess;
}

void lose_condition(int guess_count,bool &lose) {
    if (guess_count == 0) {
        cout << "Computer lose!!!";
        lose = true;
    }
}

bool win_condition(string current_word, string secret_word) {
    if (current_word == secret_word) {
        return true;
    }
    return false;
}

bool check_computer_guess(char computer_guess, string secret_word) {
    for (int i = 0; i < secret_word.length(); i++) {
        if (computer_guess == secret_word[i]) {
            return true;
        }
    }
    return false;
}

void message_guess_right(char computer_guess,string &secret_word,string& current_word) {
    cout << "Secret word contain this character " << computer_guess << endl;
    update_current_word(computer_guess, secret_word, current_word);
    Sleep(2000);
}

void message_guess_wrong(char computer_guess, string& current_word, int &guess_count) {
    cout << "No character " << computer_guess << " in secret word" << endl;
    cout << "computer lose 1 guess time " << endl;
    guess_count = update_guess_count(guess_count);
    print_guess_count(guess_count);
    cout << "secret word: " << current_word << endl;
    Sleep(2000);
}

int main()
{
    string secret_word = get_user_word();
    int guess_count = get_count_number();
    int word_length = get_word_length(secret_word);
    string current_word= init_secret_word(word_length);
    cout << "Game start!" << endl;
    cout << "computer have " << guess_count << " times to guess!" << endl;
    vector<int> char_list={};
    init_simple_ai(char_list);
    bool is_lose = false;
    while (!is_lose) {
        char computer_guess = simple_ai(char_list);
        cout << "computer guess: " << computer_guess << endl;
        if (check_computer_guess(computer_guess, secret_word)) {
            message_guess_right(computer_guess, secret_word, current_word);
        }
        else {
            message_guess_wrong(computer_guess, current_word, guess_count);
        }
        lose_condition(guess_count, is_lose);
        if (win_condition(current_word,secret_word)) {
            cout << "computer win" << endl;
            break;
        }
    }
}
