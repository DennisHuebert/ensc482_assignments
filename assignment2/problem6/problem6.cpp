#include "problem6.h"

using namespace std;

//g++ problem6.cpp -lm -lglut -lGL -lGLU -o problem6

Graph *myGraph = createGraph();

int main(int argc, char** argv){

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(1601, 897);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Problem 6");
    initRendering();
    glutDisplayFunc(draw);
    glutMouseFunc(mouseFunction);
    glutMainLoop();

    for(int i = 0; i < myGraph -> nodesAmount; i++)
        delete myGraph -> NodeArr.at(i);
    delete myGraph;

    return 0;
}

void draw() {

    string text[11]; //Click any node to highlight neighbouring paths

    for(int i = 0; i < myGraph -> nodesAmount; i++){
        text[i] = myGraph -> NodeArr.at(i) -> id;
    }

    text[10] = "Click any node to highlight neighbouring paths";


    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 0.0, 0.0);
    
    drawText(text[0].data(), text[0].size(), 1401, 460);    //Nesters
    drawText(text[1].data(), text[1].size(), 1201, 460);    //Cornerstone
    drawText(text[2].data(), text[2].size(), 1001, 280);    //ASB
    drawText(text[3].data(), text[3].size(), 1001, 610);    //Blusson
    drawText(text[4].data(), text[4].size(), 801, 610);     //Saywell
    drawText(text[5].data(), text[5].size(), 592, 460);     //AQ
    drawText(text[6].data(), text[6].size(), 401, 460);     //Library
    drawText(text[7].data(), text[7].size(), 401, 280);     //MBC
    drawText(text[8].data(), text[8].size(), 201, 280);     //GYM
    drawText(text[9].data(), text[9].size(), 201, 460);     //Westmall

    drawText(text[10].data(), text[10].size(), 580, 797);

    glColor3f(1.0, 1.0, 1.0);
    drawGraph(myGraph);
    glFlush();
}

void drawText(const char *text, int length, int x, int y){
    glMatrixMode(GL_PROJECTION);
    double *matrix = new double[16];
    glGetDoublev(GL_PROJECTION_MATRIX, matrix);
    glLoadIdentity();
    glOrtho(0.0, 1601.0, 0.0, 897.0, -5, 5);
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

void initRendering(){
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glMatrixMode(GL_PROJECTION);
    glPointSize(10.0);
    gluOrtho2D(0.0, 1601.0, 0.0, 897.0);
}

Graph* createGraph(){

    Graph *graph = new Graph;
    graph -> nodesAmount = 10;
    
    Node *nodeNesters = createNode("Nesters", 1401, 450);
    Node *nodeCornerStone = createNode("CornerStone", 1201, 450);
    Node *nodeASB = createNode("ASB", 1001, 300);
    Node *nodeBlusson = createNode("Blusson", 1001, 600);
    Node *nodeSaywell = createNode("Saywell", 801, 600);
    Node *nodeAQ = createNode("AQ", 601, 450);
    Node *nodeLibrary = createNode("Library", 401, 450);
    Node *nodeMBC = createNode("MBC", 401, 300);
    Node *nodeWestmall = createNode("Westmall", 201, 450);
    Node *nodeGym = createNode("Gym", 201, 300);

    nodeNesters -> Neighbours.push_back(nodeCornerStone);

    nodeCornerStone -> Neighbours.push_back(nodeNesters);
    nodeCornerStone -> Neighbours.push_back(nodeBlusson);
    nodeCornerStone -> Neighbours.push_back(nodeASB);

    nodeASB -> Neighbours.push_back(nodeCornerStone);
    nodeASB -> Neighbours.push_back(nodeAQ);

    nodeBlusson -> Neighbours.push_back(nodeCornerStone);
    nodeBlusson -> Neighbours.push_back(nodeSaywell);

    nodeSaywell -> Neighbours.push_back(nodeBlusson);
    nodeSaywell -> Neighbours.push_back(nodeAQ);

    nodeAQ -> Neighbours.push_back(nodeSaywell);
    nodeAQ -> Neighbours.push_back(nodeASB);
    nodeAQ -> Neighbours.push_back(nodeLibrary);

    nodeLibrary -> Neighbours.push_back(nodeAQ);
    nodeLibrary -> Neighbours.push_back(nodeMBC);
    nodeLibrary -> Neighbours.push_back(nodeWestmall);

    nodeWestmall -> Neighbours.push_back(nodeLibrary);
    nodeWestmall -> Neighbours.push_back(nodeGym);

    nodeGym -> Neighbours.push_back(nodeWestmall);
    nodeGym -> Neighbours.push_back(nodeMBC);

    nodeMBC -> Neighbours.push_back(nodeGym);
    nodeMBC -> Neighbours.push_back(nodeLibrary);

    graph -> NodeArr.push_back(nodeNesters);
    graph -> NodeArr.push_back(nodeCornerStone);
    graph -> NodeArr.push_back(nodeASB);
    graph -> NodeArr.push_back(nodeBlusson);
    graph -> NodeArr.push_back(nodeSaywell);
    graph -> NodeArr.push_back(nodeAQ);
    graph -> NodeArr.push_back(nodeLibrary);
    graph -> NodeArr.push_back(nodeMBC);
    graph -> NodeArr.push_back(nodeWestmall);
    graph -> NodeArr.push_back(nodeGym);

    return graph;
}

Node* createNode(string id, int x, int y){
    Node* newNode = new Node;
    newNode -> xPosition = x;
    newNode -> yPosition = y;
    newNode -> id = id;
    return newNode;
}

void drawGraph(Graph *g){
    for(int i = 0; i < g -> nodesAmount; i++)
        drawNode(g -> NodeArr.at(i));
    glBegin(GL_LINES);
        for(Node *x : g -> NodeArr){
            for(Node *j : x -> Neighbours){
                glVertex2i(x -> xPosition, x -> yPosition);
                glVertex2i(j -> xPosition, j -> yPosition);
            }
        }
    glEnd();
}

void drawNode(Node *n){
    glBegin(GL_POINTS);
        glVertex2f(n -> xPosition, n -> yPosition);
    glEnd();
}

void mouseFunction(int button, int state, int x, int y){
    y = abs(y - 897);
    if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN){
        for(Node *node : myGraph -> NodeArr){
            if( ((x >= node -> xPosition - 10) && (x <= node -> xPosition + 10)) && 
                ((y >= node -> yPosition - 10) && (y <= node -> yPosition + 10)) ){
                changeColour(node);
            }
        }
    }
}

void changeColour(Node *n){
    if(n -> numberOfClicks % 2 == 0)
        glColor3f(0.0, 1.0, 0.0);
    else
        glColor3f(1.0, 1.0, 1.0);
    n -> numberOfClicks++;
    glBegin(GL_LINES);
        for(Node *x : n -> Neighbours){
            glVertex2i(n -> xPosition, n -> yPosition);
            glVertex2i(x -> xPosition, x -> yPosition);
        }
    glEnd();
    glFlush();
}