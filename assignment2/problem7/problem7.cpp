#include "problem7.h"

using namespace std;

//g++ problem7.cpp -lm -lglut -lGL -lGLU -o problem7

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

    string text[11];

    for(int i = 0; i < myGraph -> nodesAmount; i++){
        text[i] = myGraph -> NodeArr.at(i) -> id;
    }

    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 0.0, 0.0);
    
    drawText(text[0].data(), text[0].size(), 1401, 460);    //Home
    drawText(text[1].data(), text[1].size(), 1201, 460);    //Park
    drawText(text[2].data(), text[2].size(), 1261, 320);    //Sushi
    drawText(text[3].data(), text[3].size(), 1071, 610);    //GroceryStore
    drawText(text[4].data(), text[4].size(), 850, 610);     //Mexican
    drawText(text[5].data(), text[5].size(), 920, 460);     //Dentist
    drawText(text[6].data(), text[6].size(), 731, 320);     //Downtown
    drawText(text[7].data(), text[7].size(), 551, 130);     //Quay
    drawText(text[8].data(), text[8].size(), 950, 170);     //Skytrain
    drawText(text[9].data(), text[9].size(), 1321, 130);    //Basketball
    //drawText(text[10].data(), text[10].size(), 580, 797);

    glColor3f(1.0, 1.0, 1.0);
    drawGraph(myGraph);
    glFlush();
}

void initRendering(){
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glMatrixMode(GL_PROJECTION);
    glPointSize(10.0);
    gluOrtho2D(0.0, 1601.0, 0.0, 897.0);
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

Graph* createGraph(){

    Graph *graph = new Graph;
    graph -> nodesAmount = 10;
    
    Node *nodeHome = createNode("Home", 1401, 450);
    Node *nodePark = createNode("Park", 1201, 450);
    Node *nodeSushi = createNode("Sushi", 1301, 300);
    Node *nodeGroceryStore = createNode("Grocery Store", 1101, 600);
    Node *nodeMexican = createNode("Mexican Restaurant", 1001, 600);
    Node *nodeDentist = createNode("Dentist", 1001, 450);
    Node *nodeDownTown = createNode("Downtown", 801, 300);
    Node *nodeQuay = createNode("Quay", 601, 150);
    Node *nodeSkytrain = createNode("Skytrain", 1001, 200);
    Node *nodeBasketBall = createNode("BasketBall Court", 1401, 150);

    nodeHome -> Neighbours.push_back(nodePark);
    nodeHome -> Neighbours.push_back(nodeSushi);
    nodeHome -> Neighbours.push_back(nodeGroceryStore);

    nodePark -> Neighbours.push_back(nodeHome);
    nodePark -> Neighbours.push_back(nodeDentist);
    
    nodeSushi -> Neighbours.push_back(nodeHome);
    nodeSushi -> Neighbours.push_back(nodeSkytrain);
    nodeSushi -> Neighbours.push_back(nodeBasketBall);

    nodeGroceryStore -> Neighbours.push_back(nodeMexican);
    nodeGroceryStore -> Neighbours.push_back(nodeHome);

    nodeMexican -> Neighbours.push_back(nodeGroceryStore);
    nodeMexican -> Neighbours.push_back(nodeDentist);

    nodeDentist -> Neighbours.push_back(nodeMexican);
    nodeDentist -> Neighbours.push_back(nodeDownTown);
    nodeDentist -> Neighbours.push_back(nodePark);

    nodeDownTown -> Neighbours.push_back(nodeDentist);
    nodeDownTown -> Neighbours.push_back(nodeSkytrain);
    nodeDownTown -> Neighbours.push_back(nodeQuay);

    nodeQuay -> Neighbours.push_back(nodeDownTown);
    nodeQuay -> Neighbours.push_back(nodeSkytrain);

    nodeSkytrain -> Neighbours.push_back(nodeQuay);
    nodeSkytrain -> Neighbours.push_back(nodeDownTown);
    nodeSkytrain -> Neighbours.push_back(nodeBasketBall);
    nodeSkytrain -> Neighbours.push_back(nodeSushi);

    nodeBasketBall -> Neighbours.push_back(nodeSkytrain);
    nodeBasketBall -> Neighbours.push_back(nodeSushi);

    graph -> NodeArr.push_back(nodeHome);
    graph -> NodeArr.push_back(nodePark);
    graph -> NodeArr.push_back(nodeSushi);
    graph -> NodeArr.push_back(nodeGroceryStore);
    graph -> NodeArr.push_back(nodeMexican);
    graph -> NodeArr.push_back(nodeDentist);
    graph -> NodeArr.push_back(nodeDownTown);
    graph -> NodeArr.push_back(nodeQuay);
    graph -> NodeArr.push_back(nodeSkytrain);
    graph -> NodeArr.push_back(nodeBasketBall);

    return graph;
}

Node* createNode(string id, int x, int y){
    Node* newNode = new Node;
    newNode -> xPosition = x;
    newNode -> yPosition = y;
    newNode -> id = id;
    return newNode;
}

void mouseFunction(int button, int state, int x, int y){
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