//
//  Node.h
//  Dijkstra
//
//  Created by Anthony Cormican on 1/10/17.
//  Copyright (c) 2017 Anthony Cormican. All rights reserved.
//

#include <iostream>
#include <string>
#include <iomanip>

#ifndef __Dijkstra__Node__
#define __Dijkstra__Node__

// the data contained in a graph node
class Node
{
public:
    Node() : desc(""), id(0), edge(0.0) {}
    Node(std::string i, float w) : desc(i), id(0), edge(w) {}
    
    void   setName (std::string& name)   { desc = name; }
    std::string getName ()               { return desc; }
    void   setEdge(const float w)   { edge = w; }
    float  getEdge()                { return edge; }
    void   print()                  { std::cout << "(" << std::setprecision(2) << desc << ", " << edge << ")"; }
    void   printName()              { std::cout << "(" << std::setprecision(2) << desc << ")"; }
    void   printWeight()            { std::cout << "(" << std::setprecision(2) << edge << ")"; }
    Node*  get_ptr()                { return this; }
    int    getId()                  { return id; }
    void   setId (const int i)      { id = i; }
    
private:
    std::string desc;        // name of this node
    float edge;       // edge weighting
    int id;             // id of this node
};

#endif /* defined(__Dijkstra__Node__) */
