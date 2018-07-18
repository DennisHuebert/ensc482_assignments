#ifndef __PROBLEM6_H_INCLUDED__
#define __PROBLEM6_H_INCLUDED__
#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include <string>
#include <math.h>
#include <map>
#include <iostream>

struct Node 
{
    std::string id;
    int xPosition;
    int yPosition;
    std::map<Node *, int> Neighbours;
};

struct Graph
{
    unsigned int nodesAmount;
    std::vector<Node *> NodeArr;
};

bool wasMouseClicked = false;

Node *clickedNodesArray[2];

void drawText(const char*, int, int, int);
void draw(void);
void initRendering();
Graph* createGraph();
Node* createNode(std::string, int, int);
void drawGraph(Graph*);
void drawNode(Node*);
void mouseFunction(int, int state, int x, int y);
void calcualteShortestPath(Node*, Node*);
void highLightShortestPath(std::vector<Node*>);

#endif