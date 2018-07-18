#ifndef __PROBLEM2_H_INCLUDED__
#define __PROBLEM2_H_INCLUDED__

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
const int WINDOW_RIGHT = 1100;
const int WINDOW_TOP = 1100;
const int WINDOW_WIDTH = WINDOW_RIGHT - WINDOW_LEFT;
const int WINDOW_HIEGHT = WINDOW_TOP - WINDOW_BOTTOM;

const char *amountPledgedData = "data/KickStarterData/amountPledged.txt";
const char *goalData = "data/KickStarterData/goal.txt";
const char *numberOfBackersData = "data/KickStarterData/numberOfBackers.txt";

std::vector<float> normalizedAmountPledged;
std::vector<float> normalizedGoals;
std::vector<float> normalizedNumberOfBackers;

float rGoalsNumberOfBackers = 0.0;
float rAmountPledgedNumberOfBackers = 0.0;
float rAmountPledgedGoals = 0.0;

void initRendering();
void drawText(const char*, int, int, int);
void drawPlots();
void drawBoxMatrix(int, int, int);
void drawBox(int, int, int);
std::vector<float> readData(const char*);
std::vector<float> normalizeData(int, int, std::vector<float>);
double calculateMean(std::vector<float>);
float calculateCorrelationCoefficient(std::vector<float>, std::vector<float>, double, double);

#endif