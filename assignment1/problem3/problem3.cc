#include <iostream>
#include <stdlib.h>

using namespace std;

const int decisionMatrix[4][4] = {
        {20, 20, 0, 10},
        {10, 10, 10, 10},
        {0, 40, 0, 0},
        {10, 30, 0, 0}
};

struct customType{
    double decisionVal;
    int row;
};

string maximumRule(void){
    double temp = 0.0;
    string returnVal = "";
    customType a;
    a.decisionVal = 0.0;
    a.row = 0;

    for(int i = 0; i < sizeof(decisionMatrix)/sizeof(decisionMatrix[0]); i++) {
        for(int j = 0; j < sizeof(decisionMatrix[0])/sizeof(int); j++){
            temp += decisionMatrix[i][j]*0.25;
        }
        if(temp > a.decisionVal){
            a.decisionVal = temp;
            a.row = i;
        }
        temp = 0.0;
    }
    switch(a.row){
        case 0: returnVal = "a1";
                break;
        case 1: returnVal = "a2";
                break;
        case 2: returnVal = "a3";
                break;
        case 3: returnVal = "a4";
                break;
    }
    return returnVal;
}

string maximax(void){
    double temp = 0.0;
    string returnVal = "";
    customType a;
    a.decisionVal = 0.0;
    a.row = 0;
    for(int i = 0; i < sizeof(decisionMatrix)/sizeof(decisionMatrix[0]); i++) {
        for(int j = 0; j < sizeof(decisionMatrix[0])/sizeof(int); j++){
            temp = (temp < decisionMatrix[i][j]) ? decisionMatrix[i][j] : temp;
        }
        if(temp > a.decisionVal){
            a.decisionVal = temp;
            a.row = i;
        }
        temp = 0.0;
    }
    switch(a.row){
        case 0: returnVal = "a1";
                break;
        case 1: returnVal = "a2";
                break;
        case 2: returnVal = "a3";
                break;
        case 3: returnVal = "a4";
                break;
    }
    return returnVal;
}

string minimaxRegret(){
    double temp = 0.0;
    string returnVal = "";
    customType *a = new customType;
    int regretTable[sizeof(decisionMatrix)/sizeof(decisionMatrix[0])][sizeof(decisionMatrix[0])/sizeof(int)];
    int maxVals[sizeof(decisionMatrix[0])/sizeof(int)];
    a -> decisionVal = 0.0;
    a -> row = 0;

    cout << endl << "test1" << endl;

    for(int i = 0; i < sizeof(decisionMatrix[0])/sizeof(int); i++){
        for(int j = 0; j < sizeof(maxVals); j++){
            if(maxVals[i] < decisionMatrix[j][i])
                maxVals[i] = decisionMatrix[j][i];
        }
    }

    cout << endl << "test2" << endl;

    for(int i = 0; i < sizeof(decisionMatrix[0])/sizeof(int); i++){
        for(int j = 0; j < sizeof(maxVals); j++){
            regretTable[j][i] = maxVals[i] - decisionMatrix[j][i];
        }
    }

    cout << endl << "test3" << endl;

    for(int i = 0; i < sizeof(regretTable)/sizeof(regretTable[0]); i++) {
        for(int j = 0; j < sizeof(regretTable[0])/sizeof(int); j++){
            if(a -> decisionVal < regretTable[i][j])
                a -> decisionVal = regretTable[i][j];
                a -> row = i;
        }
    }

    cout << endl << "test4" << endl;

    cout << endl << "row: " << a -> row << endl;

    switch(a -> row){
        case 0: returnVal = "a1";
                break;
        case 1: returnVal = "a2";
                break;
        case 2: returnVal = "a3";
                break;
        case 3: returnVal = "a4";
                break;
    }

    cout << endl << "return val " << returnVal << endl;
    delete a;
    
    return returnVal;
}

int main(void)
{
    bool continueCalc = true;
    int userInput = 0;

    while(continueCalc){
        cout << endl << "Which decision rule would you like to use?" << endl << endl;
        cout << "a) Enter 1 for the maximum rule" << endl;
        cout << "b) Enter 2 for maximax" << endl;
        cout << "c) Enter 3 for minimax regret" << endl;
        cout << "d) Enter 4 for the optimism-pessimism rule" << endl;
        cout << "e) Enter 5 for the principle of insufficient reason" << endl << endl;
        cout << "Or 6 to exit..." << endl << endl;
        cin >> userInput;
        
        switch(userInput){
            case 1: cout << endl << "The act that should be chosen is " << maximumRule() << " according to the maximum rule." << endl;
                    break;
            case 2: cout << endl << "The act that should be chosen is " << maximax() << " according to the maximax rule." << endl;
                    break;
            case 3: cout << endl << "The act that should be chosen is " << minimaxRegret() << " according to the minimax regret rule." << endl;
                    break;
            case 4:
            case 5: 
            case 6: continueCalc = false;
                    break;
        }
    }

    return 0;
}