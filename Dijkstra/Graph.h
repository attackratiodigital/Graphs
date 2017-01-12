//
//  Graph.h
//  Dijkstra
//
//  Created by Anthony Cormican on 1/10/17.
//  Copyright (c) 2017 Anthony Cormican. All rights reserved.
//

#ifndef __Dijkstra__Graph__
#define __Dijkstra__Graph__

#include "List.h"
#include <vector>
#include <cassert>
#include <iostream>
#include <chrono>
#include <random>

const unsigned int maxNodes = 50;
const bool bidirectional = false;

using namespace std;

// class for containing a graph of nodes of type T
template<class T>
class Graph
{
public:
    typedef vector<List*> pathList;
    
    Graph();
    void print(string title) const;
    T* get_ptr(const int id);
    T* get_head(const int id);
    int numVertices() const { return size; }
    int numEdges() const;
    bool adjacent(const int x, const int y);
    bool findPaths(const int x, const int y, pathList& path);
    static void releasePaths(pathList& path);
    bool paths(const int x, const int y, pathList& path);
    bool nbr(T* l, List& visited, const int& y, typename pathList::iterator& pc, pathList& path);
    static float getShortestDistance(pathList& path);
    Graph<T>* addEdge(const int x, const int y);
    List* getEdge(const int i) { return &edges[i]; }
    Graph<T>* deleteEdge(const int x, const int y);
    int get_node_value(const int x) { return getVertex(x)->data->getId(); };
    void set_node_value(std::string s, const int x) { getVertex(x)->data->setId(s); }
    float get_edge_value(const int x, const int y) const;
    void set_edge_value(const float e, const int i) { getVertex(i)->data->setWeight(e); }
    Graph<T>* biDirect();
    Graph<T>* removeDuplicates();
    Graph<T>* makeRandomGraph(float edgeDensity, float maxDistance, int size);
    Graph<T>* makeDemoGraph();
    
    T* getVertex(const int i) const
    {
        if (i < 0 || i >= size)
            return nullptr;
        else
            return edges[i].first();
    }
    int getVertexID(const int i) const { return edges[i].first()->data->getId(); }
    T* getFirstEdge(const int i) const { return edges[i].get_head(); }
    
    int size;                           // number of nodes
private:
    List edges[maxNodes];            // array of linked lists holding all the edges for a node
    bool checkExist(const int x, const int y) const;
    bool stoprec = false;               // used for breaking recursion
};

#pragma mark Class Methods

template<class T> Graph<T>::Graph()
{
    // initialise the first nodes in the edge list
    for (int i=0; i<maxNodes; ++i)
        edges[i] = *new List();
}

// display the graph as an edge list abstraction
template<class T> void Graph<T>::print(string title) const
{
    cout << title << endl;
    cout << "ID:\t| Edges" << endl;
    cout << "--------------------------------------" << endl;
    for (int i=0; i<size; ++i)
    {
        cout << getVertexID(i) << ":\t| [";
        T* f = getFirstEdge(i);
        while(f->next != nullptr)
        {
            cout << f->data->getId();
            f = f->next;
            if (f->next != nullptr)
                cout << ", ";
        }
        cout << "]" << endl;
    }
    cout << endl;
}

// return a pointer to a graph element
template<class T> T* Graph<T>::get_ptr(const int id)
{
    assert(id < size);
    //cout << "First item "<<id<<" is "<<edges[id].first()->data->desc <<endl;
    return edges[id].first();
}

// return a pointer to the head element
template<class T> T* Graph<T>::get_head(const int id)
{
    assert(id < size);
    //cout << "First item "<<id<<" is "<<edges[id].first()->data->desc <<endl;
    return edges[id].get_head();
}

// returns the total number of edges in the graph
template<class T> int Graph<T>::numEdges() const
{
    int count = 0;
    for (int i=0; i<size; ++i)
        count += edges[i].size() - 1;
    return count;
}

// returns true if x has an edge to y
template<class T> bool Graph<T>::adjacent(const int x, const int y)
{
    assert(x < y);
    
    Element* temp = get_head(x);        // get the head of x's edge list
    while (temp != nullptr)
    {
        if (temp->data->getId() == y)
            return true;
        temp=temp->next;
    }
    return false;
}

