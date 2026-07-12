//
//  DLL.cpp
//  LRUCache
//  Doubly Linked List Implementation
//  Created by Aaron Sarkar on 2026-07-12.
//

#include "../include/DLL.h"

DLL::DLL() : mHead(nullptr), mTail(nullptr), mLength(0) {};

void DLL::push_front(const pair<int,int>& kv)
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

void DLL::pop_back()
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

Node* DLL::begin()
{
    if (!mHead)
    {
        return nullptr;
    }
    return mHead;
    
}

Node* DLL::back()
{
    if (!mHead)
    {
        return nullptr;
    }
    return mTail;
}

void DLL::splice(Node* toSwap)
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

bool DLL::empty() const
{
    return mLength == 0;
}

DLL::~DLL()
{
    Node* temp = mHead;
    while (mHead)
    {
        mHead = mHead->next;
        delete temp;
        temp = mHead;
    }
}

