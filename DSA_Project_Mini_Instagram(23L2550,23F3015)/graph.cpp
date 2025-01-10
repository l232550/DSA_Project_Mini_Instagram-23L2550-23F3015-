#include "graph.h"
#include "hashtable.h"
#include "linkedlist.h"
#include "general.h"
#include <iostream>
#include <string>

using namespace std;

// Define the global variables here
string existingPasswords[MAX_USERS];
int userCount = 0;
UserHashTable userTable(100);

// --- Graph Implementaion (for Managing Friendships/Followers) --- 
int Graph::validatePassword(string password) 
{
    // Check for special characters
    int hasSpecialChar = 0;
    for (char c : password) 
    {
        if (!isalnum(c)) //alp-> alphabets, num->numbers 
        { // Check if the character is not alphanumeric
            hasSpecialChar = 1;
            break;
        }
    }

    if (!hasSpecialChar) 
    {
        return 0;
    }

    return 1; // Valid password
}

void Graph::signup(string username, string password, string city) 
{
    // Validate the password
    int passwordValidity = validatePassword(password);
    if (passwordValidity != 1) 
    {
        cout << "Signup failed! Please try with a stronger password (at least one special character must be used).\n";
        return; // Stop further processing if password is invalid
    }

    // Check if the password is already used by another user
    Node* temp = users.head;
    while (temp != nullptr) 
    {
        if (temp->password == password) 
        {
            cout << "Password already in use by another user. Please choose a different password.\n";
            return;
        }
        temp = temp->next;
    }

    // Check if the username is unique and insert into the hash table
    if (!userTable.insertUser(username, password)) 
    {
        cout << "Username already exists. Please try a different username.\n";
        return; // Exit early if the username is already in use
    }

    // Ensure the username isn't already in the linked list (extra safety)
    if (users.findUser(username) != nullptr) 
    {
        cout << "Username already exists in the linked list. Please try a different username.\n";
        userTable.removeUser(username); // Remove from hash table to maintain consistency
        return;
    }

    // Add the user to the linked list and confirm success
    users.addUser(username, password, city);
    cout << "Signup successful!\n";
}

Node* Graph::login(string username, string password) 
{
    Node* user = users.findUser(username);
    if (user && user->password == password) 
    {
        user->lastLogin = currentTimestamp(); // Record login time
        cout << "Login successful! Last login: " << user->lastLogin << endl;
        return user;
    }
    return nullptr;
}

void Graph::addFriend(Node* user, string friendName) 
{
    Node* friendUser = users.findUser(friendName);
    if (!friendUser) 
    {
        cout << "User " << friendName << " not found.\n";
        return;
    }
    friendUser->notifications.enqueue(user->name + " sent you a friend request.");
    cout << "Friend request sent to " << friendName << ".\n";
}

void Graph::acceptFriendRequest(Node* user, string friendName)
{
    string targetRequest = friendName + " sent you a friend request.";
    string removedRequest = user->notifications.dequeueSpecific(targetRequest);

    if (removedRequest != "") 
    {
        // Add friend and follower relationships
        Node* friendUser = users.findUser(friendName);

        if (friendUser) 
        {
            Node* newFriend = new Node(friendName, "", "");
            newFriend->next = user->friends;
            user->friends = newFriend;

            Node* newFollower = new Node(user->name, "", "");
            newFollower->next = friendUser->followers;
            friendUser->followers = newFollower;

            cout << "Friend request from " << friendName << " accepted.\n";
        }
    }
    else 
    {
        cout << "No friend request from " << friendName << " found.\n";
    }
}

void Graph::sendMessage(Node* sender, string recipientName, string message) 
{
    
    Node* recipient = users.findUser(recipientName);
    if (!recipient) 
    {
        cout << "User " << recipientName << " not found.\n";
        return;
    }

    sender->messages.push("To " + recipientName + ": " + message); // Add message to sender's stack
    if (!blockedUsers.findUser(sender->name))
    {
        recipient->messages.push("From " + sender->name + ": " + message); // Add message to recipient's stack
    }

    recipient->notifications.enqueue("New message from " + sender->name + ". ");
    cout << "Message sent to " << recipientName << ".\n";
}


void Graph::viewMessages(Node* user) 
{
    cout << "Your messages:\n";
    user->messages.display();
    if (!user->messages.isEmpty()) 
    {
        user->messages.pop();
        user->notifications.dequeue();  // Remove the friend request from notifications
    }
}

void Graph::viewUsers() 
{
    users.displayUsers();
}

void Graph::searchUser(string username) 
{
    if (users.findUser(username))
        cout << "User " << username << " found!\n";
    else
        cout << "User " << username << " not found.\n";
}

void Graph::viewFriendsPosts(Node* user) 
{
    if (!user->friends) 
    {
        cout << "You have no friends to view posts from.\n";
        return;
    }

    cout << "Posts from your friends:\n";
    Node* temp = user->friends;
    while (temp != nullptr) 
    {
        Node* friendUser = users.findUser(temp->name);
        if (friendUser) 
        {
            cout << "Posts from " << friendUser->name << ":\n";
            friendUser->posts.display();
        }
        temp = temp->next;
    }
}

void Graph::viewFollowers(Node* user)
{
    if (!user->followers) 
    {
        cout << "You have no followers.\n";
        return;
    }

    cout << "Your followers:\n";
    Node* temp = user->followers;
    while (temp != nullptr) 
    {
        cout << temp->name << endl;
        temp = temp->next;
    }
}


