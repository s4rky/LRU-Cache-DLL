//
//  LRUCache.h
//  LRUCache
//  Main LRU Cache class that leverages DLL and Node
//  Created by Aaron Sarkar on 2026-07-12.
//
#pragma once

#include <iostream>
#include <utility>
#include <unordered_map>
#include "Node.h"
#include "DLL.h"

using namespace std;


class LRUCache
{
public:
    /**
     Constructor that is initialized with a set capacity and initializes a new instance of a DLL
     */
    LRUCache(int capacity);
    
    // Destructor
    ~LRUCache();
    
    
    /**
     Get method for LRU
     If key does not exist in the map, return early -1
     if key exists in the map, simply return the value from DLL. Getting a key also updates it to becoming the MRU
     */
    int get(int key);
    
    /**
     Put method for LRU
     Rules:
     1. If the cache is not full, simply push to the front of the DLL and update map
     2. If the cache is full, evict the LRU K-V (tail) and remove from the map. Then proceed to add to the front of the DLL (MRU) and add to map
     3. If the cache has the value already and is being updated, update the value and run a splice to rearrange
     */
    void put(int key, int value);
    
    /**
     Print  method to visualize the cache on console
     */
    void printCache();
    

private:
    /**
     MRU Private helper that uses splice from DLL. This helps abstracts away the splice method and explicitly states why the rearranging is happening
     */
    void MRU(Node* node);
    int mCapacity;
    unordered_map<int, Node*> mAccessorMap;
    DLL* mCache;
    
};

