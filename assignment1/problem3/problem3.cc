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

string decideReturnVal(int a){
    string returnVal = "";
    switch(a){
        case 0: returnVal = "a1";
                break;
        case 1: returnVal = "a2";
                break;
        case 2: returnVal = "a3";
                break;
        case 3: returnVal = "a4";
                break;
        default: returnVal = "ERROR";
    }
    return returnVal;
}

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
    returnVal = decideReturnVal(a.row);
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
    returnVal = decideReturnVal(a.row);
    return returnVal;
}

int** createRegretTable(){
    
    int** regretTable = 0;
    regretTable = new int*[sizeof(decisionMatrix)/sizeof(decisionMatrix[0])];
    for(int i = 0; i < sizeof(decisionMatrix[0])/sizeof(int); i++){
        regretTable[i] = new int[sizeof(decisionMatrix[0])/sizeof(int)];
    }

    int maxColVals[sizeof(decisionMatrix[0])/sizeof(int)] = {0, 0, 0, 0};

    for(int i = 0; i < sizeof(decisionMatrix[0])/sizeof(int); i++){
        for(int j = 0; j < sizeof(decisionMatrix)/sizeof(decisionMatrix[0]); j++){
            if(maxColVals[i] < decisionMatrix[j][i])
                maxColVals[i] = decisionMatrix[j][i];
        }
    }

    for(int i = 0; i < sizeof(decisionMatrix[0])/sizeof(int); i++){
        for(int j = 0; j < sizeof(decisionMatrix)/sizeof(decisionMatrix[0]); j++){
            regretTable[j][i] = maxColVals[i] - decisionMatrix[j][i];
        }
    }

    return regretTable;
}

string minimaxRegret(){
    int** regretTable = createRegretTable();
    string returnVal = "";
    int temp = -9999;
    customType a;
    a.decisionVal = 9999;

    for(int i = 0; i < sizeof(decisionMatrix)/sizeof(decisionMatrix[0]); i++) {
        for(int j = 0; j < sizeof(decisionMatrix[0])/sizeof(int); j++){
            if(temp < regretTable[i][j])
                temp = regretTable[i][j];
        }
        if(a.decisionVal > temp){
            a.decisionVal = temp;
            a.row = i;
        }
        temp = -9999;
    }
    
    for(int i = 0; i < sizeof(decisionMatrix)/sizeof(decisionMatrix[0]); i++)
        delete[] regretTable[i];

    delete[] regretTable;
    regretTable = NULL;

    returnVal = decideReturnVal(a.row);

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
        cout << "Or any other key to exit..." << endl << endl;
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
            default: continueCalc = false;
                    break;
        }
    }

    return 0;
}