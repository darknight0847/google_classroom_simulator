#include "classes.h"

int main()
{
    cout << "=== Google Classroom Simulator ===\n";

    while (true)
    {
        string role_choice;
        do
        {
            cout << "Who are you?\n1. Student\n2. Teacher\nChoice: ";
            getline(cin, role_choice);
            if (role_choice != "1" && role_choice != "2")
                cout << "Wrong Input!\n";
        } while (role_choice != "1" && role_choice != "2");

        string role = (role_choice == "1") ? "Student" : "Teacher";

        string auth_choice;
        do
        {
            cout << "1. Sign Up\n2. Login\nChoice: ";
            getline(cin, auth_choice);
            if (auth_choice != "1" && auth_choice != "2")
                cout << "Wrong Input!\n";
        } while (auth_choice != "1" && auth_choice != "2");

        if (auth_choice == "1")
            signup(role);
        else
        {
            login(role);
        }
    }

    return 0;
}