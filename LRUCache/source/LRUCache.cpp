//
//  LRUCache.cpp
//  LRUCache
//  LRU Cache implementation
//  Created by Aaron Sarkar on 2026-07-12.
//

#include "../include/LRUCache.h"

LRUCache::LRUCache(int capacity) : mCapacity(capacity), mCache(new DLL) {}

int LRUCache::get(int key)
{
    auto val = mAccessorMap.find(key);
    bool inMap = val != mAccessorMap.end();
    if (!inMap)
    {
        return -1;
    }
    Node* it = mAccessorMap[key];
    // update it to be MRU
    MRU(it);
    return it->val;
}

void LRUCache::put(int key, int value)
{
    auto val = mAccessorMap.find(key);
    bool inMap = val != mAccessorMap.end();
    if (!inMap)
    {
        mCache->push_front({key, value});
        mAccessorMap[key] = mCache->begin();
        if (mCapacity != 0)
        {
            mCapacity--;
        }
        else
        {
            mAccessorMap.erase(mCache->back()->key);
            mCache->pop_back();
        }
    }
    else
    {
        auto node = mAccessorMap[key];
        node->val = value;
        mCache->splice(node);
    }
}

void LRUCache::printCache()
{
    if (mCache->empty())
    {
        return;
    }
    Node* curr = mCache->begin();
    while (curr)
    {
        cout << "[" << curr->key << ":" << curr->val << "]";
        if (curr->next)
        {
            cout << " <--> ";
        }
        curr = curr->next;
    }
    cout << endl;
}

void LRUCache::MRU(Node* node)
{
    mCache->splice(node);
}

LRUCache::~LRUCache()
{
    delete mCache;
    mCache = nullptr;
}

