#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <map>
#include <vector>
#include <cmath>
#include <random>
#include <GL/glut.h>
#include <iomanip>

//This file takes an input dataset of the number of characters in Trump's tweets and draws a histogram
//It also compares it to the normal distrobution with the same mean and varience as trumps tweets

using namespace std;

const unsigned int BIN_WIDTH = 22;
const unsigned int BAR_SPACING = 75;
const unsigned int BAR_WIDTH = 50;

const float WINDOW_LEFT = -220.0;
const float WINDOW_RIGHT = 1360.0;
const float WINDOW_BOTTOM = -160.0;
const float WINDOW_TOP = 1100.0;

const int WINDOW_WIDTH = WINDOW_RIGHT - WINDOW_LEFT;
const int WINDOW_HEIGHT = WINDOW_TOP - WINDOW_BOTTOM;


//g++ problem1.cpp -lm -lglut -lGL -lGLU -o problem1

map <int, int> b;
map <int, int> normalDistValsMap;
map <int, int> normalDistVals;

double mean, varience, bhattacharyyaDistance;

vector<int> countChars();
void writeDataSetToFile(vector<int>);
map<int, int> putIntoBins(vector<int>);
float calculateMean(vector<int>);
float calculateVarience(float, vector<int>);
map<int, int> calcNormalDistVal(double, double);
double calcBhattacharyyaDistance(map<int, int>, map<int, int>);

map<int, int> calcAverage(map<int, int>);

void drawText(const char*, int, int, int);
void histogram(void);
void initRendering();

int main(int argc, char** argv){
    vector<int> numberOfChars = countChars();

    sort(numberOfChars.begin(), numberOfChars.end());
    writeDataSetToFile(numberOfChars);
    b = putIntoBins(numberOfChars);

    mean = calculateMean(numberOfChars);
    varience = calculateVarience(mean, numberOfChars);

    normalDistValsMap = calcNormalDistVal(mean, sqrt(varience));
    normalDistVals = calcAverage(normalDistValsMap);

    bhattacharyyaDistance = calcBhattacharyyaDistance(b, normalDistVals);
    
    cout << endl;
    cout << "Bhattacharyya Distance = " << bhattacharyyaDistance << endl;
    cout << "mean = " << mean << endl;
    cout << "varience = " << varience << endl << endl;

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Problem 1 - Number of characters in Trump's Tweets");
    initRendering();
    glutDisplayFunc(histogram);
    glutMainLoop();

    return 1;
}

//This function is responsible for drawing out the histogram
void histogram() {

    //array of strings to print
    string text[] = {"0", "Frequency", "Number of characters per Tweet", "Bhattacharyya Distance: " + 
        to_string(bhattacharyyaDistance), "Mean: " + to_string(mean), "Standard Deviation: " + to_string(sqrt(varience))};

    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(0.0, 0.0, 0.0);

    glBegin(GL_LINES);
        glVertex2i(0, 0);
        glVertex2i(0, -15);
    glEnd();

    glBegin(GL_LINES);
        glVertex2i(0, 0);
        glVertex2i(-15, 0);
    glEnd();

    drawText(text[0].data(), text[0].size(), -8, -27);
    drawText(text[0].data(), text[0].size(), -45, -5);
    drawText(text[1].data(), text[1].size(), -150, 500);
    drawText(text[2].data(), text[2].size(), 420, -100);
    drawText(text[3].data(), text[3].size(), 0, 1000);
    drawText(text[4].data(), text[4].size(), 275, 1000);
    drawText(text[5].data(), text[5].size(), 425, 1000);
        
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

    glColor3f(0.0, 0.0, 1.0);

    glBegin (GL_POINTS);
    for(auto p: normalDistValsMap) {
        if(p.first > 0 && p.first*2.9 < 1200 && p.second * 15 < 950)
            glVertex2f (p.first*2.9, p.second * 15);
    }
    glEnd ();

    glColor3f(1.0, 0.0, 0.0);

    glBegin(GL_LINES);
        glVertex2f(0.0, normalDistVals[0]*15);
        glVertex2f((float)BAR_WIDTH, normalDistVals[0]*15);
    glEnd();

    glBegin(GL_LINES);
    for(int i = 1; i < b.size(); i++) {
        glVertex2f((float)BAR_SPACING*i, normalDistVals[i]*15);
        glVertex2f((float)(BAR_SPACING*i + BAR_WIDTH), normalDistVals[i]*15);
    }
    glEnd();
    
    glColor3f(0.0, 0.0, 0.0);

    glBegin(GL_LINES);
        glVertex2i(0, 0);
        glVertex2i(0, 950);
    glEnd();

    glBegin(GL_LINES);
        glVertex2i(0, 0);
        glVertex2i(1200, 0);
    glEnd();

    glFlush();
}

