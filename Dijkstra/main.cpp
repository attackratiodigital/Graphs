  //
//  main.cpp
//  Dijkstra
//
//  Created by Anthony Cormican on 1/7/17.
//  Copyright (c) 2017 Anthony Cormican. All rights reserved.
//

#include <iostream>
#include <string>

#include "Node.h"
#include "List.h"
#include "Graph.h"

int main(int argc, const char * argv[])
{
    auto g = new Graph<Node>;
    /*
    g->printVertices();
    g->addEdge(0, 1);
    g->addEdge(0, 2);
    g->addEdge(0, 3);
    g->addEdge(1, 2);
    
    g->addEdge(0, 1);
    g->addEdge(0, 2);
    g->addEdge(0, 3);
    g->addEdge(1, 2);
    
    g->addEdge(2, 0);
    g->addEdge(3, 0);
    g->addEdge(9, 0);
    g->addEdge(7, 0);
    g->addEdge(0, 7);
    g->addEdge(0, 8);
    g->addEdge(8, 0);
    
    g->addEdge(1, 4, 5.4);
    g->addEdge(2, 6, 9.6);
    g->addEdge(3, 6, 0.2);
    g->addEdge(3, 2, 0.3);
    cout << "edges = " << g->numEdges() << endl;
    cout << "adjacent 0, 5 = " << g->adjacent(0, 5) << endl;
    cout << "adjacent 0, 2 = " << g->adjacent(0, 2)<< endl;
    cout << "adjacent 2, 0 = " << g->adjacent(2, 0)<< endl;
    g->setEdgeValue(0, 1, 3.2);
    g->setEdgeValue(0, 2, 4.2);
    g->setEdgeValue(0, 3, 5.2);
    g->setEdgeValue(1, 2, 6.2);
    
    cout << "edge value 0, 1 = " << g->getEdgeValue(0, 1) << endl;
    cout << "edge value 0, 2 = " << g->getEdgeValue(0, 2) << endl;
    cout << "edge value 0, 3 = " << g->getEdgeValue(0, 3) << endl;
    cout << "edge value 1, 2 = " << g->getEdgeValue(1, 2) << endl;
    cout << "edge value 1, 4 = " << g->getEdgeValue(1, 4) << endl;
    cout << "edge value 2, 6 = " << g->getEdgeValue(2, 6) << endl;
    cout << "edge value 3, 6 = " << g->getEdgeValue(3, 6) << endl;
    cout << "edge value 3, 2 = " << g->getEdgeValue(3, 2) << endl;
    
    cout << "Node value of Node 0 = " << g->getNodeName(0) << endl;
    cout << "Node value of Node 1 = " << g->getNodeName(1) << endl;
    cout << "Node value of Node 2 = " << g->getNodeName(2) << endl;
    cout << "Node value of Node 3 = " << g->getNodeName(3) << endl;
    cout << "Node value of Node 4 = " << g->getNodeName(4) << endl;
  
    cout << "Setting Node value of Node 4 to Hello..." << endl; g->setNodeName("Hello", 4);
    cout << "Setting Node value of Node 3 to to..." << endl; g->setNodeName("to", 3);
    cout << "Setting Node value of Node 2 to all..." << endl; g->setNodeName("all", 2);
    cout << "Setting Node value of Node 1 to the..." << endl; g->setNodeName("the", 1);

    cout << "Node value of Node 0 = " << g->getNodeName(0) << endl;
    cout << "Node value of Node 1 = " << g->getNodeName(1) << endl;
    cout << "Node value of Node 2 = " << g->getNodeName(2) << endl;
    cout << "Node value of Node 3 = " << g->getNodeName(3) << endl;
    cout << "Node value of Node 4 = " << g->getNodeName(4) << endl;
    
    cout << "deleting edge (0,1)... " << endl; g->deleteEdge(0, 1);
    cout << "deleting edge (0,2)... "<< endl; g->deleteEdge(0, 2);
    cout << "deleting edge (1,2)... "<< endl; g->deleteEdge(1, 2);
    cout << "deleting edge (0,4)... "<< endl; g->deleteEdge(0, 4);
    
    cout << "edges = " << g->numEdges() << endl;
    cout << "Edge List 0 is: "; g->printEdgeList(0);
    cout << "Edge List 1 is: "; g->printEdgeList(1);
    cout << "Edge List 2 is: "; g->printEdgeList(2);
    cout << "Edge List 3 is: "; g->printEdgeList(3);

    g->printVertices();
    cout << "Finding neighbours of 0... "; Graph<Node>::printEdgeList(g->neighbours(0));
    
    cout << "Deleting Node 3... " << endl; g->deleteNode(3); g->printVertices();
    cout << "Deleting Node 1... " << endl; g->deleteNode(1); g->printVertices();
    cout << "Finding neighbours of 1... "; Graph<Node>::printEdgeList(g->neighbours(1));
    
    cout << "Adding node 13... " << endl; g->addNode(13); g->printVertices();
    
    cout << "Clearing graph... " << endl; g->clear(0);
    *//*
    cout << "Making Random graph... " << endl; g->makeRandomGraph(0.1, 10, 50);
    g->print("Random Graph");
    */
    g->makeDemoGraph();
    g->print("Demo Graph");
    
    for (int i=0; i<g->numVertices(); ++i)
    {
        list<int> shortestPath = *new list<int>();
        g->getShortestPath(0, i, shortestPath);
        shortestPath.clear();
    }
    
    g = new Graph<Node>("/Volumes/Studio Drive 01/C++ for C Programmers/Dijkstra/Homework3_SampleTestData_mst_data.txt");
    g->print("Graph from file");
    
    for (int i=0; i<g->numVertices(); ++i)
    {
        list<int> shortestPath = *new list<int>();
        g->getShortestPath(0, i, shortestPath);
        shortestPath.clear();
    }
    
    return 0;
}