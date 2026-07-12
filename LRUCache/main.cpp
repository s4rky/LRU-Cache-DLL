//
//  main.cpp
//  LRUCache
//  Driver Code for LRU cache
//  Created by Aaron Sarkar on 2026-07-12.
//

#include <iostream>
#include "include/LRUCache.h"

using namespace std;

int main(int argc, const char * argv[])
{
    LRUCache* cache = new LRUCache(4);
    cache->put(2, 6);
    cache->put(1, 5);
    cache->put(4, 23);
    cache->put(9, 9);
    cache->printCache();
    cache->put(90, 90);
    cache->printCache();

    return EXIT_SUCCESS;
}

