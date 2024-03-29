#include "problem2.h"

using namespace std;

//g++ problem2.cpp -lm -lglut -lGL -lGLU -o problem2

//This file creates a 3x3 scatter plot matrix of kickstarter data
//calulcates the corrliation of the amount of money pledged, the goal amount,
//and the number of backers the kickstarter project had

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

    rGoalsNumberOfBackers = calculateCorrelationCoefficient(normalizedGoals, 
        normalizedNumberOfBackers, goalMean, numberOfBackersMean);

    rAmountPledgedNumberOfBackers = calculateCorrelationCoefficient(normalizedAmountPledged, 
        normalizedNumberOfBackers, amountPledgedMean, numberOfBackersMean);

    rAmountPledgedGoals = calculateCorrelationCoefficient(normalizedAmountPledged, 
        normalizedGoals, amountPledgedMean, goalMean);

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HIEGHT);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Problem 2");
    initRendering();
    glutDisplayFunc(drawPlots);
    glutMainLoop();

    return 0;
}

//Function that is responsible for drawing the plots to the screen
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

    drawText(text[1].data(), text[1].size(), 145, 900);
    drawText(text[0].data(), text[0].size(), 475, 550);
    drawText(text[2].data(), text[2].size(), 830, 200);

    drawText(to_string(rAmountPledgedNumberOfBackers).data(), to_string(rAmountPledgedNumberOfBackers).size(), 830, 900);
    drawText(to_string(rGoalsNumberOfBackers).data(), to_string(rGoalsNumberOfBackers).size(), 550, 900);
    drawText(to_string(rAmountPledgedGoals).data(), to_string(rAmountPledgedGoals).size(), 830, 550);

    glFlush();
}

//Same as the function for problem 1, draws text to the screen
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

//Draws the 3x3 matrix of sub-plots
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

//Draws each sub-plot
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

//Reads input data from a textfile
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

//Normalizes data to fit into the size of each sub-plot
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

//Calulates the mean of inputed data
double calculateMean(vector<float> data){
    double mean = 0.0;
    float sum = 0.0;
    for(int i = 0; i < data.size(); i++)
        sum += data.at(i);
    if(data.size() != 0)
        mean = (double)sum/(double)data.size();
    return mean;
}

//calulcates the correlation coeff between to inputed datasets
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