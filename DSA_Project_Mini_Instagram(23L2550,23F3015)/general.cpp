#include"general.h"
#include<iostream>
#include<string>
#include <ctime> // Added for timestamp functionality (For secure time functions); This includes the C++ library that provides time and date functions. It allows us to work with time_t, tm, localtime, etc.
#include <limits> // For numeric_limits
#include <sstream> // For advanced input validation
using namespace std;

// --- Function to get current time safely ---
string currentTimestamp()
{
    time_t now = time(0);  //time(0) returns the current time as a time_t value, which is typically the number of seconds since the Unix epoch(January 1, 1970).
    //This time_t value is stored in the now variable, representing the current system time.
    char buf[80];               //A character array (buf) of size 80 is created. This buffer will be used to store the formatted time as a string.
    struct tm tstruct; //struct tm is a structure that represents a time in broken - down form(i.e., components such as year, month, day, hour, minute, second, etc.).
    //Here, tstruct is an instance of this structure that will hold the components of the current time.
    localtime_s(&tstruct, &now); // Secure version

    //This is the secure version of the localtime function.
     //   localtime converts the time_t value(now) into a tm structure(tstruct) representing the local time(taking into account the local timezone and daylight saving time).
     //   localtime_s is safer because it prevents buffer overflows by taking the address of tstruct explicitly.

    strftime(buf, sizeof(buf), "%Y-%m-%d %X", &tstruct); // Format time

            /*strftime formats the time in tstruct and stores the result as a string in buf.
        The format "%Y-%m-%d %X" specifies the date and time format:
        %Y - Full year (e.g., 2024)
        %m - Month as two digits (e.g., 11)
        %d - Day of the month (e.g., 23)
        %X - Time in the format HH:MM:SS (e.g., 15:30:00)
        sizeof(buf) ensures that the size of the buf array is correctly passed to strftime to avoid overflow.*/

    return string(buf); // Return formatted string
            /*The formatted string (buf) is converted to a std::string and returned from the function.
        This will give the current timestamp in a readable string format, like "2024-11-23 15:30:00".
        */
}

int getValidatedChoice()
{
    int choice;
    while (true)
    {
        cout << "Enter your choice: ";
        cin >> choice;

        if (cin.fail() || choice < 1 || choice > 17)
        {
            // Clear the error flag
            cin.clear();
            // Ignore the invalid input in the buffer
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter a number between 1 and 16.\n";
        }
        else
        {
            // Valid input
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear any extra characters
            return choice;
        }
    }
}

string getValidatedString(const string& prompt, const string& errorMessage)
{
    string input;
    while (true)
    {
        cout << prompt;
        getline(cin, input);

        if (input.empty())
        {
            cout << errorMessage << endl;
        }
        else
        {
            return input; // Valid input
        }
    }
}


