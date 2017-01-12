//
//  Node.cpp
//  Dijkstra
//
//  Created by Anthony Cormican on 1/10/17.
//  Copyright (c) 2017 Anthony Cormican. All rights reserved.
//

#include "Node.h"

using namespace std;

ostream& operator<<(ostream& out, const Node& n)
{
    return (out << "(" << setprecision(2) << n.desc << ")");
}