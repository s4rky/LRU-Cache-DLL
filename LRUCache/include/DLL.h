//
//  DLL.h
//  LRUCache
//  Custom build Doubly Linked List class to serve as the storage for LRU Cache. This class shares method names (and is heavily inspired by) with the STL container std::list
//  Created by Aaron Sarkar on 2026-07-12.
//
#pragma once

#include <iostream>
#include <utility>
#include "Node.h"

using namespace std;

class DLL
{

public:
    /**
     Constructor (defaults as an empty container)
     */
    DLL();
    
    // destructor
    ~DLL();
    
    /**
     Method to push to the front of the DLL. The front(head) will always be the MRU while the back(tail) will be the LRU
     */
    void push_front(const pair<int,int>& kv);
    
    /**
     Method to pop from back of the DLL. The front(head) will always be the MRU while the back(tail) will be the LRU
     */
    void pop_back();
    
    /**
     Method to return a  pointer to the head of the DLL
     */
    Node* begin();
    
    /**
     Method to return a  pointer to the tail of the DLL
     */
    Node* back();
    
    /**
     Splice Method to rearrange the DLL using a Node pointer parameter.
     Rules:
     1. When length is 0 or 1 OR the Node toSwap is the head nothing needs to be rearranged
     2. When the Node toSwap is the tail, a simple update to tail and head is required
     3. When the Node toSwap is a non-head/non-tail node, in-place rechaining is required with the use of prevNode and nextNode
     */
    void splice(Node* toSwap);
    
    /**
     Returns true if DLL is empty
     */
    bool empty() const;
    
private:
    int mLength;
    Node* mHead;
    Node* mTail;
    
};