// interface to paths() - this just does the display
template<class T> bool Graph<T>::findPaths(const int x, const int y, pathList& path)
{
    if (!checkExist(x, y))
        return false;
    cout << "--------------------------------------" << endl;
    cout << "Paths from node " << x << " to node " << y << ":" << endl;
    
    path.push_back(new List());
    bool found = false;
    found = paths(x, y, path);
    
    for (int i=0;i<path.size();++i)
    {
        path[i]->print(1);
        
    }
    cout << "shortest distance is " << setprecision(5) << getShortestDistance(path) << endl;
    cout << endl;
    return found;
}

// reclaim the memory by this pathList
template<class T> void Graph<T>::releasePaths(pathList& path)
{
    // clean up
    for (int i=0; i<path.size(); ++i)
    {
        path[i]->release();
        path.pop_back();
    }
    path.clear();
}

// if any paths exist between x and y this function will return true
// and return a vector of vertex lists for each path from x to y in allPaths
template<class T> bool Graph<T>::paths(const int x, const int y, pathList& path)
{
    typename vector<List*>::iterator pc;
    pc = path.begin();
    
    float shortest_distance = 0;
    bool found = false;
    List temp = edges[x];
    /*
    if (temp.contains(y) != nullptr)
    {
        cout << "(" << x << ")->(" << y << ")" << endl << endl;
        shortest_distance = get_edge_value(x, y);
        
        (*pc)->add(*getVertex(x)->data);
        (*pc)->add(*getVertex(y)->data);
        return true;
    }
    */
    T* w = getFirstEdge(x);
    while (w->next != nullptr)
    {
        stoprec = false;
        cout << "(" << x << ")->";
        
        (*pc)->add(*getVertex(x)->data);
        List* visited = new List();
        found = nbr(w, *visited, y, pc, path);
        visited->release();
        w = w->next;
    }
    cout << endl;
    
    // remove any NULL elements from the path lists created by the
    // recursion
    int i = 0;
    while(i<path.size())
    {
        if (path[i]->size() == 0)
        {
            path[i]->release();
            path.erase(path.begin()+i);
        }
        else
            ++i;
    }
    
    return found;
}

// the recursive routine to parse every possible node in the graph and return all possible
// paths from node x to node y as defined in the previous method
template<class T> bool Graph<T>::nbr(T* l, List& visited, const int& y, typename pathList::iterator& pc,
                                     pathList& path)
{
    bool found = false;
    int data_id = 0;

    
    if (l->next == nullptr)
    {
        (*pc)->add(*getVertex(y)->data);
        (*pc)->add(*getVertex(data_id)->data);
        //cout << "(" << data_id << /*")->(" << y << ")" << */  endl;
        path.push_back(new List());
        pc = path.end()-1;
    }
    else
    {
        data_id = l->data->getId();


        if (edges[data_id].contains(y) == nullptr)
        {
            if (visited.contains(data_id) == nullptr)
            {
                visited.add(*l->data->get_ptr());
                cout << "(" << data_id << ")->";
                (*pc)->add(*getVertex(data_id)->data);
                nbr(edges[data_id].get_head(), visited, y, pc, path);
            }
            else
            {
                // move to the next node
                /*while (visited.contains(data_id) != nullptr && l->next!= nullptr)*/
                {
                    l=l->next;
                    visited.add(*l->data->get_ptr());
                    
                    //data_id = l->data->getId();
                }
                //l = l->next;
                //if (l!=nullptr)
                    nbr(l, visited, y, pc, path);
            }
        }
    }
    return found;
}

// return the shortest distance from a set of paths
template<class T> float Graph<T>::getShortestDistance(pathList& path)
{
    float minimum = 0;
    float sum = 0;
    for (auto it : path)
    {
        sum = 0;
        T* temp = (*it).get_head()->next;   // don't include the last node as we have arrived there
        while(temp != nullptr)
        {
            sum += temp->data->getEdge();
            temp = temp->next;
        }
        if (sum < minimum)
            minimum = sum;
    }
    return sum;
}

// Add an edge between x and y if it does not already exist
template<class T> Graph<T>* Graph<T>::addEdge(const int x, const int y)
{
    assert(x != y);
    if (!checkExist(x, y))
        return false;
    
    Node* n = this->get_ptr(y)->data;
    this->edges[x].add(*n);
    return this;
}

// Delete the edge between x and y if it exists
template<class T> Graph<T>* Graph<T>::deleteEdge(const int x, const int y)
{
    assert(x != y);
    if (!checkExist(x, y))
        return false;
    
    this->edges[x].del(y);
    return this;
}

// return the edge value between to nodes
template<class T> float Graph<T>::get_edge_value(const int x, const int y) const
{
    assert(x != y);
    if (!checkExist(x, y))
        return false;
    
    // check that they are connected
    if (edges[x].contains(y) != nullptr)
        return edges[x].get_element(y)->data->getEdge();
    else
        return 0;
}

