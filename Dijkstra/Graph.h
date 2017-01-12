//
//  Graph.h
//  Dijkstra
//
//  Created by Anthony Cormican on 1/10/17.
//  Copyright (c) 2017 Anthony Cormican. All rights reserved.
//

#ifndef __Dijkstra__Graph__
#define __Dijkstra__Graph__

#include <list>
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
    struct Adj;
public:
    Graph(const int size = 10);
    ~Graph();
    
    void addNode(const int index);
    void addNode(string name);
    void deleteNode(const int n);
    string getNodeName(const int x) const;
    void setNodeName(string s, const int x);
    
    void addEdge(const int x, const int y, const float value = 0.0);
    void deleteEdge(const int x, const int y);
    float getEdgeValue(const int x, const int y) const;
    void setEdgeValue(const int x, const int y, const float value = 0.0);
    unsigned long numEdges() const;
    
    void printVertices() const;
    void printEdgeList(const int v) const;
    void print(string title) const;
    static void printEdgeList(list<Adj> l);
    static void printEdgeList(list<int> l);
    unsigned long numVertices() const { return V.size(); }

    bool adjacent(const int x, const int y) const;
    list<int> neighbours (const int x) const;
    //bool findPaths(const int x, const int y, pathList& path);
    //static void releasePaths(pathList& path);
    //bool paths(const int x, const int y, pathList& path);
    //bool nbr(T* l, List& visited, const int& y, typename pathList::iterator& pc, pathList& path);
    //static float getShortestDistance(pathList& path);
    //Graph<T>* biDirect();
    //Graph<T>* removeDuplicates();
    void makeRandomGraph(float edgeDensity, float maxDistance, unsigned long size);
    void clear(unsigned long size);
    //Graph<T>* makeDemoGraph();
    
private:
    struct Adj {
        int edge;
        float value;
    };
    
    vector<list<Adj>> edges;
    vector<T*> V;
    
    bool exists(const int x) const;
    static bool contains(list<Adj>& edgeList, const int x);
};

#pragma mark Class Methods

template<class T>
Graph<T>::Graph(const int size)
{
    // initialise the Vertices
    for (int i = 0; i < size; ++i)
        addNode(to_string(i));
    
    // initialise the edge lists
    for (int i = 0; i < size; ++i)
        edges.push_back(*new list<Adj>);
}

template<class T>
Graph<T>::~Graph()
{
        // delete all the Nodes from V
    //delete all edge lists
}

// clears all nodes and edges from the graph
template<class T>
void Graph<T>::clear(unsigned long size)
{
    for (int i = 0; i < numVertices(); ++i)
        deleteNode(i);
    edges.resize(size);
    V.resize(size);
}

template<class T>
void Graph<T>::addNode(string name)
{
    T* n = new T();
    n->setName(name);
    V.push_back(n);
    n->setId(V.size() - 1);
}

template<class T>
void Graph<T>::addNode(const int index)
{
    if (index < V.size())
        cout << "Node already exists!" << endl;
    else
    {
        V.resize(index);
        T* n = new T();
        string s = to_string(index);
        n->setName(s);
        
        V.push_back(n);
        n->setId(V.size() - 1);
    }
}

// remove the node n from the graph
template<class T>
void Graph<T>::deleteNode(const int n)
{
    // this doesn't actually delete the node from the vector,
    // but assigns it to a nullptr value.  This way the one to
    // one mapping of node id to vector index holds.
    if (V[n] != nullptr)
        if (!edges[n].empty())
            edges[n].erase(edges[n].begin(), edges[n].end());
    V[n] = nullptr;
}


// returns true if an edge list contains a given edge x
template<class T>
bool Graph<T>::contains(list<Adj>& edgeList, const int x)
{
    for (auto it : edgeList)
        if (it.edge == x)
            return true;
    return false;
}

template<class T>
void Graph<T>::addEdge(const int x, const int y, const float value)
{
    if (exists(x) && exists(y))
    {
        if (!contains(edges[x], y))
            edges[x].push_back( {y, value} );
    }
}

template<class T>
void Graph<T>::deleteEdge(const int x, const int y)
{
    if (exists(x) && exists(y))
        if (contains(edges[x], y))
            edges[x].remove_if([y](Adj a) { return a.edge == y; });
}

template<class T>
void Graph<T>::printVertices() const
{
    for ( auto it : V)
        if (it != nullptr)
            cout << (*it);
        else
            cout << "null";
    cout << endl;
}

