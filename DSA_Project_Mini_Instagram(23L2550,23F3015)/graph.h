#pragma once
#include <iostream>
#include <string>
#include "linkedlist.h"
#include "hashtable.h"

using namespace std;

const int MAX_USERS = 100; // Maximum number of users

// Declare global variables as extern //normally we declare global vars by declaring them outside main(),but for header files,we write extern
extern string existingPasswords[MAX_USERS];
extern int userCount;
extern UserHashTable userTable; // Declare without initialization


// --- Graph  (for Managing Friendships/Followers) --- 
class Graph 
{
private:
    LinkedList users;
    LinkedList blockedUsers;
public:
    int validatePassword(string password);
    void signup(string username, string password, string city);
    Node* login(string username, string password);
    void addFriend(Node* user, string friendName);
    void acceptFriendRequest(Node* user, string friendName);
    void sendMessage(Node* sender, string recipientName, string message);
    void viewMessages(Node* user);
    void viewUsers();
    void searchUser(string username);
    void viewFriendsPosts(Node* user);
    void viewFollowers(Node* user);
};
