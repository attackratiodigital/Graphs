//
//  List.cpp
//  Dijkstra
//
//  Created by Anthony Cormican on 1/10/17.
//  Copyright (c) 2017 Anthony Cormican. All rights reserved.
//

#include "Node.h"
#include "List.h"
#include <cassert>

using namespace std;

// insert a new element at the end of the list only if does not
// already exist
void List::add(Node &n)
{
    Element* temp = new Element();
    assert(temp != nullptr);
    
    // avoid duplicates
    Element* already_here = this->contains(n.getName());
    if (already_here == nullptr)
    {
        temp->data = &n;
        //temp->data->visited = false;
        temp->next = head;
        head = temp;
    }
}

// insert an element, even if it already exists in the list
void List::addAllowDuplicate(Node &n)
{
    Element* temp = new Element();
    assert(temp != nullptr);
    
    temp->data = &n;
    //temp->data->visited = false;
    temp->next = head;
    head = temp;
}

// return a pointer to the first element in a list
Element* List::first() const
{
    Element* temp = head;
    while (temp->next != nullptr)
        temp = temp->next;
    return temp;
}

// return a pointer to the first element in a list
Element* List::get_head() const
{
    return head;
}

// return a pointer to the nth element in a list
Element* List::get_element(const int e) const
{
    Element* temp = head;
    while (temp != nullptr)
        if (temp->data->getId() != e) temp = temp->next; else break;
    return temp;
}

// delete an element from a list
void List::del()
{
    Element* temp = head;
    head = head->next;
    //cout << "Deleting node: " << temp->data->getName() << endl;
    delete temp;
}

// delete an element from a list
void List::del(const int i)
{
    Element* temp = head;
    Element* prev = temp;
    
    // check if it's the head
    if (temp->data->getId() == i)
    {
        temp = head;
        head = temp->next;
        delete temp;
        return;
    }
    
    while (temp != nullptr)
    {
        if (temp->data->getId() == i)
        {
            prev->next = temp->next;
            //cout << "Deleting node: " << temp->data->getName() << endl;
            delete temp;
            break;
        }
        else
        {
            prev = temp;
            temp = temp->next;
        }
    }
}

// used to enable printing from the tail to the head of the list
void List::printRecursive(Element* curr_ptr, const int &i) const
{
    if (curr_ptr == nullptr)
        return;
    printRecursive(curr_ptr->next, i);
    cout << "->";
    switch (i)
    {
        case 0: curr_ptr->data->print(); break;
        case 1: curr_ptr->data->printName(); break;
        case 2: curr_ptr->data->printWeight(); break;
        default: break;
    }
}

// display the elements in a list
// using recursion to print from end to start
void List::print(const int& i) const
{
    Element* temp = head;
    printRecursive(temp, i);
    cout << endl;
}

// output memory addresses for all nodes
void List::printAddresses() const
{
    Element* temp = head;
    while(temp != nullptr)
    {
        cout << "Address of node ID: " << temp->data->getName() << " is " << temp->data->get_ptr() << endl;
        temp = temp->next;
    }
    cout << endl << endl;
}

// reclaims memory used by the list
void List::release()
{
    while (head != nullptr)
        del();
}

// returns a pointer to the node specified by name if it exists
// otherwise returns a nullptr
Element* List::contains(const string name) const
{
    Element* temp = head;
    while (temp != nullptr)
    {
        if (temp->data->getName() != name)
            temp = temp->next;
        else
            break;
    }
    return temp;
}

// returns a pointer to the node specified by id, e,  if it exists
// otherwise returns a nullptr
Element* List::contains(const int e) const
{
    Element* temp = head;
    while (temp != nullptr)
        if (temp->data->getId() != e)
            temp = temp->next;
        else
            break;
    return temp;
}

// insert the element e after the node identified by name
void List::insert(string name, Element& e)
{
    Element* temp = new Element();
    temp = this->contains(name);
    
    if (temp !=nullptr)
    {
        e.next = temp->next;
        temp->next = &e;
    }
}

// insert the element e after the node identified by i
void List::insert(const int i, Element& e)
{
    Element* temp = new Element();
    temp = this->contains(i);
    
    if (temp !=nullptr)
    {
        e.next = temp->next;
        temp->next = &e;
    }
}

// return the size of the list
int List::size() const
{
    int count = 0;
    Element* temp = head;
    while (temp != nullptr)
    {
        temp = temp->next;
        count++;
    }
    return count;
}

