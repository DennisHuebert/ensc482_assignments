#include <iostream>
#include <string>
#include <stdlib.h>
#include <cstdlib>
#include <GL/glut.h>

using namespace std;

void playRoulette(double betAmount, string betNumber){
    int rollNumber = (rand() % 38) - 1;
    int intBetNumber;

    if(betNumber == "00")
        intBetNumber = -1;
    else
        intBetNumber = stoi(betNumber);
    
    if(rollNumber == intBetNumber){
        cout << "\nWINNER WINNER CHICKEN DINNER" << endl;
        cout << "You have won $" << betAmount*35 + betAmount << "!" << endl;
    } else {
        cout << "\nSORRY please try again" << endl;
    }
}

int main(int argc, char **argv){
    double userBetAmount;
    string betNumber;
    bool continuePlaying = true;
    cout << endl << "~~~~~~~~~~~~~~~~~~~WELCOME TO THE ROULETTE GAME~~~~~~~~~~~~~~~~~~~";
    while(continuePlaying){
        cout << "\n\n";
        cout << "Please enter the amount of money you wish to bet" << endl;
        cin >> userBetAmount;
        cout << "Please enter the number you wish to bet on" << endl;
        cin >> betNumber;
        playRoulette(userBetAmount, betNumber);
    }
    return 0;
}