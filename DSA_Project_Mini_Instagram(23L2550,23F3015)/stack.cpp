#include<iostream>
#include"stack.h"
using namespace std;

 NodeStack::NodeStack(string d)
 {
        data = d;
        next = nullptr;
 }


   Stack::Stack() { Top = nullptr; }

    Stack::~Stack()
    {
        while (!isEmpty())
            pop();
    }

    void Stack::push(string s)
    {
        NodeStack* n = new NodeStack(s);
        n->next = Top;
        Top = n;
    }

    string Stack::pop()
    {
        if (isEmpty())
        {
            cout << "Stack underflow\n";
            return "";
        }
        string s = Top->data;
        NodeStack* temp = Top;
        Top = Top->next;
        delete temp;
        return s;
    }

    bool Stack::isEmpty() { return Top == nullptr; }

    void Stack::display()
    {
        if (isEmpty())
        {
            cout << "Nothing to display.\n";
            return;
        }
        NodeStack* temp = Top;
        while (temp != nullptr)
        {
            cout << temp->data << endl;
            temp = temp->next;
        }
    }