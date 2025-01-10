#include<iostream>
#include<string>
#include"linkedlist.h"
using namespace std;

    Node::Node(string username, string pwd, string userCity)
    {
        name = username;
        password = pwd;
        city = userCity;
        lastLogin = "2024-11-23 12:00:00"; // Placeholder for current timestamp
        friends = nullptr;
        followers = nullptr; // Initialize followers list
        next = nullptr;
    }


    LinkedList::LinkedList() { head = nullptr; }

    Node*LinkedList:: findUser(string username)
    {
        Node* temp = head;
        while (temp != nullptr)
        {
            if (temp->name == username)
                return temp;
            temp = temp->next;
        }
        return nullptr;
    }

    void LinkedList::addUser(string username, string password, string city)
    {
        if (findUser(username))
        {
            cout << "Username already exists.\n";
            return;
        }
        Node* newUser = new Node(username, password, city);
        newUser->next = head;
        head = newUser;
        cout << "User added successfully.\n";
    }

    void LinkedList::displayUsers()
    {
        if (!head)
        {
            cout << "No users available.\n";
            return;
        }
        Node* temp = head;
        while (temp)
        {
            cout << "Name: " << temp->name << ", City: " << temp->city << endl;
            temp = temp->next;
        }
    }



