#include "problem7.h"

using namespace std;

Graph *myGraph = createGraph();

int main(int argc, char** argv){

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(1601, 897);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Problem 6");
    initRendering();
    glutDisplayFunc(draw);
    glutMouseFunc(mouseFunction);
    glutMainLoop();

    for(int i = 0; i < myGraph -> nodesAmount; i++)
        delete myGraph -> NodeArr.at(i);
    delete myGraph;

    return 0;
}

void draw() {

    string text[11] = {"Nesters", "Cornerstone", "ASB", "Blusson", "Saywell", "AQ", 
        "Library", "MBC", "Gym", "Westmall", "Click any node to highlight neighbouring paths"};


    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 0.0, 0.0);
    
    drawText(text[0].data(), text[0].size(), 1401, 460);    //Nesters
    drawText(text[1].data(), text[1].size(), 1201, 460);    //Cornerstone
    drawText(text[2].data(), text[2].size(), 1001, 280);    //ASB
    drawText(text[3].data(), text[3].size(), 1001, 610);    //Blusson
    drawText(text[4].data(), text[4].size(), 801, 610);     //Saywell
    drawText(text[5].data(), text[5].size(), 592, 460);     //AQ
    drawText(text[6].data(), text[6].size(), 401, 460);     //Library
    drawText(text[7].data(), text[7].size(), 401, 280);     //MBC
    drawText(text[8].data(), text[8].size(), 201, 280);     //GYM
    drawText(text[9].data(), text[9].size(), 201, 460);     //Westmall

    drawText(text[10].data(), text[10].size(), 580, 797);

    glColor3f(1.0, 1.0, 1.0);
    drawGraph(myGraph);
    glFlush();
}

void drawText(const char *text, int length, int x, int y){
    glMatrixMode(GL_PROJECTION);
    double *matrix = new double[16];
    glGetDoublev(GL_PROJECTION_MATRIX, matrix);
    glLoadIdentity();
    glOrtho(0.0, 1601.0, 0.0, 897.0, -5, 5);
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