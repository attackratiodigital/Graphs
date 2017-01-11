//
//  tests.cpp
//  Dijkstra
//
//  Created by Anthony Cormican on 1/9/17.
//  Copyright (c) 2017 Anthony Cormican. All rights reserved.
//

#include "tests.h"
/*
// Testing Routines
void tests()
{
    // populate some nodes with data
    List<Element> v;
    for (int i=0; i<10; i++)
    {
        Node* t = new Node;
        string s = to_string(i);
        t->setName(s);
        t->setWeight(static_cast<float>(i));
        v.add(*t);
    }
    
    // test print
    cout << "Testing:    print()" << endl;
    cout << "-------------------" << endl;
    v.print();
    cout << "Testing: printAddresses()" << endl;
    cout << "-------------------------" << endl;
    v.printAddresses();
    
    // test contains
    cout << "Testing: contains()" << endl;
    cout << "-------------------" << endl;
    Element* e = v.contains("41");
    cout << "address of 41 is " << e << endl;
    cout << "address of 4  is " << v.contains("4") << endl;
    
    // test insert
    cout << "Testing:   insert()" << endl;
    cout << "-------------------" << endl;
    Node* fn = new Node("123", 4.5);
    Element* f = new Element(*fn);
    v.insert("2", *f);
    
    Node* fn2 = new Node("123", 4.5);
    Element* f2 = new Element(*fn2);
    v.insert("6", *f2);
    
    Node* fn3 = new Node("f3", 25);
    Element* f3 = new Element(*fn3);
    v.insert("10", *f3);
    v.printAddresses();
    
    // test release
    cout << "Testing:  release()" << endl;
    cout << "-------------------" << endl;
    v.release();
    v.print();
}
*/

//g->neighbors(0, 5);
/*
 g->neighbors(2, 6);
 g->neighbors(0, 9);
 g->neighbors(3, 7);
 
 // Testing Add
 g->addEdge(3, 4);
 g->addEdge(1, 4);
 g->addEdge(1, 4);
 g->addEdge(1, 7);
 g->print();
 
 // Testing Delete
 g->deleteEdge(3, 4);
 g->deleteEdge(1, 4);
 g->deleteEdge(1, 4);
 g->deleteEdge(1, 7);
 g->deleteEdge(8, 0);
 g->print();

 cout << "3, 4 adjacent = " << g->adjacent(3, 4) << endl;
 cout << "8, 2 adjacent = " << g->adjacent(2, 8) << endl;
 
 // Testing Edge value
 cout << "edge value 0->35 is " << g->get_edge_value(0, 35) << endl;
 */



/*
Graph<Element>* makeDemoGraph()
{
    const float maxD = 10;
    Graph<Element>* g = new Graph<Element>;
    
    const int size = 10;
    assert(size < maxNodes);
    srand(static_cast <unsigned> (time(0)));    // seed the random number generation
    //create 'size' nodes first
    for (int i=0; i<size; ++i)
    {
        Node* t = new Node();
        string s = to_string(i);
        t->setName(s);
        t->setId(i);
        // generate a random edge distance within the range
        const float r2 = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX/maxD));
        t->setWeight(r2);
        g->edges[i].add(*t);
    }
    g->size = size;
    
    
    //size = 10;
    /*int node[size][size] = { {3, 4, 8, 9, -1},
     {3, 5, 7, -1},
     {1, 3, 6, 7, 8, -1},
     {5, 6, 9, -1},
     {2, 3, 6, 9, -1},
     {0, 7, -1},
     {0, 7, 8, 9, -1},
     {3, 4, 8, 9, -1},
     {1, 3, 4, -1},
     {1, 2, 8, -1} };
 
    
    
    //size = 10;
    int node[size][size] = { {1, 2, 4, 7, 8, 9, -1},
        {6, -1},
        {4, 6, 7, 8, -1},
        {0, 2, 5, 6, 7, 9 -1},
        {1, 5, 6, 7 -1},
        {0, 7, 9, -1},
        {5, 9, -1},
        {1, 8, -1},
        {3, 3, -1},
        {1, 7, -1} };
    
    

     // size = 10;
     // causes crash
     int node[size][size] = { {1, 3, 4, 5, 7, -1},
     {4, 7, -1},
     {0, 1, 3, 4, 5, 8, 9, -1},
     {5, 6, 9, -1},
     {5, 8, -1},
     {1, 7, 9, -1},
     {0, 7, 8, 9, -1},
     {3, -1},
     {0, 3, 5, 9, -1},
     {7, -1} };
     */
    
    // size = 6;
    /*int node[size][size] = { {5, 2, 4, -1},
     {3, 2, -1},
     {0, 1, 3, 4, 5, -1},
     {1, 4, 5, 2, -1},
     {0, 5, 2, 3, -1},
     {0, 3, 2, 4, -1} };
    
    
    for (int i=0; i<size; ++i)
        for (int j=0; node[i][j] != -1; ++ j)
        {
            Node* n = g->get_ptr(node[i][j])->data;
            g->edges[i].add(*n);
        }
    
    return g;
}
*/

