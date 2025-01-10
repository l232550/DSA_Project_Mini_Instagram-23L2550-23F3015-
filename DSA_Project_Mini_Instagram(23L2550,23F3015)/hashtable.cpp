#include<iostream>
#include<string>
#include"hashtable.h"
using namespace std;


//hash table implementation using Chaining:
// UserNode Struct
    UserNode::UserNode(string uname, string pword) : username(uname), password(pword), next(nullptr) {}

// UserHashTable Class

    int UserHashTable::hash(string key)
    {
        int hashValue = 0;
        for (char ch : key)
        {
            hashValue = (hashValue * 31 + ch) % size; // Hash function based on ASCII values
        }
        return hashValue;
    }

    UserHashTable::UserHashTable(int size) : size(size)
    {
        table = new UserNode * [size];
        for (int i = 0; i < size; i++)
        {
            table[i] = nullptr;
        }
    }

    UserHashTable::~UserHashTable()
    {
        for (int i = 0; i < size; i++)
        {
            UserNode* current = table[i];
            while (current != nullptr)
            {
                UserNode* temp = current;
                current = current->next;
                delete temp;
            }
        }
        delete[] table;
    }

   
    bool UserHashTable::insertUser(string username, string password)
    {
        int index = hash(username);
        UserNode* current = table[index];

        // Check if username already exists
        while (current != nullptr)
        {
            if (current->username == username)
            {
                return false; // Username already exists
            }
            current = current->next;
        }

        // Insert at the head of the chain
        UserNode* newNode = new UserNode(username, password);
        newNode->next = table[index];
        table[index] = newNode;
        return true;
    }

    // Verify login
    bool UserHashTable::verifyUser(string username, string password)
    {
        int index = hash(username);
        UserNode* current = table[index];

        // Traverse the chain
        while (current != nullptr)
        {
            if (current->username == username && current->password == password)
            {
                return true; // Login successful
            }
            current = current->next;
        }
        return false; // Login failed
    }

   
    bool UserHashTable::removeUser(string username)
    {
        int index = hash(username);
        UserNode* current = table[index];
        UserNode* previous = nullptr;

        // Traverse the chain
        while (current != nullptr)
        {
            if (current->username == username)
            {
                // Remove the node
                if (previous == nullptr)
                {
                    table[index] = current->next;
                }
                else
                {
                    previous->next = current->next;
                }
                delete current;
                return true;
            }
            previous = current;
            current = current->next;
        }
        return false; // Username not found
    }

    void UserHashTable::printUsers()
    {
        for (int i = 0; i < size; i++)
        {
            cout << "Bucket " << i << ": ";
            UserNode* current = table[i];
            while (current != nullptr)
            {
                cout << "[" << current->username << ", " << current->password << "] -> ";
                current = current->next;
            }
            cout << "nullptr\n";
        }
    }