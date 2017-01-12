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
    typedef std::vector<List*> pathList;    // to hold the list of paths
    const int size = 10;
/*
    // Compute averages for graph 1
    //Graph<Element>* g = makeRandomGraph(0.2, 10, size);
    Graph<Element>* g = makeDemoGraph();
    g->print("Graph 1: Edge Density 20%, Distance Range = 10, Size = 50");
    cout << "Graph 1:" << endl;
    cout << "Number of Vertices: " << g->numVertices() << endl;
    cout << "Number of Edges: " << g->numEdges() << endl;

    float distance = 0;
    for (int i=1; i<size; ++i)
    {
        auto thisPath = *new pathList();
        g->findPaths(0, i, thisPath);
        distance += Graph<Element>::getShortestDistance(thisPath);
        Graph<Element>::releasePaths(thisPath);
    }
    cout << "Average distance of Graph 1 = " << distance / size << endl;
    cout << "#---------------------------------------------------------------------------#" << endl;
    cout << endl << endl;
    */
    
    // Compute averages for graph 2
    Graph<Element>* g2 = new Graph<Element>();
    g2->makeDemoGraph();
    g2->print("Graph 2: Edge Density 40%, Distance Range = 10, Size = 50");
    std::cout << "Graph 2:" << std::endl;
    std::cout << "Number of Vertices: " << g2->numVertices() << std::endl;
    std::cout << "Number of Edges: " << g2->numEdges() << std::endl;

    float distance = 0;
    for (int i=1; i<2; ++i)
    {
        auto thisPath = *new pathList();
        g2->findPaths(0, i, thisPath);
        distance += Graph<Element>::getShortestDistance(thisPath);
        Graph<Element>::releasePaths(thisPath);
    }
    
    cout << "Average distance of Graph 2 = " << distance / size << endl;
    return 0;
}