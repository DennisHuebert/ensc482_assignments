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

    nodeHome -> Neighbours.insert(pair<Node*, int>(nodePark, 2));
    nodeHome -> Neighbours.insert(pair<Node*, int>(nodeSushi, 2));
    nodeHome -> Neighbours.insert(pair<Node*, int>(nodeGroceryStore, 4));

    nodePark -> Neighbours.insert(pair<Node*, int>(nodeHome, 2));
    nodePark -> Neighbours.insert(pair<Node*, int>(nodeDentist, 4));

    nodeSushi -> Neighbours.insert(pair<Node*, int>(nodeHome, 2));
    nodeSushi -> Neighbours.insert(pair<Node*, int>(nodeSkytrain, 4));
    nodeSushi -> Neighbours.insert(pair<Node*, int>(nodeBasketBall, 3));

    nodeGroceryStore -> Neighbours.insert(pair<Node*, int>(nodeMexican, 3));
    nodeGroceryStore -> Neighbours.insert(pair<Node*, int>(nodeHome, 4));

    nodeMexican -> Neighbours.insert(pair<Node*, int>(nodeGroceryStore, 3));
    nodeMexican -> Neighbours.insert(pair<Node*, int>(nodeDentist, 2));

    nodeDentist -> Neighbours.insert(pair<Node*, int>(nodeMexican, 2));
    nodeDentist -> Neighbours.insert(pair<Node*, int>(nodeDownTown, 3));
    nodeDentist -> Neighbours.insert(pair<Node*, int>(nodePark, 4));

    nodeDownTown -> Neighbours.insert(pair<Node*, int>(nodeDentist, 3));
    nodeDownTown -> Neighbours.insert(pair<Node*, int>(nodeSkytrain, 2));
    nodeDownTown -> Neighbours.insert(pair<Node*, int>(nodeQuay, 2));

    nodeQuay -> Neighbours.insert(pair<Node*, int>(nodeDownTown, 2));
    nodeQuay -> Neighbours.insert(pair<Node*, int>(nodeSkytrain, 3));

    nodeSkytrain -> Neighbours.insert(pair<Node*, int>(nodeQuay, 3));
    nodeSkytrain -> Neighbours.insert(pair<Node*, int>(nodeDownTown, 2));
    nodeSkytrain -> Neighbours.insert(pair<Node*, int>(nodeBasketBall, 2));
    nodeSkytrain -> Neighbours.insert(pair<Node*, int>(nodeSushi, 4));

    nodeBasketBall -> Neighbours.insert(pair<Node*, int>(nodeSkytrain, 2));
    nodeBasketBall -> Neighbours.insert(pair<Node*, int>(nodeSushi, 3));

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
    if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN){
        y = abs(y - 897);
        if(!wasMouseClicked){
            for(Node *node : myGraph -> NodeArr){
                if( ((x >= node -> xPosition - 10) && (x <= node -> xPosition + 10)) && 
                    ((y >= node -> yPosition - 10) && (y <= node -> yPosition + 10)) ){
                        clickedNodesArray[0] = node;
                        wasMouseClicked = true;
                }
            }
        }else{
            for(Node *node : myGraph -> NodeArr){
                if( ((x >= node -> xPosition - 10) && (x <= node -> xPosition + 10)) && 
                    ((y >= node -> yPosition - 10) && (y <= node -> yPosition + 10)) ){
                        clickedNodesArray[1] = node;
                        wasMouseClicked = false;
                        calcualteShortestPath(clickedNodesArray[0], clickedNodesArray[1]);
                }
            }
        }
    }
}

void drawGraph(Graph *g){
    for(int i = 0; i < g -> nodesAmount; i++)
        drawNode(g -> NodeArr.at(i));
    glBegin(GL_LINES);
        for(Node *x : g -> NodeArr){
            for(auto j : x -> Neighbours){
                glVertex2i(x -> xPosition, x -> yPosition);
                glVertex2i(j.first -> xPosition, j.first -> yPosition);
            }
        }
    glEnd();
}

void drawNode(Node *n){
    glBegin(GL_POINTS);
        glVertex2f(n -> xPosition, n -> yPosition);
    glEnd();
}

void calcualteShortestPath(Node *start, Node *destination){
    vector<Node*> shortestPath;
    shortestPath.push_back(start);
    int temp = 1000;
    if(start != destination){
        while(start != destination){
            for(auto i : start -> Neighbours){
                if(i.first == destination){
                    start = i.first;
                    break;
                } else if((abs(i.first -> xPosition - start -> xPosition) < abs(start -> xPosition - destination -> xPosition)) ||
                          (abs(i.first -> yPosition - start -> yPosition) < abs(start -> yPosition - destination -> yPosition))) {
                    start = i.first;
                } else if(i.second < temp){
                    start = i.first;
                }
            }
            shortestPath.push_back(start);
        }
        highLightShortestPath(shortestPath);
    }

}

void highLightShortestPath(vector<Node*> shortestPath){
    glColor3f(0.0, 1.0, 0.0);
    glBegin(GL_LINES);
    for(int i = 0; i < shortestPath.size() - 1; i++){
        glVertex2i(shortestPath.at(i) -> xPosition, shortestPath.at(i) -> yPosition);
        glVertex2i(shortestPath.at(i + 1) -> xPosition, shortestPath.at(i + 1) -> yPosition);
    }
    glEnd();
    glFlush();
}