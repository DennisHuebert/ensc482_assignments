#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <map>
#include <vector>
#include <cmath>
#include <GL/glut.h>

using namespace std;

const unsigned int BIN_WIDTH = 22;
const unsigned int BAR_SPACING = 75;
const unsigned int BAR_WIDTH = 50;

//g++ problem1.cpp -lm -lglut -lGL -lGLU -o problem1

map <int, int> b;
vector<int> countChars();
void writeDataSetToFile(vector<int>);
map<int, int> putIntoBins(vector<int>);
double calculateMean(vector<int>);
double calculateVarience(double, vector<int>);
void drawText(const char*, int, int, int);
void histogram(void);
void initRendering();

int main(int argc, char** argv){

    vector<int> numberOfChars = countChars();
    sort(numberOfChars.begin(), numberOfChars.end());
    writeDataSetToFile(numberOfChars);
    b = putIntoBins(numberOfChars);

    double mean = calculateMean(numberOfChars);
    double varience = calculateVarience(mean, numberOfChars);

    cout << endl;
    for(int i = 0; i < b.size(); i++){
        cout << "map " << i << ": " << b.at(i) << endl;
    }
    cout << endl;
    cout << "mean = " << mean << endl << endl;
    cout << "varience = " << varience << endl << endl;

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(1280, 1050);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Problem 1 - Number of characters in Trump's Tweets");
    initRendering();
    glutDisplayFunc(histogram);
    glutMainLoop();

    return 1;
}

void histogram() {

    string text = "0";
    int counter = 0;

    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(0.0, 0.0, 0.0);

    glBegin(GL_LINES);
        glVertex2i(0, 0);
        glVertex2i(0, 950);
    glEnd();

    glBegin(GL_LINES);
        glVertex2i(0, 0);
        glVertex2i(1200, 0);
    glEnd();

    glBegin(GL_LINES);
        glVertex2i(0, 0);
        glVertex2i(0, -15);
    glEnd();

    glBegin(GL_LINES);
        glVertex2i(0, 0);
        glVertex2i(-15, 0);
    glEnd();

    drawText(text.data(), text.size(), -8, -27);
    drawText(text.data(), text.size(), -45, -5);
        
    for(int i = 0; i < b.size(); i++){
        glBegin(GL_LINES);
            glVertex2i(BAR_WIDTH + i*BAR_SPACING, 0);
            glVertex2i(BAR_WIDTH + i*BAR_SPACING, -15);
        glEnd();

        drawText(to_string(BIN_WIDTH*(i + 1)).data(), to_string(BIN_WIDTH*(i + 1)).size(), BAR_WIDTH + i*BAR_SPACING - 8, -27);
    }

    glColor3f(0.498, 0.431, 0.392);

    for(int i = 0; i < b.size(); i++)
        glRecti(i*BAR_SPACING, 0, BAR_WIDTH + i*BAR_SPACING, b[i]*2);

    glColor3f(0.0, 0.0, 0.0);
    
    for(int i = 50; i <= 950; i += 50){
        glBegin(GL_LINES);
            glVertex2i(-15, i);
            glVertex2i(1200, i);
        glEnd();
        drawText(to_string(i/2).data(), to_string(i/2).size(), -45, i - 5);
    }

    glFlush();
}

void drawText(const char *text, int length, int x, int y){
    glMatrixMode(GL_PROJECTION);
    double *matrix = new double[16];
    glGetDoublev(GL_PROJECTION_MATRIX, matrix);
    glLoadIdentity();
    glOrtho(-80.0, 1200.0, -50.0, 1000.0, -5, 5);
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


void initRendering()
{
    glClearColor(0.635, 0.686, 0.769, 0.0);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(-80.0, 1200.0, -50.0, 1000.0);
}

vector<int> countChars() {
    vector<int> charCount;
    ifstream trumpTweets;
    trumpTweets.open("TrumpTweets.txt");
    string line;

    if(trumpTweets.is_open()){
        while(getline(trumpTweets, line))
            charCount.push_back(line.size());
    }
    trumpTweets.close();
    return charCount;
}

void writeDataSetToFile(vector<int> a){
    ofstream lengthOfTrumpTweets("LengthOfTrumpTweets.txt");
    for(int i = 0; i < a.size(); i++)
        lengthOfTrumpTweets << a.at(i) << endl;
    lengthOfTrumpTweets.close();
}

map<int, int> putIntoBins(vector<int> data){
    int currentBinMax = BIN_WIDTH;
    map<int, int> bins;
    int count = 0;

    for(int i = 0; i < data.size(); i++){
        if(data.at(i) < currentBinMax){
            count++;
        } else {
            bins.insert(pair<int, int>(bins.size(), count));
            currentBinMax += BIN_WIDTH;
            count = 0;
        }
    } 
    return bins;
}

double calculateMean(vector<int> data){
    double mean = 0.0;
    int sum = 0;
    for(int i = 0; i < data.size(); i++)
        sum += data.at(i);
    if(data.size() != 0)
        mean = (double)sum/(double)data.size();
    return mean;
}

double calculateVarience(double mean, vector<int> data) {
    double varience = 0.0;
    int sumSquared = 0;

    for(int i = 0; i < data.size(); i++)
        sumSquared += pow(data.at(i), 2);
        
    varience = ((double)sumSquared/(double)data.size()) - pow(mean, 2);
    return varience;
}