#ifndef __PROBLEM3_H_INCLUDED__
#define __PROBLEM3_H_INCLUDED__

#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <map>
#include <vector>
#include <cmath>
#include <GL/glut.h>

const int WINDOW_LEFT = -60;
const int WINDOW_BOTTOM = -60;
const int WINDOW_RIGHT = 1500;
const int WINDOW_TOP = 1300;
const int WINDOW_WIDTH = WINDOW_RIGHT - WINDOW_LEFT;
const int WINDOW_HIEGHT = WINDOW_TOP - WINDOW_BOTTOM;
const int NUMBER_OF_ITERATIONS = 20;
const int CONSTANT = 1;

const char *trumpTweetData = "data/LengthOfTrumpTweets.txt";

// dataPairs;
std::vector<std::pair<float, float> > dataPairs;
std::vector<std::pair<float, float> > clusterDomain1;
std::vector<std::pair<float, float> > clusterDomain2;
std::vector<std::pair<float, float> > clusterDomain3;

std::pair<float, float> clusterCentre1, clusterCentre2, clusterCentre3;

std::vector<std::vector<float> > trainingData = {   {950.0, 400.0, 1}, {800.0, 800.0, 2}, {250.0, 500.0, 3},
                                                    {880.0, 430.0, 1}, {850.0, 900.0, 2}, {320.0, 550.0, 3} };

std::vector<std::vector<float> > perceptronCoef;

std::vector<float> readData(const char*);
void initRendering();
void drawText(const char*, int, int, int);
void drawInitalDataSet();
void drawClustering();
void drawClusterMeans();
void keyBoardInput(unsigned char, int, int);
std::vector<float> normalizeData(int, int, std::vector<float>);
float euclideanDistance(std::pair<float, float>, std::pair<float, float>);
void assignToCluster(std::pair<float, float>);
std::pair<float, float> computeClusterCentre(std::vector<std::pair<float, float> >);
void perceptron();
void drawDecisionLines();
int classifyUserData(std::pair<float, float>);

#endif