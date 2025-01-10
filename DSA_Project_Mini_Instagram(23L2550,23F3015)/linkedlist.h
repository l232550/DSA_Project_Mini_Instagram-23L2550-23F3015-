#pragma once
#include<iostream>
#include<string>
#include"stack.h"
#include"cqueue.h"
using namespace std;

// --- Linked List (for Managing Users) --- 
class Node
{
public:
    string name;
    string password;
    string city;
    Stack posts;        // Custom stack for storing posts
    Stack messages;     // Custom stack for storing messages
    Node* friends; // Linked list for friends
    Node* followers; // Linked list for followers
    CQueue notifications; // Custom queue for notifications
    string lastLogin;
    Node* next;

    Node(string, string, string );
    
};

class LinkedList
{
 public:
    Node* head;

    LinkedList();
    Node* findUser(string);
    void addUser(string, string, string);
    void displayUsers();

};

