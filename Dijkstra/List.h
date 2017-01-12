//
//  List.h
//  Dijkstra
//
//  Created by Anthony Cormican on 1/10/17.
//  Copyright (c) 2017 Anthony Cormican. All rights reserved.
//

#ifndef __Dijkstra__List__
#define __Dijkstra__List__

#include "Node.h"
#include <iostream>
#include <string>

// a container class to hold the data
class Element
{
public:
    Element() : next(nullptr) { data = new Node(); data = nullptr; }
    Element(Node& n) : next(nullptr) { data = new Node(); data = &n; }
    
    Node* data;
    Element* next;
};

// the class that allows the manipulation of a linked list to
// hold pointers to each node
class List
{
public:
    List() : head(nullptr) {}
    ~List() {}
    
    void add(Node& n);
    void addAllowDuplicate(Node& n);
    Element*   first() const;
    Element*   get_head() const;
    Element*   get_element(const int n) const;
    void del();
    void del(const int i);
    void print(const int& i) const;
    void printRecursive(Element* curr_ptr, const int& i) const;
    void printAddresses() const;
    void release();
    Element*   contains(std::string name) const;
    Element*   contains(const int e) const;
    void insert(std::string name, Element& e);
    void insert(const int i, Element& e);
    int size() const;
private:
    Element* head;
};

#endif /* defined(__Dijkstra__List__) */
