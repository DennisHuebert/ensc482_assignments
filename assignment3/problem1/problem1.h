#ifndef __PROBLEM1_H_INCLUDED__
#define __PROBLEM1_H_INCLUDED__

#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <map>
#include <vector>
#include <cmath>
#include <GL/glut.h>

const int WINDOW_LEFT = 0;
const int WINDOW_BOTTOM = 0;
const int WINDOW_RIGHT = 1500;
const int WINDOW_TOP = 1300;
const int WINDOW_WIDTH = WINDOW_RIGHT - WINDOW_LEFT;
const int WINDOW_HIEGHT = WINDOW_TOP - WINDOW_BOTTOM;

const char *trumpTweetData = "data/LengthOfTrumpTweets.txt";

// dataPairs;
std::vector<std::pair<float, float> > clusterDomain1;
std::vector<std::pair<float, float> > clusterDomain2;
std::vector<std::pair<float, float> > clusterDomain3;

std::pair<float, float> clusterCentre1, clusterCentre2, clusterCentre3;

std::vector<float> readData(const char*);
void initRendering();
void drawText(const char*, int, int, int);
void drawClustering();
void keyBoardInput(unsigned char, int, int);
std::vector<float> normalizeData(int, int, std::vector<float>);
float euclideanDistance(std::pair<float, float>, std::pair<float, float>);
void assignToCluster(std::pair<float, float>);
std::pair<float, float> computeClusterCentre(std::vector<std::pair<float, float> >);
void computeClustering(std::vector<std::pair<float, float> >);

#endif