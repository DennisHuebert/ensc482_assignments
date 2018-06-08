#include <iostream>
#include <string>
#include <stdlib.h>
#include <cstdlib>
#include <GL/glut.h>

using namespace std;

void playRoulette(double betAmount, string betNumber){
    int rollNumber = (rand() % 38) - 1; //generate number between -1 and 36, -1 for 00 input
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

void createDecisionMatrix(){

}

void initRendering()
{
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0.0, 1400.0, 0.0, 1400.0);
}

void drawText(const char *text, int length, int x, int y){
    glMatrixMode(GL_PROJECTION);
    double *matrix = new double[16];
    glGetDoublev(GL_PROJECTION_MATRIX, matrix);
    glLoadIdentity();
    glOrtho(0, 1400, 0, 1400, -5, 5);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glPushMatrix();
    glLoadIdentity();
    glRasterPos2i(x, y);

    for(int i = 0; i < length; i++)
        glutBitmapCharacter(GLUT_BITMAP_9_BY_15, (int)text[i]);

    glPopMatrix();
    glMatrixMode(GL_PROJECTION);
    glLoadMatrixd(matrix);
    glMatrixMode(GL_MODELVIEW);

    delete[] matrix;
}


void lineSegmentsAndText(void){

    string text[] = {"0.02632", "0.97368", "Win", "Lose"};
    
    glClear(GL_COLOR_BUFFER_BIT);
    
    glColor3f(1.0, 0.0, 0.0);
    glBegin(GL_LINES);
        glVertex2i(300, 700);
        glVertex2i(1100, 1300);
    glEnd();

    glBegin(GL_LINES);
        glVertex2i(300, 700);
        glVertex2i(1100, 100);
    glEnd();

    drawText(text[0].data(), text[0].size(), 400, 1000);
    drawText(text[1].data(), text[1].size(), 400, 400);
    drawText(text[2].data(), text[2].size(), 1100, 1300);
    drawText(text[3].data(), text[3].size(), 1100, 100);

    glFlush();
}

int main(int argc, char** argv){
    double userBetAmount;
    string betNumber;
    bool continuePlaying = true;
    cout << endl << "~~~~~~~~~~~~~~~~~~~WELCOME TO THE ROULETTE GAME~~~~~~~~~~~~~~~~~~~";
    cout << "\n\n";
    cout << "Please enter the amount of money you wish to bet" << endl;
    cin >> userBetAmount;
    cout << "Please enter the number you wish to bet on" << endl;
    cin >> betNumber;
    playRoulette(userBetAmount, betNumber); 
    createDecisionMatrix();

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(1400, 1400);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Problem 4b - Drawing Decision Tree");
    initRendering();
    glutDisplayFunc(lineSegmentsAndText);
    glutMainLoop();

    return 0;
}