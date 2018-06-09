#include <iostream>
#include <stdlib.h>
#include <cstdlib>
#include <GL/glut.h>

using namespace std;

const int GAMEMATRIX[2][4] = { 
        {2, -3, 1, 2},
        {1, 1, 4, -1}
};

const int PLAYER_ONE_EU[4][2] = {
            {0, GAMEMATRIX[0][2]*100},
            {100, GAMEMATRIX[0][0]*100},
            {0, GAMEMATRIX[1][2]*100},
            {100, GAMEMATRIX[1][0]*100}
    };

const int PLAYER_TWO_EU[4][2] = {
        {0, GAMEMATRIX[1][1]*100 - 300},
        {100, GAMEMATRIX[0][1]*100 - 300},
        {0, GAMEMATRIX[1][3]*100 - 300},
        {100, GAMEMATRIX[0][2]*100 - 300}
};

const int ROWS = sizeof(GAMEMATRIX)/sizeof(GAMEMATRIX[0]);
const int COLUMNS = sizeof(GAMEMATRIX[0])/sizeof(int);

void initRendering()
{
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(-700.0, 700.0, -700.0, 700.0);
}

void drawText(const char *text, int length, int x, int y){
    glMatrixMode(GL_PROJECTION);
    double *matrix = new double[16];
    glGetDoublev(GL_PROJECTION_MATRIX, matrix);
    glLoadIdentity();
    glOrtho(-700, 700, -700, 700, -5, 5);
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
    
    for(int i = 0; i < sizeof(PLAYER_ONE_EU)/sizeof(PLAYER_ONE_EU[0]); i += 2){
        for(int j = 0; j < sizeof(PLAYER_ONE_EU[0])/sizeof(int); j += 2){
            glBegin(GL_LINES);
                glVertex2i(PLAYER_ONE_EU[i][j], PLAYER_ONE_EU[i][j + 1]);
                glVertex2i(PLAYER_ONE_EU[i + 1][j], PLAYER_ONE_EU[i + 1][j + 1]);
            glEnd(); 
        }
    }

    for(int i = 0; i < sizeof(PLAYER_ONE_EU)/sizeof(PLAYER_ONE_EU[0]); i += 2){
        for(int j = 0; j < sizeof(PLAYER_ONE_EU[0])/sizeof(int); j += 2){
            glBegin(GL_LINES);
                glVertex2i(PLAYER_TWO_EU[i][j], PLAYER_TWO_EU[i][j + 1]);
                glVertex2i(PLAYER_TWO_EU[i + 1][j], PLAYER_TWO_EU[i + 1][j + 1]);
            glEnd();
        }
    }
    glFlush();
}

int main(int argc, char** argv){
    double  player1ProbUp, player1ProbDown, 
            player2ProbLeft, player2ProbRight = 0.0;
    
    //Equilibrium probabilities
    player1ProbUp = (double)(GAMEMATRIX[1][3] - GAMEMATRIX[1][1])/(double)(GAMEMATRIX[0][1] - 
                    GAMEMATRIX[1][1] - GAMEMATRIX[0][3] + GAMEMATRIX[1][3]);
    player1ProbDown = 1 - player1ProbUp;
    
    player2ProbLeft =   (double)(GAMEMATRIX[1][2] - GAMEMATRIX[1][0])/(double)(GAMEMATRIX[0][0] - 
                        GAMEMATRIX[1][0] - GAMEMATRIX[0][2] + GAMEMATRIX[1][2]);
    player2ProbRight = 1 - player2ProbLeft;

    cout << "\nplayer 1 prob up: " << player1ProbUp*100 << "%\n";
    cout << "player 1 prob down: " << player1ProbDown*100 << "%\n";
    
    cout << "player 2 prob left: " << player2ProbLeft*100 << "%\n";
    cout << "player 2 prob right: " << player2ProbRight*100 << "%\n\n";

    /*for(int i = 0; i < sizeof(PLAYER_ONE_EU)/sizeof(PLAYER_ONE_EU[0]); i++){
        for(int j = 0; j < sizeof(PLAYER_ONE_EU[0])/sizeof(int); j++){
            cout << PLAYER_ONE_EU[i][j] << ", ";
        }
        cout << endl;
    }*/

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(1400, 1400);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Problem 7 - Mixed Strategy Nash Equlibrium");
    initRendering();
    glutDisplayFunc(lineSegmentsAndText);
    glutMainLoop();

    return 0;
}