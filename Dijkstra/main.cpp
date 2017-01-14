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
    list<int> mstPath = *new list<int>();
    string f1= "/Volumes/Studio Drive 01/C++ for C Programmers/Dijkstra/Homework3_SampleTestData_mst_data.txt";
    auto g = new Graph<Node>(f1);
    
    g->print("Sample Test Data");
    cout << endl;
    cout << "Minimum Spanning Tree Length is: " << g->getPrimMST(mstPath) << endl;
    cout << "Edge weights traversed: "; Graph<Node>::printList(mstPath);
    
    return 0;
}