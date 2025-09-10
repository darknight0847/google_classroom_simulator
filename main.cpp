#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>

using namespace std;

class classroom
{
    string classid;  // class ni id store karava random ganarate thase
    string classname; // class nu name
    string teacher_email; // teacher nu email je class banavase
    vector<pair<string, string>> students; // students nu {name, email} je join karase

public:
    classroom() {}
    classroom(string cid, string cname, string temail)
    {
        classid = cid;
        classname = cname;
        teacher_email = temail;
    }

    void save()
    {
        ofstream file("classroom_data.txt", ios::app);
        file << classid << "|" << classname << "|" << teacher_email << "\n";
        file.close();
    }

    void add_student(string sname, string semail)
    {
        students.push_back({sname, semail});
        ofstream file("classroom_students.txt", ios::app);
        file << classid << "|" << sname << "|" << semail << "\n";
        file.close();
    }

    void show_students()
    {
        cout << "\n=== students in classroom " << classname << " (" << classid << ") ===\n";
        for (auto &s : students)
        {
            cout << "name: " << s.first << " | email: " << s.second << "\n";
        }
        if (students.empty())
        {
            cout << "no students yet.\n";
        }
    }

    static void show_classrooms()
    {
        ifstream file("classroom_data.txt");
        string line;
        cout << "\n=== available classrooms ===\n";
        while (getline(file, line))
        {
            stringstream ss(line);
            string cid, cname, temail;
            getline(ss, cid, '|');
            getline(ss, cname, '|');
            getline(ss, temail, '|');
            cout << "id: " << cid << " | class: " << cname << " | teacher: " << temail << "\n";
        }
        file.close();
    }

    static string generate_classid()
    {
        ifstream file("classroom_data.txt");
        int count = 1;
        string line;
        while (getline(file, line))
        {
            count++;
        }
        file.close();
        return "C" + to_string(count);
    }
};

int main()
{
    cout << "=== Google Classroom Simulator ===\n";

    while (true) {
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
        else {
            bool success = login(role);
            if (success) break; 
        }
    }

    return 0;
}
