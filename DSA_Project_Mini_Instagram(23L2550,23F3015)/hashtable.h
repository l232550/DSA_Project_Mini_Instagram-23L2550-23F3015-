#pragma once
#include<iostream>
#include<string>
using namespace std;

//hash table using Chaining:
// UserNode Struct
struct UserNode 
{
    string username;
    string password;
    UserNode* next;

    UserNode(string, string);
};

// UserHashTable Class
class UserHashTable
{
private:
    UserNode** table; // Array of pointers to UserNode (for chaining)
    //Each slot in the array points to the head of a linked list(chain).This is how we implement separate OR open chaining.
    int size;         // Number of buckets
    int hash(string);

public:
    UserHashTable(int );
    ~UserHashTable();
    bool insertUser(string, string);
    bool verifyUser(string, string);
    bool removeUser(string );
    void printUsers();
};