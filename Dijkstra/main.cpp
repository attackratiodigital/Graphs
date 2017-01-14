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
#include "Graph.h"

int main(int argc, const char * argv[])
{
    auto mstPath = *new EdgeList();
    string f1= "/Volumes/Studio Drive 01/C++ for C Programmers/Dijkstra/Homework3_SampleTestData_mst_data.txt";
    auto g = new Graph<Node>(f1);
    
    g->print("Sample Test Data");
    cout << endl;
    cout << "Minimum Spanning Tree Length is: " << g->getPrimMST(mstPath) << endl;
    cout << "Edge weights traversed: " << endl;
    for (auto it : *mstPath.first())
        cout << it;

    return 0;
}