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

const unsigned int THRESHOLD = 50;

const char *amountPledgedData = "data/KickStarterData/amountPledged.txt";
const char *numberOfBackersData = "data/KickStarterData/numberOfBackers.txt";

std::vector<float> normalizedNumberOfBackers;
std::vector<float> normalizedAmountPledged;

std::vector<float> readData(const char*);
void initRendering();
void drawText(const char*, int, int, int);
void drawClustering();
std::vector<float> normalizeData(int, int, std::vector<float>);
float euclideanDistance(std::vector<float>);

#endif