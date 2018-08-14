#include "problem3.h"

using namespace std;

//g++ problem1.cpp -lm -lglut -lGL -lGLU -o problem1

int main(int argc, char** argv){

    vector<float> lengthOfTrumpTweets;
    pair<float, float> userInput;
    int userClassification = -1;

    //Read input data from textfile and store them into a vector of ints
    lengthOfTrumpTweets = readData(trumpTweetData);
    lengthOfTrumpTweets = normalizeData(25, 1230, lengthOfTrumpTweets);

    for(int i = 0; i < lengthOfTrumpTweets.size(); i++)
        dataPairs.push_back(make_pair((float)(i + 23), lengthOfTrumpTweets[i]));

    //Initially set the cluster centres to be the first 3 samples in lengthOfTrumpTweets
    //and add them to their corresponding domains
    clusterCentre1 = dataPairs[0];
    clusterCentre2 = dataPairs[1];
    clusterCentre3 = dataPairs[2];
    clusterDomain1.push_back(clusterCentre1);
    clusterDomain2.push_back(clusterCentre2);
    clusterDomain3.push_back(clusterCentre3);

    cout << "Enter x data position as a float: ";
    cin >> userInput.first;
    cout << "Enter y data position as a float: ";
    cin >> userInput.second;
    userClassification = classifyUserData(userInput);
    cout << "Your data point belongs to class: " << userClassification << endl;

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HIEGHT);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Problem 3");
    initRendering();
    glutDisplayFunc(drawInitalDataSet);
    glutMainLoop();

    return 1;
}

void initRendering(){
    glClearColor(0.623, 0.639, 0.659, 0.0);
    glEnable(GL_PROGRAM_POINT_SIZE);
    glPointSize(7.0);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(WINDOW_LEFT, WINDOW_RIGHT, WINDOW_BOTTOM, WINDOW_TOP);
    glutKeyboardFunc(keyBoardInput);
}

//Gets data from textfile given a path
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


//This function draws text on the screen
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


//This function checks if the spacebar has been pressed or not if it has it 
//computes the new cluster centres and clears the cluster domains and calls
//assignToCluster then draws the new cluster domains
void keyBoardInput(unsigned char Key, int x, int y){
    if(Key == 32){
        for(int i = 0; i < NUMBER_OF_ITERATIONS; i++){
            drawClusterMeans();
            clusterCentre1 = computeClusterCentre(clusterDomain1);
            clusterCentre2 = computeClusterCentre(clusterDomain2);
            clusterCentre3 = computeClusterCentre(clusterDomain3);
            clusterDomain1.clear();
            clusterDomain2.clear();
            clusterDomain3.clear();
            for(auto i : dataPairs)
                assignToCluster(i);
            drawClustering();
        }
    } else if(Key == 13){
        perceptron();
        drawDecisionLines();
    }
}

//Inital drawing setup function
void drawInitalDataSet(){

    string text[4] = {"K-Means Clustering of the number of characters in Trump's Tweets", "Press spacebar to cluster and then ENTER to exicute the perceptron algorithm"};

    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.0, 0.0, 0.0);

    drawText(text[0].data(), text[0].size(), 420, 1250);
    drawText(text[1].data(), text[1].size(), 200, -10);

    glBegin(GL_LINES);
        glVertex2i(20, 0);
        glVertex2i(20, 1230);
    glEnd();

    glBegin(GL_LINES);
        glVertex2i(0, 20);
        glVertex2i(1310, 20);
    glEnd();
    glBegin(GL_POINTS);
        for(auto i : dataPairs)
            glVertex2f(i.first, i.second);
    glEnd();

    glFlush();
}

//Draws each clustering
void drawClustering(){
    glBegin(GL_POINTS);
        glColor3f(1.0, 0.0, 0.0);
        for(auto i : clusterDomain1)
            glVertex2f(i.first, i.second);
    glEnd();

    glBegin(GL_POINTS);
        glColor3f(0.0, 1.0, 0.0);
        for(auto i : clusterDomain2)
            glVertex2f(i.first, i.second);
    glEnd();

    glBegin(GL_POINTS);
        glColor3f(0.0, 0.0, 1.0);
        for(auto i : clusterDomain3)
            glVertex2f(i.first, i.second);
    glEnd();

    glBegin(GL_POINTS);
        glColor3f(1.0, 1.0, 1.0);
        glVertex2f(clusterCentre1.first, clusterCentre1.second);
        glVertex2f(clusterCentre2.first, clusterCentre2.second);
        glVertex2f(clusterCentre3.first, clusterCentre3.second);
    glEnd();

    glFlush();
}

void drawClusterMeans(){
    glColor3f(0.623, 0.639, 0.659);
    glBegin(GL_POINTS);
        glVertex2f(clusterCentre1.first, clusterCentre1.second);
        glVertex2f(clusterCentre2.first, clusterCentre2.second);
        glVertex2f(clusterCentre3.first, clusterCentre3.second);
    glEnd();
    glFlush();
}
//Function that draws the decsion lines
void drawDecisionLines(){
    glColor3f(0, 0, 0);
    glBegin(GL_LINES);
        glVertex2f(20, (perceptronCoef[1][0]/(-perceptronCoef[1][1]))*20 + perceptronCoef[1][2] + 3000);
        glVertex2f(1310, (perceptronCoef[1][0]/(-perceptronCoef[1][1]))*1310 + perceptronCoef[1][2]);
    glEnd();

    glBegin(GL_LINES);
        glVertex2f(20, (perceptronCoef[2][0]/(-perceptronCoef[2][1]))*20 + perceptronCoef[2][2]);
        glVertex2f(1310, (perceptronCoef[2][0]/(-perceptronCoef[2][1]))*1310 + perceptronCoef[2][2]);
    glEnd();
    glFlush();
}