// Create two way edges (if not already there) for all edges
template<class T> Graph<T>* Graph<T>::biDirect()
{
    // to ensure edge bi-directionality, go through each edge list and add the reverse-direction edge to the
    // corresponding node; i.e. map (2,3) to (3,2)
    for (int i=0; i<size; ++i)
    {
        Element* temp = this->get_head(i);        // get the head of this edge list
        while (temp != nullptr)
        {
            int thisNode = temp->data->getId();       // get the id we're looking for
            if (thisNode != i)
            {
                Node* n = this->get_ptr(i)->data;
                this->edges[thisNode].add(*n);
            }
            temp = temp->next;
        }
    }
    return this;
}

// Removes any two-way edges forcing a one way graph
template<class T> Graph<T>* Graph<T>::removeDuplicates()
{
    for (int i=0; i<size; ++i)
    {
        //cout << endl; g->print();
        Element* temp = this->get_head(i);        // get the head of this edge list
        while (temp != nullptr)
        {
            int thisNode;
            thisNode = temp->data->getId();       // get the id we're looking for
            if (thisNode != i)
            {
                this->edges[thisNode].del(i);
            }
            temp = temp->next;
        }
    }
    return this;
}

// check that the nodes x and y exist in the graph
template<class T> bool Graph<T>::checkExist(const int x, const int y) const
{
    // check that both nodes exist
    if (getVertex(x) == nullptr)
    {
        cout << "Node " << x << " does not exist in this graph" << endl;
        return false;
    }
    
    if (getVertex(y) == nullptr)
    {
        cout << "Node " << y << " does not exist in this graph" << endl;
        return false;
    }
    return true;
}

// Generates a random graph with:
//      number of nodes: size
//      maximum distance/weighting for an edge: maxDistance
//      number of edges from each node: edgeDensity (this is a probability, not a discrete value of edges)
// returns a Graph object containing 'size' nodes with edge lists containing no self referencing nodes and
// ensuring that bi-directionality is implemented
template<class T> Graph<T>* Graph<T>::makeRandomGraph(float edgeDensity, float maxDistance, int size)
{
    //Graph<T>* g = new Graph<T>;
    assert(size <= maxNodes);
    
    srand(static_cast <unsigned> (time(0)));    // seed the random number generation
    
    //create 'size' nodes first
    for (int i=0; i<size; ++i)
    {
        Node* t = new Node();
        string s = to_string(i);
        t->setName(s);
        t->setId(i);
        // generate a random edge distance within the range
        const float r2 = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX/maxDistance-1)) + 1;
        t->setEdge(r2);
        getEdge(i)->add(*t); //this
    }
    this->size = size;
    
    //traverse each node and add edges according to probability density
    for (int i=0; i<size;++i)
    {
        for (int j=0; j<size; ++j)
        {
            if (j != i)
            {
                const float r = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
                if (r < edgeDensity)
                {
                    Element* e = get_ptr(j); //this
                    if (e != nullptr)
                    {
                        Node* temp = get_ptr(j)->data;   // get pointer to first element in this array - this
                        // add if not already there
                        if (getEdge(i)->contains(temp->getName()) == nullptr)    // do not create any self referential loops
                            getEdge(i)->add(*temp);
                    }
                }
            }
        }
    }
    
    if (bidirectional)
        biDirect();
    else
        removeDuplicates();
    return this;
}

template<class T> Graph<T>* Graph<T>::makeDemoGraph()
{
    const float maxD = 10;
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
        t->setEdge(r2);
        getEdge(i)->add(*t); //this
    }
    this->size = size;
    
    
    //size = 10;
    /*
     int node[size][size] = { {3, 4, 8, 9, -1},
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
     */
     
     // size = 10;
    // crashes
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
     
    /*
    // size = 6;
    int node[size][size] = { {5, 2, 4, -1},
        {3, 2, -1},
        {0, 1, 3, 4, 5, -1},
        {1, 4, 5, 2, -1},
        {0, 5, 2, 3, -1},
        {0, 3, 2, 4, -1} };
    */
    
    for (int i=0; i<size; ++i)
        for (int j=0; node[i][j] != -1; ++ j)
        {
            Node* n = this->get_ptr(node[i][j])->data;
            this->getEdge(i)->add(*n);
        }
    
    return this;
}

#endif /* defined(__Dijkstra__Graph__) */
