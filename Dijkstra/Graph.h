//
//  Graph.h
//
//  Created by Anthony Cormican on 1/10/17.
//  Copyright (c) 2017 Anthony Cormican. All rights reserved.
//

#ifndef __Graph__
#define __Graph__

#include <list>
#include <vector>
#include <queue>
#include <cassert>
#include <string>
#include <sstream>
#include <fstream>
#include <iostream>
#include <chrono>
#include <random>

using namespace std;

/*
 This class holds the infomation and methods on the edge between two nodes in a graph
*/
class Edge
{
public:
    Edge(const int from, const int to, const float w) : from(from), to(to), weight(w) {}
    int getStart() const { return from; }
    void setStart(const int s) { from = s; }
    int getEnd() const { return to; }
    void setEnd(const int e) { to = e; }
    float getWeight() const { return weight; }
    void setWeight(const float w) { weight = w; }
    
    friend class EdgeList;
    friend ostream& operator<<(ostream& out, const Edge& e)
    {
        return (out << "Edge (" << e.from << ", " << e.to << ") = " << e.weight << endl);
    }
    
private:
    int from, to;
    float weight;
};

/*
 The list of edges that are connected to a node and the operations on that list
*/
class EdgeList
{
public:
    EdgeList() {};
    ~EdgeList() { clear(); }
    
    void clear() { edgeList.clear(); }
    bool empty() const { return edgeList.empty(); }
    bool contains(const int x)
    {
        for (auto it : edgeList)
            if (it.to == x)
                return true;
        return false;
    }
    
    void add(Edge& e) { edgeList.push_back(e); }
    void del(const int y) { edgeList.remove_if([y](Edge e) { return e.to == y; } ); }
    unsigned long size() { return edgeList.size(); }
    list<Edge>* first() { return &edgeList; }
    
    friend ostream& operator<<(ostream& out, const EdgeList& e)
    {
        typename list<Edge>::const_iterator last = e.edgeList.end() ;
        last--;
        for (typename list<Edge>::const_iterator it = e.edgeList.begin(); it != e.edgeList.end(); ++it)
        {
            out << (*it).getEnd() << "(" <<(*it).getWeight() << ")";
            if (it != last)
                out << ", ";
        }
        return out;
    }
    
private:
    list<Edge> edgeList;
};

/*
 class for containing a graph of nodes of type T
*/
template<typename T>
class Graph
{
public:
    Graph(const int size = 10) { construct(size); }
    Graph(string filename);
    ~Graph() { clear(0); }
    
    void clear(unsigned long size);
    void addNode(const int index);
    void addNode(string name);
    void deleteNode(const int n);
    string getNodeName(const int x) const;
    void setNodeName(string s, const int x);
    
    void addEdge(const int x, const int y, const float value = 0.0);
    void deleteEdge(const int x, const int y);
    float getEdgeValue(const int x, const int y);
    void setEdgeValue(const int x, const int y, const float value = 0.0);
    int numEdges() const;
    int numVertices() const { return static_cast<int>(V.size()); }
    
    void printVertices() const;
    void printEdgeList(const int v) const;
    void print(string title) const;
    static void printList(list<int> l);

    bool adjacent(const int x, const int y);
    list<int> neighbours (const int x);

    void makeRandomGraph(float edgeDensity, float maxDistance, unsigned long size);
    float getShortestPath(const int start, const int end, list<int>& path);
    float getPrimMST(const int start, const int end, EdgeList& path);
    float getPrimMST(EdgeList& path);
    float getPrimMST();
    
private:
    vector<EdgeList> edges;
    vector<T*> V;

    bool exists(const int x) const;
    void construct(const int size);
};

#pragma mark Class Methods

template<class T>
void Graph<T>::construct(const int size)
{
    // initialise the Vertices
    V.clear();
    for (int i = 0; i < size; ++i)
        addNode(to_string(i));
    
    // initialise the edge lists
    edges.clear();
    for (int i = 0; i < size; ++i)
        edges.push_back(*new EdgeList());
}

// read a Graph in from a file
template<class T>
Graph<T>::Graph(string filename)
{
    int n;
    int s, e, w;
    
    ifstream in(filename);
    if (in.good())
    {
        in >> n;     // the size of the graph
        construct(n);
        while (in >> s >> e >> w)
            addEdge(s, e, w);

        in.close();
    }
    else
        cout << "File does not exist!" << endl;
}

// clears all nodes and edges from the graph
template<class T>
void Graph<T>::clear(unsigned long size)
{
    for (int i = 0; i < numVertices(); ++i)
        deleteNode(i);
    edges.clear();
    edges.resize(size);
    V.clear();
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
            edges[n].clear();
    V[n] = nullptr;
}

template<class T>
void Graph<T>::addEdge(const int x, const int y, const float value)
{
    if (exists(x) && exists(y))
        if (!edges[x].contains(y))
        {
            Edge e = *new Edge(x, y, value);
            edges[x].add(e);
        }
}

template<class T>
void Graph<T>::deleteEdge(const int x, const int y)
{
    if (exists(x) && exists(y))
        if (edges[x].contains(y))
            edges[x].del(y);
}

template<class T>
void Graph<T>::printVertices() const
{
    for (auto it : V)
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
    cout << edges[v];
}

// outputs the edge list for a list of ints
template<class T>
 void Graph<T>::printList(list<int> l)
{
    list<int>::const_iterator last = l.end() ;
    last--;
    cout << "(";
    for (list<int>::const_iterator it = l.begin(); it != l.end(); ++it)
    {
        cout << *it;
        if (it != last)
            cout << ", ";
    }
    cout << ")";
}

