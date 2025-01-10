#pragma once
#include<iostream>
#include<string>
using namespace std;


class NodeCQueue
{
public:
    string data;
    NodeCQueue* next;

    NodeCQueue(string);
};

class CQueue
{
    NodeCQueue* front;
    NodeCQueue* rear;

public:
    CQueue();
    ~CQueue();
    void enqueue(string );
    string dequeue();
    bool isEmpty();
    void display();
    NodeCQueue* getFront() const;  // Getter method for the front
    string dequeueSpecific(string );
    
};

