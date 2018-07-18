#include "problem6.h"

using namespace std;

//g++ problem6.cpp -lm -lglut -lGL -lGLU -o problem6

GLuint texture[1];

int LoadGLTextures(){
    texture[0] = SOIL_load_OGL_texture("SfuMap.jpg", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);

    if(texture[0] == 0) 
        return false;

    glBindTexture(GL_TEXTURE_2D, texture[0]);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);

    return true;                                       
}

static void Draw(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();                           
    glTranslatef(0.0f,0.0f,-5.0f);  
	glBindTexture(GL_TEXTURE_2D, texture[0]);

	glBegin(GL_QUADS);
        glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f,  1.0f);
        glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f, -1.0f,  1.0f);
        glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f,  1.0f,  1.0f);
        glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,  1.0f,  1.0f);
	glEnd();

	glutSwapBuffers();
    glFlush();
}

int main(int argc, char** argv){

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(1601, 897);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Problem 6");
    initRendering();
    LoadGLTextures();
    glutDisplayFunc(Draw);
    glutMainLoop();

    return 0;
}

/*void draw() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.0, 0.0, 0.0);
    glFlush();
}*/

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

void initRendering(){
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0.0, 1601.0, 0.0, 897.0);
}