// outputs the edge list for a vertex v
template<class T>
void Graph<T>::printEdgeList(const int v) const
{
    typename list<Adj>::const_iterator last = edges[v].end() ;
    last--;
    for (typename list<Adj>::const_iterator it = edges[v].begin(); it != edges[v].end(); ++it)
    {
        cout << (*it).edge;
        if (it != last)
            cout << ", ";
    }
}

// outputs the edge list for a list of Adj
template<class T>
void Graph<T>::printEdgeList(list<Adj> l)
{
    typename list<Adj>::const_iterator last = l.end() ;
    last--;
    for (auto it : l)
    {
        cout << (*it).edge;
        if (it != last)
            cout << ", ";
    }
}

// outputs the edge list for a list of ints
template<class T>
void Graph<T>::printEdgeList(list<int> l)
{
    list<int>::const_iterator last = l.end() ;
    last--;
    for (list<int>::const_iterator it = l.begin(); it != l.end(); ++it)
    {
        cout << *it;
        if (it != last)
            cout << ", ";
    }
}


// display the graph as an edge list abstraction
template<class T> void Graph<T>::print(string title) const
{
    cout << title << endl;
    cout << "ID:\t| Edges" << endl;
    cout << "--------------------------------------" << endl;
    for (int i = 0; i < numVertices(); ++i)
    {
        cout << i << ":\t| [";
        printEdgeList(i);
        cout << "]" << endl;
    }
}

template<class T>
unsigned long Graph<T>::numEdges() const
{
    unsigned long sum = 0;
    for (auto it : edges)
        sum += it.size();
    return sum;
}

template<class T>
bool Graph<T>::adjacent(const int x, const int y) const
{
    if (exists(x) && exists(y))
    {
        if (!edges[x].empty())
        {
            for (auto it : edges[x])
                if (it.edge == y)
                    return true;
        }
    }
    return false;
}

// returns a list of all nodes that have an edge to x
template<class T>
list<int> Graph<T>::neighbours (const int x) const
{
    // TODO: make this a pass by ref value
    list<int> temp = *new list<int>();
    // find node x in all the edge lists and return the node they join to
    for (int i = 0; i < numVertices(); ++i)
    {
        for (auto it : edges[i])
            if (it.edge == x)
                temp.push_back(i);
    }
    for (auto it : edges[x])
        temp.push_back(it.edge);
    
    temp.sort();
    temp.unique();
    return temp;
    // delete temp?
}

template<class T>
void Graph<T>::setNodeName(string s, const int x)
{
    if (exists(x))
        V[x]->setName(s);
}

template<class T>
string Graph<T>::getNodeName(const int x) const
{
    if (exists(x))
        return V[x]->getName();
    return "";
}

template<class T>
void Graph<T>::setEdgeValue(const int x, const int y, const float value)
{
    if (exists(x) && exists(y))
    {
        if (!edges[x].empty())
        {
            for (auto &it : edges[x])
                if (it.edge == y)
                {
                    it.value = value;
                    break;
                }
        }
    }
}

template<class T>
float Graph<T>::getEdgeValue(const int x, const int y) const
{
    if (exists(x) && exists(y))
    {
        if (!edges[x].empty())
        {
            for (auto it : edges[x])
            if (it.edge == y)
                return it.value;
        }
    }
    return 0;
}

// check that the nodes x and y exist in the graph
template<class T>
bool Graph<T>::exists(const int x) const
{
    if (V.size() - 1 >= x)
        return true;
    return false;
}

template<class T>
void Graph<T>::makeRandomGraph(float edgeDensity, float maxDistance, unsigned long size)
{
    srand(static_cast <unsigned> (time(0)));    // seed the random number generation
 
    clear(size);
    //create 'size' nodes first
        
    for (int i = 0; i < numVertices(); ++i)
        for (int j = 0; j < numVertices(); ++j)
        {
            const float prob = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
            if (prob < edgeDensity)
                addEdge(i, j, static_cast <float> (rand()) / (static_cast <float> (RAND_MAX/maxDistance-1)) + 1);
        }
}

/*
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
     

    // size = 6;
    int node[size][size] = { {5, 2, 4, -1},
        {3, 2, -1},
        {0, 1, 3, 4, 5, -1},
        {1, 4, 5, 2, -1},
        {0, 5, 2, 3, -1},
        {0, 3, 2, 4, -1} };

    
    for (int i=0; i<size; ++i)
        for (int j=0; node[i][j] != -1; ++ j)
        {
            Node* n = this->get_ptr(node[i][j])->data;
            this->getEdge(i)->add(*n);
        }
    
    return this;
}
*/
#endif /* defined(__Dijkstra__Graph__) */
