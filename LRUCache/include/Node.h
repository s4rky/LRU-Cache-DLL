//
//  Node.h
//  LRUCache
//  Simple custom node class to store integer k-v pairs for LRU cache
//  Created by Aaron Sarkar on 2026-07-12.
//
#pragma once

#include <iostream>

class Node
{
public:
    /**
     Custom Node constructor for LRU Cache
     */
    Node(int key, int val);
    
    Node* prev;
    Node* next;
    int val;
    int key;
};
