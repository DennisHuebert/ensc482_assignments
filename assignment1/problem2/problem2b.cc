
#include <iostream>
#include <stdlib.h>
#include <GL/glut.h>

using namespace std;
// The coordinates for the vertices of the cube
double x = 0.6;
double y = 0.6;
double z = 0.6;
float angle = 30.0;
unsigned int unsortedCubeColours[4][3];

void drawCubes()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(0.0, 0.0, -5.0);
    GLfloat ambientColor[] = {0.2, 0.2, 0.2, 1.0};
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientColor);
    GLfloat lightColor0[] = {0.5, 0.5, 0.5, 1.0};
    GLfloat lightPos0[] = {4.0, 0.0, 8.0, 1.0};
    glLightfv(GL_LIGHT0, GL_DIFFUSE, lightColor0);
    glLightfv(GL_LIGHT0, GL_POSITION, lightPos0);
    glRotatef(angle, 1.0, 1.0, 1.0);

    for(int i = 0; i < 4; i++){
        //Back
        //double i = 0.0;
        glBegin(GL_POLYGON);
            glColor3f(0.5, 0.3, 0.2);
            glVertex3f(x + i*10, -y, z);
            glVertex3f(x + i*10, y, z);
            glVertex3f(-(x + i*10), y, z);
            glVertex3f(-(x + i*10), -y, z);
        glEnd();

        //Front
        glBegin(GL_POLYGON);
            glColor3f(0.0, 0.5, 0.0);
            glVertex3f(-(x + i*10), y, -z);
            glVertex3f(-(x + i*10), -y, -z);
            glVertex3f(x + i*10, -y, -z);
            glVertex3f(x + i*10, y, -z);
        glEnd();

        //Left
        glBegin(GL_POLYGON);
            glColor3f(0.5, 0.5, 0.5);
            glVertex3f(-(x + i*10), -y, -z);
            glVertex3f(-(x + i*10), -y, z);
            glVertex3f(-(x + i*10), y, z);
            glVertex3f(-(x + i*10), y, -z);
        glEnd();

        //Right
        glBegin(GL_POLYGON);
            glColor3f(0.0, 0.0, 0.0);
            glVertex3f(x + i*10, -y, -z);
            glVertex3f(x + i*10, -y, z);
            glVertex3f(x + i*10, y, z);
            glVertex3f(x + i*10, y, -z);
        glEnd();

        //Top
        glBegin(GL_POLYGON);
            glColor3f(0.6, 0.0, 0.0);
            glVertex3f(x + i*10, y, z);
            glVertex3f(-(x + i*10), y, z);
            glVertex3f(-(x + i*10), y, -z);
            glVertex3f(x + i*10, y, -z);
        glEnd();

        //Bottom
        glBegin(GL_POLYGON);
            glColor3f(0.3, 0.0, 0.3);
            glVertex3f(-(x + i*10), -y, -z);
            glVertex3f(-(x + i*10), -y, z);
            glVertex3f(x + i*10, -y, z);
            glVertex3f(x + i*10, -y, -z);
        glEnd();
    }
    glFlush();
    glutSwapBuffers();
}

void update(int value)
{
    angle += 1.0f;
    if (angle > 360)
        angle -= 360;

    glutPostRedisplay();
    glutTimerFunc(25, update, 0);
}

void initRendering()
{
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_COLOR_MATERIAL);
    glClearColor(0.7f, 0.8f, 1.0f, 1.0f);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_NORMALIZE);
}

void handleResize(int w, int h)
{
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, (double)w / (double)h, 1.0, 200.0);
}

int main(int argc, char **argv)
{
    unsigned int input = 0;
    for(int i = 0; i < 4; i++) {
        cout << "Please enter the R value of cube " << i + 1 << ": ";
        cin >> input;
        unsortedCubeColours[i][0] = (input < 255) ? input : 255;
        cout << "Please enter the G value of cube " << i + 1 << ": ";
        cin >> input;
        unsortedCubeColours[i][1] = (input < 255) ? input : 255;
        cout << "Please enter the B value of cube " << i + 1 << ": ";
        cin >> input;
        unsortedCubeColours[i][2] = (input < 255) ? input : 255;

        /*cout << endl << "r: " << unsortedCubeColours[i][0] << endl;
        cout << "g: " << unsortedCubeColours[i][1] << endl;
        cout << "b: " << unsortedCubeColours[i][2] << endl;*/
    }

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(1400, 1400);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Problem 2b - Sorting Cubes");
    initRendering();
    glutDisplayFunc(drawCubes);
    glutReshapeFunc(handleResize);
    glutTimerFunc(25, update, 0);
    glutMainLoop();
    return 0;
}