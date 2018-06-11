
#include <iostream>
#include <stdlib.h>
#include <GL/glut.h>

using namespace std;
// The coordinates for the vertices of the cube (starting values)
double x = 0.3;
double y = 0.3;
double z = 0.3;
float angle = 30.0;
float CubeColours[4][3];
float sortedCubeColours[4][3];

float* sortCubeColours(float a[4], int left, int right){
    float pivot = a[(left + right) / 2];
    float temp;
    int i = left;
    int j = right;

    while(i <= j){
        while(a[i] < pivot)
            i++;
        while(a[j] > pivot)
            j--;
        if(i <= j){
            temp = a[i];
            a[i] = a[j];
            a[j] = temp;
            i++;
            j--;
        }
    }

    if(left < j)
        sortCubeColours(a, left, j);
    if(i < right)
        sortCubeColours(a, i, right);
    
    return a;
}

void drawCube(double xPos, double yPos, double zPos, float r, float g, float b){
    
    //glClear(GL_COLOR_BUFFER_BIT);
    glPushMatrix();
    glRotatef(angle, 1.0, 1.0, 1.0);
    glColor3f(r, g, b);

    //Back
    glBegin(GL_POLYGON);
        glVertex3f(xPos, -yPos, zPos);
        glVertex3f(xPos, yPos, zPos);
        glVertex3f(-xPos, yPos, zPos);
        glVertex3f(-xPos, -yPos, zPos);
    glEnd();

    //Front
    glBegin(GL_POLYGON);
        glVertex3f(-xPos, yPos, -zPos);
        glVertex3f(-xPos, -yPos, -zPos);
        glVertex3f(xPos, -yPos, -zPos);
        glVertex3f(xPos, yPos, -zPos);
    glEnd();

    //Left
    glBegin(GL_POLYGON);
        glVertex3f(-xPos , -yPos, -zPos);
        glVertex3f(-xPos, -yPos, zPos);
        glVertex3f(-xPos, yPos, zPos);
        glVertex3f(-xPos, yPos, -zPos);
    glEnd();

    //Right
    glBegin(GL_POLYGON);
        glVertex3f(xPos, -yPos, -zPos);
        glVertex3f(xPos, -yPos, zPos);
        glVertex3f(xPos, yPos, zPos);
        glVertex3f(xPos, yPos, -zPos);
    glEnd();

    //Top
    glBegin(GL_POLYGON);
        glVertex3f(xPos, yPos, zPos);
        glVertex3f(-xPos, yPos, zPos);
        glVertex3f(-xPos, yPos, -zPos);
        glVertex3f(xPos, yPos, -zPos);
    glEnd();

    //Bottom
    glBegin(GL_POLYGON);
        glVertex3f(-xPos, -yPos, -zPos);
        glVertex3f(-xPos, -yPos, zPos);
        glVertex3f(xPos, -yPos, zPos);
        glVertex3f(xPos, -yPos, -zPos);
    glEnd();
    glPopMatrix();
}

void drawCubes()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(-1.3, 0.0, -5.0);
    GLfloat ambientColor[] = {0.2, 0.2, 0.2, 1.0};
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientColor);
    GLfloat lightColor0[] = {0.5, 0.5, 0.5, 1.0};
    GLfloat lightPos0[] = {4.0, 0.0, 8.0, 1.0};
    glLightfv(GL_LIGHT0, GL_DIFFUSE, lightColor0);
    glLightfv(GL_LIGHT0, GL_POSITION, lightPos0);

    drawCube(x, x, x, CubeColours[0][0], CubeColours[0][1], CubeColours[0][2]);

    glTranslatef(1.0, 0.0, 0.0);
    drawCube(x, x, x, CubeColours[1][0], CubeColours[1][1], CubeColours[1][2]);

    glTranslatef(1.0, 0.0, 0.0);
    drawCube(x, x, x, CubeColours[2][0], CubeColours[2][1], CubeColours[2][2]);

    glTranslatef(1.0, 0.0, 0.0);
    drawCube(x, x, x, CubeColours[3][0], CubeColours[3][1], CubeColours[3][2]);

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
        CubeColours[i][0] = (input < 255) && (input > 0) ? input : 255;
        cout << "Please enter the G value of cube " << i + 1 << ": ";
        cin >> input;
        CubeColours[i][1] = (input < 255) && (input > 0) ? input : 255;
        cout << "Please enter the B value of cube " << i + 1 << ": ";
        cin >> input;
        CubeColours[i][2] = (input < 255) && (input > 0) ? input : 255;
    }

    float* red = new float[4];

    for(int i = 0; i < 4; i++)
        red[i] = CubeColours[i][0];

    red = sortCubeColours(red, 0, 3);
    cout << "\nSorted R values:\n";
    
    for(int i = 0; i < 4; i++)
        cout << "red: " << red[i] << endl;

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

    delete red;

    return 0;
}