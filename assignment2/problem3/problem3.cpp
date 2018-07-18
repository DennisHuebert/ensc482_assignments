#include "problem3.h"

using namespace std;

//g++ problem1.cpp -lm -lglut -lGL -lGLU -o problem1

int main(int argc, char** argv){

    vector<float> goals, amountPledged, numberOfBackers;

    goals = readData(goalData);
    amountPledged = readData(amountPledgedData);
    numberOfBackers = readData(numberOfBackersData);

    normalizedAmountPledged = normalizeData(50, 350, amountPledged);
    normalizedGoals = normalizeData(50, 350, goals);
    normalizedNumberOfBackers = normalizeData(50, 350, numberOfBackers);

    double amountPledgedMean = calculateMean(normalizedAmountPledged);
    double goalMean = calculateMean(normalizedGoals);
    double numberOfBackersMean = calculateMean(normalizedNumberOfBackers);

    double amountPledgedVarience = calculateVarience(amountPledgedMean, normalizedAmountPledged);
    double goalVarience = calculateVarience(goalMean, normalizedGoals);
    double numberOfBackersVarience = calculateVarience(numberOfBackersVarience, normalizedNumberOfBackers);

    rGoalsNumberOfBackers = calculateCorrelationCoefficient(normalizedGoals, 
        normalizedNumberOfBackers, goalMean, numberOfBackersMean);

    rAmountPledgedNumberOfBackers = calculateCorrelationCoefficient(normalizedAmountPledged, 
        normalizedNumberOfBackers, amountPledgedMean, numberOfBackersMean);

    rAmountPledgedGoals = calculateCorrelationCoefficient(normalizedAmountPledged, 
        normalizedGoals, amountPledgedMean, goalMean);
    
    leastSquaresGoalsNumberOfBackers = calculateLeastSquaresCoeff(rGoalsNumberOfBackers, goalMean, 
        numberOfBackersMean, sqrt(goalVarience), sqrt(numberOfBackersVarience));
    
    leastSquaresAmountPledgedNumberOfBackers = calculateLeastSquaresCoeff(rAmountPledgedNumberOfBackers, amountPledgedMean, 
        numberOfBackersMean, sqrt(amountPledgedVarience), sqrt(numberOfBackersVarience));

    leastAmountPledgedGoals = calculateLeastSquaresCoeff(rAmountPledgedGoals, amountPledgedMean, 
        goalMean, sqrt(amountPledgedVarience), sqrt(goalVarience));
    
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HIEGHT);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Problem 3");
    initRendering();
    glutDisplayFunc(drawPlots);
    glutMainLoop();

    return 0;
}

void drawPlots(){
    string text[3] = {"Goal Amount", "Number of Backers", "Amount Pledged"};

    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 1.0, 1.0);
    drawBoxMatrix(3, 50, 300);

    glBegin(GL_POINTS);
        for(int i = 0; i < normalizedAmountPledged.size(); i++) {
            glVertex2f(normalizedAmountPledged.at(i), normalizedNumberOfBackers.at(i));
            glVertex2f(normalizedGoals.at(i), normalizedNumberOfBackers.at(i) + 350);
            glVertex2f(normalizedAmountPledged.at(i) + 350, normalizedGoals.at(i));
        }
    glEnd();

    glColor3f(1.0, 0.0, 0.0);

    glBegin(GL_LINES);
        glVertex2f(50.0, leastSquaresAmountPledgedNumberOfBackers.at(0) + leastSquaresAmountPledgedNumberOfBackers.at(1)*50.0);
        glVertex2f(350.0, leastSquaresAmountPledgedNumberOfBackers.at(0) + leastSquaresAmountPledgedNumberOfBackers.at(1)*56.32);
    glEnd();

    glBegin(GL_LINES);
        glVertex2f(50.0, leastSquaresGoalsNumberOfBackers.at(0) + leastSquaresGoalsNumberOfBackers.at(1)*50.00 + 400);
        glVertex2f(55.0, leastSquaresGoalsNumberOfBackers.at(0) + leastSquaresGoalsNumberOfBackers.at(1)*4757.295 + 350);
    glEnd();

    glBegin(GL_LINES);
        glVertex2f(400.0, leastAmountPledgedGoals.at(0) + leastAmountPledgedGoals.at(1)*50.00);
        glVertex2f(456.32, leastAmountPledgedGoals.at(0) + leastAmountPledgedGoals.at(1)*13239.766);
    glEnd();

    glColor3f(1.0, 1.0, 1.0);

    drawText(text[1].data(), text[1].size(), 145, 900);
    drawText(text[0].data(), text[0].size(), 475, 550);
    drawText(text[2].data(), text[2].size(), 830, 200);

    drawText(to_string(rAmountPledgedNumberOfBackers).data(), to_string(rAmountPledgedNumberOfBackers).size(), 830, 900);
    drawText(to_string(rGoalsNumberOfBackers).data(), to_string(rGoalsNumberOfBackers).size(), 550, 900);
    drawText(to_string(rAmountPledgedGoals).data(), to_string(rAmountPledgedGoals).size(), 830, 550);

    glFlush();
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

