#ifndef FUNCTIONS_H
#define FUNCTIONS_H

// Define ANSI Codes
#define RESET "\033[0m"   // reset attributes
#define BOLD "\033[1m"    // make text bold
#define GREEN "\033[2;32m"  // make text green
#define ORANGE "\033[38;5;220m" // make text orange 
#define BLACK "\033[90m"  // make text black

// Libraries
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <iomanip>
#include <ios>
#include <limits>
using namespace std;

// String for random word
string randomWord = "";

// String Functions
string toUpperString(string word){
  string rS = "     ";
  for (int i = 0; i < word.length(); i++) {
    rS[i] = toupper(word[i]);
  }
  return rS;
}

string toUpperCharString(string word)
{
  string rS=" ";
  rS[0] = toupper(word[0]);
  return rS;
}

// Menu Options

// Function to print Menu Options
void printMenuOptions() {
  cout << "=========================" << endl;
  cout <<"    WELCOME TO WORDLE.    " << endl;
  cout << "=========================" << endl << endl << endl;
  cout << "1. Play Wordle           " << endl;
  cout << "2. How to Play           " << endl;
  cout << "3. Statistics Summary    " << endl;
  cout << "4. Reset Statistics      " << endl;
  cout << "5. Exit                  " << endl << endl << endl;
  cout << "Select an option:        " << endl;
}

// Option 2: How to Play
void printRules() {
  cout << "=============================================" << endl;
  cout << "                 HOW TO PLAY                 " << endl;
  cout << "=============================================" << endl;
  cout << "Guess the Wordle in 6 tries.                 " << endl << endl << endl;
  cout << "HOW TO PLAY:\n- Each guess must be a valid 5 letter word.\n- The color of the tiles will change to show\n  you how close your guess was to the word." << endl << endl << endl;
  cout << GREEN << " --- " << RESET << " ---  ---  ---  --- " << endl;
  cout << GREEN << "| W |" << RESET << "| E || A || R || Y |" << endl;
  cout << GREEN << " --- " << RESET << " ---  ---  ---  --- " << endl;
  cout << BOLD << "W"<< RESET << " is in the word and in the correct spot. " << endl << endl;
  cout << " --- " << ORANGE << " --- " << RESET << " ---  ---  --- " << endl;
  cout << "| W |" << ORANGE << "| E |" << RESET << "| A || R || Y |" << endl;
  cout << " --- " << ORANGE << " --- " << RESET << " ---  ---  --- " << endl;
  cout << BOLD << "E" << RESET << " is in the word but in the wrong spot." << endl << endl;
  cout << " ---  ---  --- " << BLACK << " --- " << RESET << " --- " << endl;
  cout << "| W || E || A |" << BLACK << "| R |" << RESET << "| Y |" << endl;
  cout << " ---  ---  --- " << BLACK << " --- " << RESET << " --- " << endl;
  cout << BOLD << "U" << RESET << " is not in the word at any spot." << endl << endl << endl;
}

// Option 3: Statistics Summary
void printStatistics() {
  ifstream inFile("statistics.txt");
  vector<string> stats;

  string line;
  while(getline(inFile, line)) {
      stringstream ss(line);
      stats.push_back(line);
  }
  
  cout << "==========================" << endl;
  cout << "    STATISTICS SUMMARY    " << endl;
  cout << "==========================" << endl;
  cout << "Time Played:" << setw(14) << right << stats[0] << endl;
  cout << "Average Attempts:" << setw(9) << right << setprecision(2) << stod(stats[1]) << endl;
  cout << "Win Percentage:" << setw(10) << right << setprecision(3) << stod(stats[2]) << "%" << endl;
  cout << "Current Streak:" << setw(11) << right << stats[3] << endl;
  cout << "Longest Streak:" << setw(11) << right << stats[4] << endl << endl << endl;

  cout << "--------------------------" << endl;
  cout << "WORD     ATTEMPTS      WIN" << endl;
  cout << "--------------------------" << endl;

  ifstream fileIn("statistics2.txt");
  string fileLine;
  string element;
  vector<vector<string>> dataTwo;
  while(getline(fileIn, fileLine)) {
    vector<string> dataLine;
    string element;
    stringstream ss(fileLine);
    while(getline(ss, element, ',')) {
      dataLine.push_back(element);
    }
    dataTwo.push_back(dataLine);
  }

  for(int i = 0; i < dataTwo.size(); i++) {
    cout << dataTwo[i][0] << setw(12) << right << dataTwo[i][1] << setw(9) << right << dataTwo[i][2] << endl;
  }

  cout << endl << endl;

  inFile.close();
  fileIn.close();
}

// Function to update Statistics after end of game

