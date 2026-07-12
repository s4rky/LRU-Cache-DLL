//
//  Node.cpp
//  LRUCache
//  Node Implementation
//  Created by Aaron Sarkar on 2026-07-12.
//

#include "../include/Node.h"

Node::Node(int key, int val) : key(key), val(val), prev(nullptr), next(nullptr) {};