//This function is to normalize input data between an given upper and lower bound
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

//Assigns which cluster a new data point belongs to by calulcating the Euclidean distance
//between the new data point and all 3 cluster centres. After the data point has been assigned
//which cluster it belongs to this function adds it to the corresponding cluster domain vector
void assignToCluster(pair<float, float> sample){
    float distanceCluster1, distanceCluster2, distanceCluster3;
    distanceCluster1 = euclideanDistance(clusterCentre1, sample);
    distanceCluster2 = euclideanDistance(clusterCentre2, sample);
    distanceCluster3 = euclideanDistance(clusterCentre3, sample);

    if(distanceCluster1 < distanceCluster2 && distanceCluster1 < distanceCluster3){
        clusterDomain1.push_back(sample);
    } else if(distanceCluster2 < distanceCluster1 && distanceCluster2 < distanceCluster3){
        clusterDomain2.push_back(sample);
    } else if(distanceCluster3 < distanceCluster1 && distanceCluster3 < distanceCluster2){
        clusterDomain3.push_back(sample);
    }
}

//Function calculates the Euclidean distance between two points a and b
float euclideanDistance(pair<float, float> a, pair<float, float> b){
    float distance = 0;
    float xDistSquared = 0;
    float yDistSquared = 0;
    xDistSquared = pow(a.first - b.first, 2);
    yDistSquared = pow(a.second - b.second, 2);
    distance = sqrt(xDistSquared + yDistSquared);
    return distance;
}


//Function that re-calculates cluster centres by calculating the mean of the 
//input cluster domain in both x and y directions
pair<float, float> computeClusterCentre(vector<pair<float, float> > domain){
    pair<float, float> clusterCentre;
    int sizeOfDomain = domain.size();
    float sumX = 0;
    float sumY = 0;
    for(auto i : domain){
        sumX += i.first;
        sumY += i.second;
    }
    clusterCentre.first = sumX / sizeOfDomain;
    clusterCentre.second = sumY / sizeOfDomain;

    return clusterCentre;
}

//This function determines the decsion line coeffiecents by exicuting the perceptron algorithm 
//by using one vs all technique on a set of input data.
void perceptron(){
    vector<float> weights = {0, 0, 0};
    float perceptronVal = 0;
    for(auto i : trainingData){
        perceptronVal = (i[0] * weights[0]) + (i[1] * weights[1]) + weights[2]*CONSTANT;
        if(i[2] == 1 && perceptronVal > 0){
            weights[0] -= CONSTANT*i[0];
            weights[1] -= CONSTANT*i[1];
            weights[2] -= CONSTANT;
        } else if(i[2] == 1 && perceptronVal < 0){
            weights[0] += CONSTANT*i[0];
            weights[1] += CONSTANT*i[1];
            weights[2] += CONSTANT;
        } else if( (i[2] == 2 || i[3] == 3) && perceptronVal == 0){
            weights[0] += CONSTANT*i[0];
            weights[1] += CONSTANT*i[1];
            weights[2] += CONSTANT;
        }
    }

    perceptronCoef.push_back(weights);
    weights[0] = 0;
    weights[1] = 0;
    weights[2] = 0;

    for(auto i : trainingData){
        perceptronVal = (i[0] * weights[0]) + (i[1] * weights[1]) + weights[2]*CONSTANT;
        if(i[2] == 2 && perceptronVal > 0){
            weights[0] -= CONSTANT*i[0];
            weights[1] -= CONSTANT*i[1];
            weights[2] -= CONSTANT;
        } else if(i[2] == 2 && perceptronVal < 0){
            weights[0] += CONSTANT*i[0];
            weights[1] += CONSTANT*i[1];
            weights[2] += CONSTANT;
        } else if( (i[2] == 1 || i[3] == 3) && perceptronVal == 0){
            weights[0] += CONSTANT*i[0];
            weights[1] += CONSTANT*i[1];
            weights[2] += CONSTANT;
        }
    }

    perceptronCoef.push_back(weights);
    weights[0] = 0;
    weights[1] = 0;
    weights[2] = 0;

    for(auto i : trainingData){
        perceptronVal = (i[0] * weights[0]) + (i[1] * weights[1]) + weights[2]*CONSTANT;
        if(i[2] == 3 && perceptronVal > 0){
            weights[0] -= CONSTANT*i[0];
            weights[1] -= CONSTANT*i[1];
            weights[2] -= CONSTANT;
        } else if(i[2] == 3 && perceptronVal < 0){
            weights[0] += CONSTANT*i[0];
            weights[1] += CONSTANT*i[1];
            weights[2] += CONSTANT;
        } else if( (i[2] == 1 || i[3] == 2) && perceptronVal == 0){
            weights[0] += CONSTANT*i[0];
            weights[1] += CONSTANT*i[1];
            weights[2] += CONSTANT;
        }
    }
    perceptronCoef.push_back(weights);
}
/*const int WINDOW_LEFT = -60;
const int WINDOW_BOTTOM = -60;
const int WINDOW_RIGHT = 1500;
const int WINDOW_TOP = 1300;*/


int classifyUserData(pair<float, float> a){
    int userClassification = -1;
    cout << a.first << endl;
    cout << a.second << endl;
    vector<float> data;
    data.push_back(a.first);
    data.push_back(a.second);

    if(data[0] < 500 && data[1] > 50){
        userClassification = 3;
    }
    else if(data[0] >= 500 && data[1] > 400){
        userClassification = 2;
    } else {
        userClassification = 1;
    }

    return userClassification;
}