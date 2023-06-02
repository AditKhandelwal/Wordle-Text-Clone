#include "functions.h"

//Libraries
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <stdlib.h>
#include <iomanip>
#include <limits>

int main() {
  string userInputMainMenu = "";
  system("clear");
  while (userInputMainMenu != "5") {
    printMenuOptions();
    cin >> userInputMainMenu;
    if (userInputMainMenu == "1") {
        getRandomWord("words.txt");
    }
    else if (userInputMainMenu == "2") {
        system("clear");
        printRules();
    }
    else if (userInputMainMenu == "3") {
        system("clear");
        printStatistics();
    }
    else if (userInputMainMenu == "4") {
        system("clear");
        clearStatistics();
        printStatistics();
    }
    else if (userInputMainMenu == "5") {
        system("clear");
        exit(0);  
    }
    else {
        cout << "Not a valid option. Try again.";
    }

    cout << "Press [enter] to continue" << endl;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
    system("clear");
  }

  return 0;
}