void initRendering()
{
    glClearColor(0.196, 0.196, 0.196, 0.0);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(WINDOW_LEFT, WINDOW_RIGHT, WINDOW_BOTTOM, WINDOW_TOP);
}

void drawBoxMatrix(int size, int spacing, int sideLength){
    int x = spacing;
    int y = spacing;
    
    for(int i = 0; i < size; i++){
        for(int j = 0; j < size; j++){
            drawBox(sideLength, x, y);
            y += spacing + sideLength;
        }
        x += spacing + sideLength;
        y = spacing;
    }
}

void drawBox(int sideLength, int startX, int startY){
    glBegin(GL_LINES);
        glVertex2i(startX, startY);
        glVertex2i(startX, startY + sideLength);
        glVertex2i(startX, startY + sideLength);
        glVertex2i(startX + sideLength, startY + sideLength);
        glVertex2i(startX + sideLength, startY + sideLength);
        glVertex2i(startX + sideLength, startY);
        glVertex2i(startX + sideLength, startY);
        glVertex2i(startX, startY);
    glEnd();
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

double calculateMean(vector<float> data){
    double mean = 0.0;
    float sum = 0.0;
    for(int i = 0; i < data.size(); i++)
        sum += data.at(i);
    if(data.size() != 0)
        mean = (double)sum/(double)data.size();
    return mean;
}

float calculateCorrelationCoefficient(vector<float> x, vector<float> y, double xMean, double yMean){
    float numerator = 0.0;
    float sumOfSquaresX = 0.0;
    float sumOfSquaresY = 0.0;
    float correlationCoefficient = 0.0;
    for(int i = 0; i < x.size(); i++){
        numerator += (x.at(i) - xMean)*(y.at(i) - yMean);
        sumOfSquaresX += pow((x.at(i) - xMean), 2);
        sumOfSquaresY += pow((y.at(i) - yMean), 2);
    }
    correlationCoefficient = numerator/(sqrt(sumOfSquaresX)*sqrt(sumOfSquaresY));
    return correlationCoefficient;
}

double calculateVarience(double mean, vector<float> data){
    double varience = 0.0;
    float sumSquared = 0;

    for(int i = 0; i < data.size(); i++)
        sumSquared += pow(data.at(i), 2);
        
    varience = ((double)sumSquared/(double)data.size()) - pow(mean, 2);
    return varience;
}

vector<float> calculateLeastSquaresCoeff(float rXY, double xMean, double yMean, double xSD, double ySD){
    vector<float> leastSquaresCoeff;
    float a, b;
    b = rXY*(ySD/xSD);
    a = yMean - b*xMean;
    leastSquaresCoeff.push_back(a);
    leastSquaresCoeff.push_back(b);
    return leastSquaresCoeff;
}