// display the graph as an edge list abstraction
template<class T> void Graph<T>::print(string title) const
{
    cout << title << endl;
    cout << "ID:\t| Edges (Weight)" << endl;
    cout << "--------------------------------------" << endl;
    for (int i = 0; i < numVertices(); ++i)
    {
        cout << to_string(i) + ":\t| [";
        auto r = *new EdgeList();

        struct comparator {
            bool operator()(const Edge& lhs, const Edge& rhs) const
            {
                return (lhs.getEnd() < rhs.getEnd());
            }
        };
        r = edges[i];
        r.first()->sort(comparator());

        cout << r;
        cout << "]" << endl;
    }
}

template<class T>
int Graph<T>::numEdges() const
{
    unsigned long sum = 0;
    for (auto it : edges)
        sum += it.size();
    return sum;
}

template<class T>
bool Graph<T>::adjacent(const int x, const int y)
{
    if (exists(x) && exists(y))
        if (!edges[x].empty())
            for (auto it : *edges[x].first() )
                if (it.getEnd() == y)
                    return true;
    return false;
}

// returns a list of all nodes that have an edge to x
template<class T>
list<int> Graph<T>::neighbours (const int x)
{
    list<int> temp = *new list<int>();
    // find node x in all the edge lists and return the node they join to
    for (int i = 0; i < numVertices(); ++i)
        for (auto it : *edges[i].first())
            if (it.getEnd() == x)
                temp.push_back(i);

    temp.sort();
    temp.unique();
    return temp;
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
        if (!edges[x].empty())
            for (auto &it : *edges[x].first())
                if (it.getEnd() == y)
                {
                    it.setWeight(value);
                    break;
                }
}

template<class T>
float Graph<T>::getEdgeValue(const int x, const int y)
{
    if (exists(x) && exists(y))
        if (!edges[x].empty())
            for (auto it : *edges[x].first())
            if (it.getEnd() == y)
                return it.getWeight();
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
        
    for (int i = 0; i < numVertices(); ++i)
        for (int j = 0; j < numVertices(); ++j)
        {
            const float prob = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
            if (prob < edgeDensity)
            {
                const float w = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX/maxDistance-1)) + 1;
                addEdge(i, j, w);
                addEdge(j, i, w);
            }
        }
}

template<class T>
float Graph<T>::getShortestPath(int start, const int end, list<int>& path)
{
    if (!exists(start) || !exists(end))
        return numeric_limits<float>::infinity();
        
    // a vector (size numVertices) to hold the cumulative distances
    vector<float> dist = vector<float>(numVertices(), numeric_limits<float>::infinity());
    
    dist[start] = 0;
    
    typedef pair<float, int> dn;   //distance, node pair
    priority_queue<dn, vector<dn>, greater<dn> > openSet;
    
    openSet.push(make_pair(dist[start], start));
    vector<int> prevNode = vector<int>(numVertices(), numeric_limits<int>::infinity());
    prevNode[start] = start;
    
    while (!openSet.empty())
    {
        int s = openSet.top().second;
        openSet.pop();
        if (s == end)
            break;
        
        for (int u : neighbours(s))
        {
            float candPath = dist[s] + getEdgeValue(s, u);
            if (candPath < dist[u])
            {
                dist[u] = candPath;
                prevNode[u] = s;
                openSet.push(make_pair(dist[u], u));
            }
        }
    }

    // copy to path
    if (dist[end] < numeric_limits<float>::infinity())
    {
        int currNode = end;
        path.push_front(currNode);
        while (currNode != start)
        {
            currNode = prevNode[currNode];
            path.push_front(currNode);
        }
    }
    
    cout << "Shortest Path between " << start << " & " << end << " is: ";
    printList(path);
    cout << " with an edge value of " << dist[end] << endl;
    
    return dist[end];
}

template<class T>
float Graph<T>::getPrimMST()
{
    EdgeList em = *new EdgeList();
    return getPrimMST(0, static_cast<int>(numVertices()-1), em);
}

template<class T>
float Graph<T>::getPrimMST(EdgeList& path)
{
    return getPrimMST(0, static_cast<int>(numVertices()-1), path);
}

template<class T>
float Graph<T>::getPrimMST(const int start, const int end, EdgeList& path)
{
 /*
    Prim Minimum Spanning Tree algorithm
    Requires that the graph is connected and has positive edge weights
    Returns: the weight of the MST, and the edge list of the nodes that represent the mst
    Works in O(V^2) time 
 */
    typedef pair<float, int> mst_pair;
    vector<mst_pair> Q;
    vector<bool> visited(numVertices(), false);
 
    float s = static_cast<float>(start);
    Q.push_back(make_pair(s, 0.0));
    visited[0] = true;
    
    float minDist = 0;
    while (Q.size() != numVertices())
    {
        minDist = numeric_limits<float>::infinity();
        int prev = 0, next = 0;
        for (int i = 0; i < Q.size(); ++i)
        {
            s = Q[i].second;
            for (int u : neighbours(s))
                if (!visited[u])
                    if (getEdgeValue(s, u) < minDist)
                    {
                        minDist = getEdgeValue(s, u);
                        prev = u;
                        next = s;
                    }
        }
        visited[prev] = true;
        Q.push_back(make_pair(minDist, prev));
        auto mstEdge = *new Edge(next, prev, minDist);
        path.add(mstEdge);
    }
    
    float sum = 0.0;
    for (auto &it : Q)
        sum += it.first;
    
    return sum;
}

#endif /* defined(__Graph__) */
