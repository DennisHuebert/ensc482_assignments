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
    gluOrtho2D(0.0, 100.0, -650.0, 500.0);
}

void drawText(const char *text, int length, int x, int y){
    glMatrixMode(GL_PROJECTION);
    double *matrix = new double[16];
    glGetDoublev(GL_PROJECTION_MATRIX, matrix);
    glLoadIdentity();
    glOrtho(0, 100, -650, 500, -5, 5);
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

    string text1[] = {"q = 28.5714%", "0", "1", "2", "4", "Pay off to player one", "Moving up plays: q + 1", "Moving down plays: 4 - 3q"};
    string text2[] = {"q = 75%", "1", "-3", "2", "-1", "Pay off to player two", "Moving left plays: 1 - 4q", "Moving right plays: 3q - 1"};
    
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

    drawText(text1[0].data(), text1[0].size(), 70, 200);
    drawText(text1[2].data(), text1[2].size(), 0, 105);
    drawText(text1[4].data(), text1[4].size(), 0, 405);
    drawText(text1[2].data(), text1[2].size(), 98, 107);
    drawText(text1[3].data(), text1[3].size(), 98, 207);
    drawText(text1[5].data(), text1[5].size(), 0, 485);
    drawText(text1[6].data(), text1[6].size(), 37, 300);   
    drawText(text1[7].data(), text1[7].size(), 37, 117);

    drawText(text2[0].data(), text2[0].size(), 30, -300);
    drawText(text2[1].data(), text2[1].size(), 0, -195);
    drawText(text2[2].data(), text2[2].size(), 0, -385);
    drawText(text2[3].data(), text2[3].size(), 98, -190);
    drawText(text2[4].data(), text2[4].size(), 97, -587);
    drawText(text2[5].data(), text2[5].size(), 0, -15);
    drawText(text2[6].data(), text2[6].size(), 60, -300);
    drawText(text2[7].data(), text2[7].size(), 60, -435);  

    glColor3f(0.0, 1.0, 0.0);

    glBegin(GL_LINES);
        glVertex2i(0, 0);
        glVertex2i(100, 0);
    glEnd();

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

    cout << "\nPlayer 1 should play up: " << player1ProbUp*100 << "% of the time when player 2 plays left\n";
    cout << "Player 2 should play left: " << player2ProbLeft*100 << "% of the time when player 1 plays up\n\n";

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(700, 1150);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Problem 7 - Mixed Strategy Nash Equlibrium");
    initRendering();
    glutDisplayFunc(lineSegmentsAndText);
    glutMainLoop();

    return 0;
}