#include "classes.h"

void student_menu(student &s)
{
    while (true)
    {
        cout << "\n=== Student Menu ===\n";
        cout << "1. Join a Classroom\n";
        cout << "2. Submit an Assignment\n";
        cout << "3. View Assignments\n";
        cout << "4. Logout\n";
        cout << "Choice: ";
        string choice;
        getline(cin, choice);

        if (choice == "1")
        {
            classroom::show_classrooms();
            cout << "Enter classroom id to join: ";
            string cid;
            getline(cin, cid);
            classroom c(cid, "unknown", "unknown");
            c.add_student(s.getname(), s.getemail());
            cout << "Joined classroom: " << cid << "\n";
        }
        else if (choice == "2")
        {
            // Find which classrooms the student has joined
            ifstream csfile("classroom_students.txt");
            string line;
            vector<string> joined_classrooms;

            while (getline(csfile, line))
            {
                string cid, sname_line, semail;
                stringstream ss(line);
                getline(ss, cid, '|');
                getline(ss, sname_line, '|');
                getline(ss, semail, '|');
                if (semail == s.getemail())
                    joined_classrooms.push_back(cid);
            }
            csfile.close();

            if (joined_classrooms.empty())
            {
                cout << "You haven't joined any classroom yet. Join one first.\n";
                continue;
            }

            // Show assignments for classrooms the student has joined
            for (auto &cid : joined_classrooms)
                assignment::show_assignments(cid); 

            cout << "Enter Assignment ID to submit: ";
            string aid;
            getline(cin, aid);

            string found_classid = "";
            ifstream af("assignments.txt");
            while (getline(af, line))
            {
                stringstream ss(line);
                string id, title, desc, due, temail, classid;
                getline(ss, id, '|');
                getline(ss, title, '|');
                getline(ss, desc, '|');
                getline(ss, due, '|');
                getline(ss, temail, '|');
                getline(ss, classid, '|');

                if (id == aid)
                {
                    found_classid = classid;
                    break;
                }
            }
            af.close();

            if (found_classid == "")
            {
                cout << "Assignment ID not found.\n";
                continue;
            }

            // Check if student is member of the classroom
            bool joined = false;
            for (auto &cid : joined_classrooms)
            {
                if (cid == found_classid)
                {
                    joined = true;
                    break;
                }
            }

            if (!joined)
            {
                cout << "You are NOT a member of the classroom for this assignment. Join the classroom first.\n";
                continue;
            }

            // Take submission
            cout << "Enter your submission content: ";
            string content;
            getline(cin, content);

            submission sub(aid, found_classid, s.getname(), s.getemail(), content);
            sub.save();
            cout << "Submission Done for Assignment " << aid << " (Class " << found_classid << ")\n";
        }
        else if (choice == "3")
        {
            ifstream file("classroom_students.txt");
            string line;
            vector<string> joined_classrooms;

            while (getline(file, line))
            {
                string cid, sname, semail;
                stringstream ss(line);
                getline(ss, cid, '|');
                getline(ss, sname, '|');
                getline(ss, semail, '|');
                if (semail == s.getemail())
                {
                    joined_classrooms.push_back(cid);
                }
            }
            file.close();

            for (string cid : joined_classrooms)
            {
                assignment::show_assignments(cid);
            }
        }
        else if (choice == "4")
        {
            cout << "Logging out...\n";
            break;
        }
        else
        {
            cout << "Invalid choice!\n";
        }
    }
}

void teacher_menu(teacher &t)
{
    while (true)
    {
        cout << "\n=== Teacher Menu ===\n";
        cout << "1. Create a Classroom\n";
        cout << "2. Post an Assignment\n";
        cout << "3. View Submissions\n";
        cout << "4. Logout\n";
        cout << "Choice: ";
        string choice;
        getline(cin, choice);

        if (choice == "1")
        {
            cout << "Enter new classroom name: ";
            string cname;
            getline(cin, cname);
            string cid = classroom::generate_classid();
            classroom c(cid, cname, t.getemail());
            c.save();
            cout << "Classroom created with ID: " << cid << "\n";
        }
        else if (choice == "2")
        {
            cout << "Enter Classroom ID for this assignment: ";
            string cid;
            getline(cin, cid);

            cout << "Enter Assignment Title: ";
            string title;
            getline(cin, title);
            cout << "Enter Assignment Description: ";
            string desc;
            getline(cin, desc);
            cout << "Enter Due Date (e.g., 2025-09-20): ";
            string due;
            getline(cin, due);

            string aid = assignment::generate_assignment_id();
            assignment a(aid, title, desc, due, t.getemail(), cid);
            a.save();
            cout << "Assignment Posted with ID: " << aid << " for Classroom " << cid << "\n";
        }
        else if (choice == "3")
        {
            cout << "Enter Assignment ID to view submissions: ";
            string aid;
            getline(cin, aid);
            submission::show_submissions(aid);
        }
        else if (choice == "4")
        {
            cout << "Logging out...\n";
            break;
        }
        else
        {
            cout << "Invalid choice!\n";
        }
    }
}