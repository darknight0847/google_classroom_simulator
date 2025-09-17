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
            // Check if any classrooms exist
            ifstream file("classroom_data.txt");
            vector<pair<string, string>> class_teacher_list;
            string line;
            while (getline(file, line)) {
                stringstream ss(line);
                string cid, cname, temail;
                getline(ss, cid, '|');
                getline(ss, cname, '|');
                getline(ss, temail, '|');
                if (!cid.empty())
                    class_teacher_list.push_back({cid, temail});
            }
            file.close();
            if (class_teacher_list.empty()) {
                cout << "No classrooms available to join.\n";
                continue;
            }
            classroom::show_classrooms();
            cout << "Enter classroom id to join: ";
            string cid;
            getline(cin, cid);
            // Find teacher name for this class
            string teacher_email = "";
            for (auto &ct : class_teacher_list) {
                if (ct.first == cid) {
                    teacher_email = ct.second;
                    break;
                }
            }
            if (teacher_email == "") {
                cout << "Classroom ID not found.\n";
                continue;
            }
            classroom c(cid, "unknown", teacher_email);
            c.add_student(s.getname(), s.getemail());
            show_classroom(c);
            cout << "Joined classroom: " << cid << " | Teacher: " << teacher_email << "\n";
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
            show_submission(sub);
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

            // Show student's submissions with grade and feedback
            ifstream subfile("submissions.txt");
            cout << "\n=== Your Submissions, Grades, and Feedback ===\n";
            while (getline(subfile, line)) {
                stringstream ss(line);
                string aid, classid, sname, semail, content, grade, feedback;
                getline(ss, aid, '|');
                getline(ss, classid, '|');
                getline(ss, sname, '|');
                getline(ss, semail, '|');
                getline(ss, content, '|');
                getline(ss, grade, '|');
                getline(ss, feedback, '|');
                if (semail == s.getemail()) {
                    cout << "Assignment: " << aid << " | Class: " << classid << "\n";
                    cout << "Content: " << content << "\n";
                    cout << "Grade: " << grade << "\n";
                    cout << "Feedback: " << feedback << "\n\n";
                }
            }
            subfile.close();
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
    cout << "4. Assign Grade and Feedback\n";
    cout << "5. Logout\n";
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
            show_assignment(a);
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
            cout << "Enter Assignment ID: ";
            string aid;
            getline(cin, aid);
            cout << "Enter Student Email: ";
            string semail;
            getline(cin, semail);
            // Check if submission exists
            bool found = false;
            ifstream file("submissions.txt");
            string line;
            while (getline(file, line)) {
                stringstream ss(line);
                string id, classid, sname, email, content, old_grade, old_feedback;
                getline(ss, id, '|');
                getline(ss, classid, '|');
                getline(ss, sname, '|');
                getline(ss, email, '|');
                getline(ss, content, '|');
                getline(ss, old_grade, '|');
                getline(ss, old_feedback, '|');
                if (id == aid && email == semail) {
                    found = true;
                    break;
                }
            }
            file.close();
            if (!found) {
                cout << "This student has not submitted this assignment. Cannot assign grade or feedback.\n";
                continue;
            }
            cout << "Enter Grade: ";
            string grade;
            getline(cin, grade);
            cout << "Enter Feedback: ";
            string feedback;
            getline(cin, feedback);
            submission::assign_grade_and_feedback(aid, semail, grade, feedback);
            cout << "Grade and feedback assigned.\n";
        }
        else if (choice == "5")
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