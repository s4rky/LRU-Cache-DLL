//
//  main.cpp
//  LRUCache
//
//  Created by Aaron Sarkar on 2026-07-12.
//

#include <iostream>
#include <utility>
#include <unordered_map>
#include <iterator>

using namespace std;


/**
 Node Implementation for LRU Cache
 */
class Node
{
public:
    // constructor for LRU cache
    Node(int key, int val) : key(key), val(val), prev(nullptr), next(nullptr) {};
    
    Node* prev;
    Node* next;
    int val;
    int key;
};

/**
 Doubly Linked List Implementation for LRU Cache
 */
class DLL
{
public:
    // default constructor
    DLL() : mHead(nullptr), mTail(nullptr), mLength(0) {};
    
    // push_front [void]
    void push_front(const pair<int,int>& kv)
    {
        Node* newNode = new Node(kv.first, kv.second);
        if (mLength == 0)
        {
            mHead = newNode;
            mTail = newNode;
        }
        else
        {
            newNode->next = mHead;
            mHead->prev = newNode;
            mHead = newNode;
        }
        mLength++;
    }
    
    // pop_back [void]
    void pop_back()
    {
        if (mLength == 0)
        {
            return;
        }
        Node* temp = mTail;
        if (mLength == 1)
        {
            mTail = nullptr;
            mHead = nullptr;
            delete temp;
            mLength--;
            return;
        }
        mTail = mTail->prev;
        mTail->next = nullptr;
        temp->prev = nullptr;
        delete temp;
        mLength--;
    }
    
    // begin [iterator pointing to beginning of list]
    Node* begin()
    {
        if (!mHead)
        {
            return nullptr;
        }
        return mHead;
        
    }
    
    // back [iterator pointing to back of list]
    Node* back()
    {
        if (!mHead)
        {
            return nullptr;
        }
        return mTail;
    }
    
    // custom splice to always swap with head
    void splice(Node* toSwap)
    {
        // if length is 0 or
        // if the value to splice is actually the same as head, we dont need to do repositioning
        if (mLength == 0 || mLength == 1 || toSwap == mHead)
        {
            return;
        }
        
        Node* prevNode = toSwap->prev;
        // if value is tail, simply pop off and make it to the new head
        if (toSwap == mTail)
        {
            prevNode->next = nullptr;
            toSwap->prev = nullptr;
            mTail = prevNode;
            toSwap->next = mHead;
            mHead->prev = toSwap;
            mHead = toSwap;
            return;
        }
        // swap with a node anywhere in middle and head
        Node* nextNode = toSwap->next;
        toSwap->next = mHead;
        // severance
        nextNode->prev = prevNode;
        prevNode->next = nextNode;
        toSwap->prev = nullptr;
        mHead->prev = toSwap;
        mHead = mHead->prev;
    }
    
    bool empty()
    {
        return (mLength == 0);
    }
    
    // destructor
    ~DLL()
    {
        Node* temp = mHead;
        while(mHead)
        {
            mHead = mHead->next;
            delete temp;
            temp = mHead;
        }
    }
    
private:
    int mLength;
    Node* mHead;
    Node* mTail;
    
};

class LRUCache
{
public:
    //constructor
    LRUCache(int capacity) : mCapacity(capacity), mCache(new DLL) {}
    
    ~LRUCache()
    {
        delete mCache;
        mCache = nullptr;
    }
    
    //get
    int get(int key)
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
    
    //put
    void put(int key, int value)
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
    
    //print cache
    void printCache()
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
    

private:
    
    // MRU private helper
    void MRU(Node* node)
    {
        mCache->splice(node);
    }
    int mCapacity;
    unordered_map<int, Node*> mAccessorMap;
    DLL* mCache;
    
};

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

