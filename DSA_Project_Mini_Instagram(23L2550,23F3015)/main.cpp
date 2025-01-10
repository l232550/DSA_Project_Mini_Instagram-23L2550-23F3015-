#include <iostream>
 
#include"cqueue.h"  //all header files
#include"hashtable.h"
#include"graph.h"
#include"stack.h"
#include"linkedlist.h"
#include"general.h"

#include <string>
#include <ctime> // Added for timestamp functionality (For secure time functions); This includes the C++ library that provides time and date functions. It allows us to work with time_t, tm, localtime, etc.
#include <limits> // For numeric_limits
#include <sstream> // For advanced input validation
using namespace std;



int main()
{

    Graph insta;
    Node* currentUser = nullptr;

    int choice = 0;
    string username, password, city, friendName, messageContent;

    while (true)
    {
        cout << "\n--- Mini Instagram Menu ---\n";
        cout << "1. Signup\n2. Login\n3. Add Post\n4. View NewsFeed\n5. Add Friend\n6. Accept Friend Request\n7. Send Message\n8. View Messages\n9. View All Users\n10. Search User\n11. View Followers List\n12. View Notifications\n13. View Friends' Posts\n14. Logout\n15. Exit\n16. Credits\n";

        choice = getValidatedChoice();

        switch (choice)
        {
        case 1:
        { // Signup
            string username = getValidatedString("Enter username: ", "Username cannot be empty.");
            string password = getValidatedString("Enter password: ", "Password cannot be empty.");
            string city = getValidatedString("Enter city: ", "City cannot be empty.");

            // Let the signup function handle all logic
            insta.signup(username, password, city);
            break;
        }

        case 2:
        { // Login
            if (currentUser)
            {
                cout << "Already logged in as " << currentUser->name << ". Logout first.\n";
                break;
            }

            string username = getValidatedString("Enter username: ", "Username cannot be empty.");
            string password = getValidatedString("Enter password: ", "Password cannot be empty.");

            if (userTable.verifyUser(username, password))
            {
                currentUser = insta.login(username, password);
            }
            else
            {
                cout << "Invalid username or password.\n";
            }
            break;
        }

        case 3: // Add Post
            if (!currentUser)
            {
                cout << "You need to login first.\n";
                break;
            }
            {
                string postContent = getValidatedString("Enter post content: ", "Post content cannot be empty.");
                currentUser->posts.push(postContent);
                cout << "Post added successfully.\n";
            }
            break;

        case 4: // View Posts
            if (!currentUser)
            {
                cout << "You need to login first.\n";
                break;
            }
            currentUser->posts.display();
            break;

        case 5: // Add Friend
            if (!currentUser)
            {
                cout << "You need to login first.\n";
                break;
            }
            cout << "Enter friend's username: ";
            cin >> friendName;
            insta.addFriend(currentUser, friendName);
            break;

        case 6: // Accept Friend Request
            if (!currentUser)
            {
                cout << "You need to login first.\n";
                break;
            }
            cout << "Enter friend's username to accept request: ";
            cin >> friendName;
            insta.acceptFriendRequest(currentUser, friendName);
            break;


        case 7: // Send Message
            if (!currentUser)
            {
                cout << "You need to login first.\n";
                break;
            }
            cout << "Enter recipient's username: ";
            cin >> friendName;

            cout << "Enter message: ";
            cin.ignore();
            getline(cin, messageContent);
            insta.sendMessage(currentUser, friendName, messageContent);
            break;

        case 8: // View Messages
            if (!currentUser)
            {
                cout << "You need to login first.\n";
                break;
            }
            insta.viewMessages(currentUser);
            break;

        case 9: // View All Users
            insta.viewUsers();
            break;

        case 10: // Search User
            cout << "Enter username to search: ";
            cin >> username;
            insta.searchUser(username);
            break;

        case 11: //View Followers List
            if (!currentUser)
            {
                cout << "You need to login first.\n";
                break;
            }
            insta.viewFollowers(currentUser);
            break;


        case 12: //View Notifications
            if (!currentUser)
            {
                cout << "You need to login first.\n";
                break;
            }
            currentUser->notifications.display();
            break;

        case 13: //View Friends Post
            if (!currentUser)
            {
                cout << "You need to login first.\n";
                break;
            }
            insta.viewFriendsPosts(currentUser);
            break;

        case 14: // Logout
            if (!currentUser)
            {
                cout << "You are not logged in.\n";
                break;
            }
            cout << "Logged out successfully.\n";
            currentUser = nullptr;
            break;

        case 15: // Exit
            cout << "Exiting program...\n";
            return 0;

        case 16: //Program credits
            cout << "\nMini Instagram Credits: \n> Tooba Nadeem\t23L-2550\n> Nayab Maryam\t23F-3015\n";
            break;

        default:
            cout << "Invalid choice. Please try again.\n";
        }
    }

    return 0;
}
