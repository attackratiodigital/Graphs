//
//  Node.h
//
//  Created by Anthony Cormican on 1/10/17.
//  Copyright (c) 2017 Anthony Cormican. All rights reserved.
//

#include <iostream>
#include <string>
#include <iomanip>

#ifndef __Node__
#define __Node__

/*
 This is the base class from which to derive all Vertex class from.
*/

class Node
{
public:
    Node() : desc(""), id(0) {}
    Node(std::string i, float w) : desc(i), id(0) {}
    
    void setName (std::string& name)        { desc = name; }
    std::string getName ()                  { return desc; }
    virtual void printName()                { std::cout << "(" << std::setprecision(2) << desc << ")"; }
    Node*  get_ptr()                        { return this; }
    unsigned long getId()                   { return id; }
    void setId (const unsigned long i)      { id = i; }
    
    friend std::ostream& operator<<(std::ostream& out, const Node& n);

protected:
    std::string desc;       // name of this node
private:
    unsigned long id;       // id of this node
};

#endif /* defined(__Node__) */
