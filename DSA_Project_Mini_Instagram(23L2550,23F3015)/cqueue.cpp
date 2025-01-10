#include<iostream>
#include<string>
#include"cqueue.h"
using namespace std;


//-----CQueue Implementation-----

   NodeCQueue::NodeCQueue(string d)
   {
        data = d;
        next = nullptr;
   }



   CQueue::CQueue()
   {
        front = nullptr;
        rear = nullptr;
   }

    CQueue::~CQueue()
    {
        while (!isEmpty())
            dequeue();
    }

    void CQueue::enqueue(string s)
    {
        NodeCQueue* n = new NodeCQueue(s);
        if (isEmpty())
        {
            front = rear = n;
        }
        else
        {
            rear->next = n;
            rear = n;
        }
    }

    string CQueue::dequeue()
    {
        if (isEmpty())
        {
            // cout << "Queue underflow\n"; //commented out just because it doesn't seem very good to display this msg to user
            return "";
        }
        string s = front->data;
        NodeCQueue* temp = front;
        front = front->next;
        if (front == nullptr) // Reset rear if the queue is now empty
            rear = nullptr;
        delete temp;
        return s;
    }

    bool CQueue::isEmpty() { return front == nullptr; }

    void CQueue::display()
    {
        if (isEmpty())
        {
            cout << "No notifications available.\n";
            return;
        }
        NodeCQueue* temp = front;
        while (temp != nullptr)
        {
            cout << temp->data << endl;
            temp = temp->next;
        }
    }

    NodeCQueue* CQueue::getFront() const  // Getter method for the front
    {
        return front;
    }

    string CQueue::dequeueSpecific(string target)
    {
        if (isEmpty())
            return "";

        NodeCQueue* prev = nullptr;
        NodeCQueue* curr = front;

        while (curr != nullptr)
        {
            if (curr->data == target)
            {
                if (prev == nullptr)  // If target is at front
                {
                    front = curr->next;
                    if (front == nullptr) // If queue becomes empty
                        rear = nullptr;
                }
                else
                {
                    prev->next = curr->next;
                    if (curr == rear) // If target is at rear
                        rear = prev;
                }

                string data = curr->data;
                delete curr;
                return data;
            }
            prev = curr;
            curr = curr->next;
        }
        return ""; // If target not found
    }