#include "problem1.h"

using namespace std;

//g++ problem1.cpp -lm -lglut -lGL -lGLU -o problem1

int main(int argc, char** argv){

    vector<float> lengthOfTrumpTweets;

    //Read input data from textfile and store them into a vector of ints
    lengthOfTrumpTweets = readData(trumpTweetData);
    lengthOfTrumpTweets = normalizeData(25, 1230, lengthOfTrumpTweets);

    for(int i = 0; i < lengthOfTrumpTweets.size(); i++)
        dataPairs.push_back(make_pair((float)(i + 20), lengthOfTrumpTweets[i]));

    //Initially set the cluster centres to be the first 3 samples in lengthOfTrumpTweets
    //and add them to their corresponding domains
    clusterCentre1 = dataPairs[0];
    clusterCentre2 = dataPairs[1];
    clusterCentre3 = dataPairs[2];
    clusterDomain1.push_back(clusterCentre1);
    clusterDomain2.push_back(clusterCentre2);
    clusterDomain3.push_back(clusterCentre3);

    //computeClustering(dataPairs);

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HIEGHT);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Problem 1");
    initRendering();
    glutDisplayFunc(drawInitalDataSet);
    glutMainLoop();

    return 1;
}

void initRendering()
{
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

void keyBoardInput(unsigned char Key, int x, int y){
    if(Key == 32){
        drawClusterMeans();
        assignToCluster(dataPairs[counter]);
        drawClustering();
        counter++;
    }    
}

void drawInitalDataSet(){
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.0, 0.0, 0.0);

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

void drawClustering(){
    glBegin(GL_POINTS);
        glColor3f(1.0, 0.0, 0.0);
        for(auto i : clusterDomain1)
            glVertex2f(i.first, i.second);

        glColor3f(0.0, 1.0, 0.0);
        for(auto i : clusterDomain2)
            glVertex2f(i.first, i.second);

        glColor3f(0.0, 0.0, 1.0);
        for(auto i : clusterDomain3)
            glVertex2f(i.first, i.second);
        
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
//which cluster it belongs to this function adds it to the corresponding cluster vector and
//calls to re-calculate the new cluster centre and adds the new sample to the correct domain
void assignToCluster(pair<float, float> sample){
    float distanceCluster1, distanceCluster2, distanceCluster3;
    distanceCluster1 = euclideanDistance(clusterCentre1, sample);
    distanceCluster2 = euclideanDistance(clusterCentre2, sample);
    distanceCluster3 = euclideanDistance(clusterCentre3, sample);

    if(distanceCluster1 <= distanceCluster2 && distanceCluster1 <= distanceCluster3){
        clusterDomain1.push_back(sample);
        clusterCentre1 = computeClusterCentre(clusterDomain1);
    } else if(distanceCluster2 < distanceCluster1 && distanceCluster2 <= distanceCluster3){
        clusterDomain2.push_back(sample);
        clusterCentre2 = computeClusterCentre(clusterDomain2);
    } else if(distanceCluster3 < distanceCluster1 && distanceCluster3 < distanceCluster2){
        clusterDomain3.push_back(sample);
        clusterCentre3 = computeClusterCentre(clusterDomain3);
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