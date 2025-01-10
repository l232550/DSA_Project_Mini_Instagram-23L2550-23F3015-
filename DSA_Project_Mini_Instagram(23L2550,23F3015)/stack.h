#pragma once
#include<iostream>
#include<string>
using namespace std;

class NodeStack
{
public:
    string data;
    NodeStack* next;
    NodeStack(string );
};

class Stack
{
    NodeStack* Top;

public:
    Stack();
    ~Stack();
    void push(string );
    string pop();
    bool isEmpty();
    void display();
};