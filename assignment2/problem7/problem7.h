#ifndef __PROBLEM6_H_INCLUDED__
#define __PROBLEM6_H_INCLUDED__
#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include <string>
#include <math.h>
#include <iostream>

struct Node 
{
    std::string id;
    int dimension;
    int xPosition;
    int yPosition;
    std::vector<Node *> Neighbours;
};

struct Graph
{
    unsigned int nodesAmount;
    //unsigned int arcsAmount;
    std::vector<Node *> NodeArr;
};

void drawText(const char*, int, int, int);
void draw(void);
void initRendering();
Graph* createGraph();
Node* createNode(std::string, int, int);
void drawGraph(Graph*);
void drawNode(Node*);
void mouseFunction(int, int state, int x, int y);

#endif