void updateStatistics(string word, int attempts, string winLoss) {
  ofstream outFile("statistics2.txt", ios::app);
  outFile << toUpperString(word) << ',' << attempts << ',' << winLoss << endl;
  outFile.close();

  ifstream fileIn("statistics2.txt");

  string fileLine;
  vector<vector<string>> dataTwo;
  while(getline(fileIn, fileLine)) {
    vector<string> dataLine;
    string element;
    stringstream ss(fileLine);

    while(getline(ss, element, ',')) {
      dataLine.push_back(element);
    }
    dataTwo.push_back(dataLine);
  }
  double wordCount = 0;
  double totalAttempts = 0;
  for(int i = 0; i < dataTwo.size(); i++) {
    wordCount++;
    totalAttempts += stoi(dataTwo[i][1]);
  }

  // Get current data from stats file into a vector
  ifstream inFile("statistics.txt");
  vector<string> stats;
  string line;
  while(getline(inFile, line)) {
    stringstream ss(line);
    stats.push_back(line);
  }
  inFile.close();

  double timesPlayed = stod(stats[0]) + 1;
  double averageAttempts = totalAttempts / wordCount;
  float winPercentage;
  int currentStreak = stoi(stats[3]);
  int longestStreak = stoi(stats[4]);
  double totalWins = stod(stats[5]);

  if(winLoss == "YES") {  
    totalWins += 1;

    winPercentage = (totalWins / timesPlayed) * 100;

    currentStreak += 1;
    if(currentStreak > longestStreak) {
      longestStreak = currentStreak;
    }
  }

  else if(winLoss == "NO") {
    winPercentage = (totalWins / timesPlayed) * 100;

    if(currentStreak > longestStreak) {
      longestStreak = currentStreak;
    }
    currentStreak = 0;
  }

  // Update with new calculated stats in same file
  ofstream outFile2("statistics.txt");
  outFile2 << timesPlayed << "\n" << averageAttempts << "\n" << winPercentage << "\n" << currentStreak << "\n" << longestStreak << "\n" << totalWins;

  outFile2.close();
  outFile.close();
}

// Option 4: Ckear Statistics
void clearStatistics() {
  ofstream outFile1("statistics.txt");
  ofstream outFile2("statistics2.txt");

  outFile1 << "0\n0\n0\n0\n0\n0";
  outFile2 << "";
}

//Get random word from "words.txt"
void getRandomWord(string filename){
  srand(time(NULL));
  ifstream words(filename);
  int numOfLines = 0;
  string line;
  while (getline(words, line))
  {
    numOfLines++;
  }
  words.clear();
  words.seekg(0, ios::beg);

  int randomLineNum = (rand() % numOfLines) + 1;
  int currentLine = 1;
  while (getline(words, line))
  {
    if (currentLine == randomLineNum)
    {
      randomWord = line;
      break;
    }
    currentLine++;
  }
  words.close();
}

// Checks if userInput is a valid word
bool checkValidWord(string userInput) {
  if(userInput.length() != 5) {
    cout << "Not a valid word, please enter a valid word." << endl;
    return false;
  }

  ifstream allowed("words.txt");
  bool check = false;
  string line1;
  while (getline(allowed,line1)) {
    if(toUpperString(userInput) == toUpperString(line1)) {
      check = true;
    }
  }
  if (check) {
    return true;
  }
  else {
    cout << "Not a valid word, please enter a valid word." << endl;
    return false;
  }
}

// Main logic of the wordle game
void mainWordle() {
  system("clear");
  string userInput = "";
  int maxGuesses = 6;
  int guessCount = 0;
  while((guessCount != maxGuesses) && (userInput != randomWord)) {
    cin >> userInput;
    cout << "\033[1A\033[2K";
    string row1 = "";
    string row2 = "";
    string row3 = "";
    if (checkValidWord(userInput)) {
      for (int i = 0; i < randomWord.length(); i++) {
        char guessedChar = userInput[i];
        char toGuessChar = randomWord[i];
        string character;
        character += guessedChar;
        if (toupper(guessedChar) == toupper(toGuessChar)) {
          row1 += GREEN;
          row1 += " --- ";
          row2 += GREEN;
          row2 += "| ";
          row2 += toupper(guessedChar);
          row2 += " |";
          row3 += GREEN;
          row3 += " --- ";
          row1 += RESET;
          row2 += RESET;
          row3 += RESET;
        }
        else if(toUpperString(randomWord).find(toupper(guessedChar)) != string::npos) {
          row1 += ORANGE;
          row1 += " --- ";
          row2 += ORANGE;
          row2 += "| ";
          row2 += toupper(guessedChar);
          row2 += " |";
          row3 += ORANGE;
          row3 += " --- ";
          row1 += RESET;
          row2 += RESET;
          row3 += RESET;
        }
        else {
          row1 += BLACK;
          row1 += " --- ";
          row2 += BLACK;
          row2 += "| ";
          row2 += toupper(guessedChar);
          row2 += " |";
          row3 += BLACK;
          row3 += " --- ";
          row1 += RESET;
          row2 += RESET;
          row3 += RESET;
        }
      }
      cout << row1 << endl;
      cout << row2 << endl;
      cout << row3 << endl;
    }
    else {
      guessCount --;
    }
    guessCount++;
  }
  if (userInput == randomWord) {
    cout << "Splendid." << endl;
    updateStatistics(randomWord, guessCount, "YES");
  }
  else {
    cout << "The word was " << toUpperString(randomWord) << endl << endl;
    cout << "Better luck next time!" << endl << endl;
    updateStatistics(randomWord, guessCount, "NO");
  }
}

#endif