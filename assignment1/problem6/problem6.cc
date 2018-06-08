#include <iostream>
#include <stdlib.h>

using namespace std;

// The payoff matrix below is structured in the following way
// The 2nd and 4th columns are player 2's responses for not confessing and confessing respectively
// The 1st and 3rd columns are player 1's responses for not confessing and confessing respectively
const int PAYOFFMATRIX[2][4] = { 
        {-2, -2, -10, -1},
        {-1, -10, -5, -5}
};

const int ROWS = sizeof(PAYOFFMATRIX)/sizeof(PAYOFFMATRIX[0]);
const int COLUMNS = sizeof(PAYOFFMATRIX[0])/sizeof(int);

struct customType{
    int position;
    int value;
};

int main(void){
    
    // Array of summed player one and player 2 utilities in this order
    // [P1 NC + P2 NC, P1 NC + P2 C, P1 C + P2 NC, P1 C + P2 C]
    int sumUtility[(COLUMNS / 2) * ROWS];
    customType temp;
    temp.position = 0;
    temp.value = -999999;

    for(int i = 0; i < ROWS; i++)
        for(int j = 0; j < COLUMNS; j += 2)
            sumUtility[i + j] = PAYOFFMATRIX[i][j] + PAYOFFMATRIX[i][j + 1];

    for(int i = 0; i < sizeof(sumUtility)/sizeof(int); i++){
        if(sumUtility[i] > temp.value){
            temp.value = sumUtility[i];
            temp.position = i;
        }
    }

    cout << "\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Prisonder's Dilemma ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n";
    cout << "The input payoff matrix is:\n\n";
    cout << "               Player 2\n";
    cout << "Player 1  | NC      |   C\n";
    cout << "       NC | " << PAYOFFMATRIX[0][0] << ", " << PAYOFFMATRIX[0][1] << "  | " << PAYOFFMATRIX[0][2] << ", " << PAYOFFMATRIX[0][3] << endl;
    cout << "       C  | " << PAYOFFMATRIX[1][0] << ", " << PAYOFFMATRIX[1][1] << " | " << PAYOFFMATRIX[1][2] << ", " << PAYOFFMATRIX[1][3] << endl << endl;

    switch(temp.position){
        case 0: cout << "The best outcome jointly for both players is for them to both not confess.\n\n";
                break;
        case 1: cout << "The best outcome jointly for both players is for player one to not confess and player two to confess.\n\n";
                break;
        case 2: cout << "The best outcome jointly for both players is for player one to confess and player two to not confess.\n\n";
                break;
        case 3: cout << "The best outcome jointly for both players is for them to both confess.\n\n";
                break;
        default: cout << "Game doesnt support more than two players or two game decisions.\n\n";
                 break;
    }

    return 0;
}