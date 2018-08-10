#include "problem1.h"

using namespace std;

//g++ problem1.cpp -lm -lglut -lGL -lGLU -o problem1

int main(int argc, char** argv){

    vector<float> amountPledged, numberOfBackers;

    amountPledged = readData(amountPledgedData);
    numberOfBackers = readData(numberOfBackersData);

    normalizedNumberOfBackers = normalizeData(20, 30000, numberOfBackers);
    normalizedAmountPledged = normalizeData(20, 30000, amountPledged);

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HIEGHT);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Problem 1");
    initRendering();
    glutDisplayFunc(drawClustering);
    glutMainLoop();

    return 1;
}

void initRendering()
{
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glEnable(GL_PROGRAM_POINT_SIZE);
    glPointSize(3.0);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(WINDOW_LEFT, WINDOW_RIGHT, WINDOW_BOTTOM, WINDOW_TOP);
}

vector<float> readData(const char* file){
    ifstream data;
    vector<float> dataVector;
    float number;
    data.open(file);

    if(data.is_open()){
        while(!data.eof()){
            data >> number;
            dataVector.push_back(number);
        }
    }
    data.close();
    return dataVector;
}

void drawText(const char *text, int length, int x, int y){
    glMatrixMode(GL_PROJECTION);
    double *matrix = new double[16];
    glGetDoublev(GL_PROJECTION_MATRIX, matrix);
    glLoadIdentity();
    glOrtho(WINDOW_LEFT, WINDOW_RIGHT, WINDOW_BOTTOM, WINDOW_TOP, -5, 5);
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

void drawClustering(){
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.0, 0.0, 0.0);

    glBegin(GL_LINES);
        glVertex2i(20, 0);
        glVertex2i(20, 1230);
    glEnd();

    glBegin(GL_LINES);
        glVertex2i(0, 20);
        glVertex2i(1380, 20);
    glEnd();

    glColor3f(0.0, 0.0, 1.0);

    glBegin(GL_POINTS);
        for(int i = 0; i < normalizedAmountPledged.size(); i++){
            if(normalizedAmountPledged.at(i) < 1380 && normalizedNumberOfBackers.at(i) < 1230)
                glVertex2f(normalizedAmountPledged.at(i), normalizedNumberOfBackers.at(i));
        }
    glEnd();

    glFlush();
    
}

vector<float> normalizeData(int lowerBound, int upperBound, vector<float> inputData){
    vector<float> normalizedData;
    float max = *max_element(inputData.begin(), inputData.end());
    float min = *min_element(inputData.begin(), inputData.end());
    float deltaMaxMin = max - min;
    float deltaLowerUpper = upperBound - lowerBound;
    float differenceXi;
    float normalData;
    for(int i = 0; i < inputData.size(); i++){
        differenceXi = inputData.at(i) - min;
        normalData = deltaLowerUpper*(differenceXi/deltaMaxMin)+lowerBound;
        normalizedData.push_back(normalData);
    }
    return normalizedData;
}




float euclideanDistance(vector<float> intput){
    float distance = 0;
    return distance;
}