//Function that draws text to the screen
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

void initRendering()
{
    //glClearColor(0.635, 0.686, 0.769, 0.0);
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glEnable(GL_PROGRAM_POINT_SIZE);
    glPointSize(5.0);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(WINDOW_LEFT, WINDOW_RIGHT, WINDOW_BOTTOM, WINDOW_TOP);
}

//Take the input textfile and counts the number of characters perline or per tweet
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

//write the lengths of each tweet to a separate textfile
void writeDataSetToFile(vector<int> a){
    ofstream lengthOfTrumpTweets("LengthOfTrumpTweets.txt");
    for(int i = 0; i < a.size(); i++)
        lengthOfTrumpTweets << a.at(i) << endl;
    lengthOfTrumpTweets.close();
}

//Counts the number of tweets that fall within a certain bin width (22 in this case)
//Have to do this because I am dealing with a large data set
map<int, int> putIntoBins(vector<int> data){
    int currentBinMax = BIN_WIDTH;
    map<int, int> bins;
    int count = 0;

    cout << "input vector size: " << data.size() << endl;

    for(int i = 0; i < data.size(); i++){
        if(data.at(i) < currentBinMax){
            count++;
        } else {
            bins.insert(pair<int, int>(bins.size(), count));
            currentBinMax += BIN_WIDTH;
            count = 0;
        }
    }
    cout << "output map size: " << bins.size() << endl;
    return bins;
}

//Calculate the mean of the number of tweets
float calculateMean(vector<int> data){
    float mean = 0.0;
    int sum = 0;
    for(int i = 0; i < data.size(); i++)
        sum += data[i];
    if(data.size() != 0)
        mean = (float)sum/(float)data.size();
    return mean;
}

//Calulcate the varience of the number of tweets
float calculateVarience(float mean, vector<int> data) {
    float varience = 0.0;
    int sumSquared = 0;
    for(int i = 0; i < data.size(); i++)
        sumSquared += pow(data[i], 2); 
    varience = ((float)sumSquared/(float)data.size()) - pow(mean, 2);
    return varience;
}

//Generate a normal dist with the same mean and standard deviation as the dataset I am dealing with
map<int, int> calcNormalDistVal(double mean, double std) {
    random_device rd{};
    mt19937 gen{rd()};
    normal_distribution<> d{mean, std};
    map<int, int> hist{};
    for(int n = 0; n < 10000; ++n) 
        ++hist[std::round(d(gen))];
    return hist;
}

//This function calculates the avaerage value of the normal dist within certain bin sizes (22 in this case)
map<int, int> calcAverage(map<int, int> a) {
    map<int, int> averagedMap;
    int temp, counter;
    int width = BIN_WIDTH;

    for(auto i: a){
        if(i.first <= width && i.first > 0){
            temp += i.second;
            counter++;
        } else if(i.first > 0) {
            if(counter > 0)
                averagedMap.insert(pair<int, int>(averagedMap.size(), temp/counter));
            counter = 0;
            temp = 0;
            width += BIN_WIDTH;
        }
    }
    return averagedMap;
}

//This function calulates the Bhattacharyya Distance between the histogram of the data set
//and the normal dist following the formula
double calcBhattacharyyaDistance(map<int, int> a, map<int, int> b){
    double bhattacharyyaDistance = 0.0;
    for(int i = 0; i < a.size(); i++) {
        if(a[i] && b[i] > 0)
            bhattacharyyaDistance += sqrt(a[i]*b[i]);
    }
    return bhattacharyyaDistance;
}