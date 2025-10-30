#include "classes.h"
#include <exception>

void student_menu(student &s)
{
    while (true)
    {
        try {
        cout << "\n=== Student Menu ===\n";
        cout << "1. Join a Classroom\n";
        cout << "2. Submit an Assignment\n";
        cout << "3. View Assignments\n";
        cout << "4. View Announcements\n";
        cout << "5. Comment on Announcement\n";
        cout << "6. Logout\n";
        cout << "Choice: ";
        string choice;
        getline(cin, choice);

        if (choice == "1")
        {
            // ...existing code...
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
            // ...existing code for assignment submission...
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
            // ...existing code for viewing assignments and submissions...
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
            // View Announcements for joined classrooms
            ifstream file("classroom_students.txt");
            string line;
            vector<string> joined_classrooms;
            while (getline(file, line)) {
                string cid, sname, semail;
                stringstream ss(line);
                getline(ss, cid, '|');
                getline(ss, sname, '|');
                getline(ss, semail, '|');
                if (semail == s.getemail())
                    joined_classrooms.push_back(cid);
            }
            file.close();
            if (joined_classrooms.empty()) {
                cout << "You haven't joined any classroom yet. Join one first.\n";
                continue;
            }
            for (string cid : joined_classrooms) {
                announcement::show_announcements(cid);
            }
        }
        else if (choice == "5")
        {
            // Comment on Announcement
            ifstream file("classroom_students.txt");
            string line;
            vector<string> joined_classrooms;
            while (getline(file, line)) {
                string cid, sname, semail;
                stringstream ss(line);
                getline(ss, cid, '|');
                getline(ss, sname, '|');
                getline(ss, semail, '|');
                if (semail == s.getemail())
                    joined_classrooms.push_back(cid);
            }
            file.close();
            if (joined_classrooms.empty()) {
                cout << "You haven't joined any classroom yet. Join one first.\n";
                continue;
            }
            cout << "Enter Classroom ID to view announcements: ";
            string cid;
            getline(cin, cid);
            bool joined = false;
            for (auto &jc : joined_classrooms) {
                if (jc == cid) { joined = true; break; }
            }
            if (!joined) {
                cout << "You are not a member of this classroom.\n";
                continue;
            }
            announcement::show_announcements(cid);
            cout << "Enter Announcement ID to comment on: ";
            string aid;
            getline(cin, aid);
            // Verify announcement exists and belongs to the classroom
            bool valid_announcement = false;
            ifstream afile("announcements.txt");
            string aline;
            while (getline(afile, aline)) {
                stringstream ss(aline);
                string a_id, a_title, a_content, a_temail, a_cid, a_date;
                getline(ss, a_id, '|');
                getline(ss, a_title, '|');
                getline(ss, a_content, '|');
                getline(ss, a_temail, '|');
                getline(ss, a_cid, '|');
                getline(ss, a_date, '|');
                if (a_id == aid && a_cid == cid) {
                    valid_announcement = true;
                    break;
                }
            }
            afile.close();
            if (!valid_announcement) {
                cout << "Invalid Announcement ID for this classroom.\n";
                continue;
            }
            cout << "Enter your comment: ";
            string comment;
            getline(cin, comment);
            // Save comment to file with correct announcement ID
            ofstream cfile("announcement_comments.txt", ios::app);
            cfile << aid << "|" << s.getemail() << "|" << comment << "\n";
            cfile.close();
            cout << "Comment added. Only the teacher can view your comment.\n";
        }
        else if (choice == "6")
        {
            cout << "Logging out...\n";
            break;
        }
        else
        {
            cout << "Invalid choice!\n";
        }
        }
        catch (const exception &e) {
            cerr << "An error occurred in student menu: " << e.what() << "\n";
        }
    }
}

void teacher_menu(teacher &t)
{
    while (true)
    {
        try {
        cout << "\n=== Teacher Menu ===\n";
        cout << "1. Create a Classroom\n";
        cout << "2. Post an Assignment\n";
        cout << "3. View Submissions\n";
        cout << "4. Assign Grade and Feedback\n";
        cout << "5. Make Announcement\n";
        cout << "6. View Announcement Comments\n";
        cout << "7. Logout\n";
        cout << "Choice: ";
        string choice;
        getline(cin, choice);

        if (choice == "1")
        {
            // ...existing code for classroom creation...
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
            // ...existing code for posting assignment...
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
            // ...existing code for viewing submissions...
            cout << "Enter Assignment ID to view submissions: ";
            string aid;
            getline(cin, aid);
            submission::show_submissions(aid);
        }
        else if (choice == "4")
        {
            // ...existing code for assigning grade and feedback...
            cout << "Enter Assignment ID: ";
            string aid;
            getline(cin, aid);
            cout << "Enter Student Email: ";
            string semail;
            getline(cin, semail);
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
            // Make Announcement
            cout << "Enter Classroom ID to make announcement: ";
            string cid;
            getline(cin, cid);
            // Check if teacher owns this classroom
            bool owns = false;
            ifstream file("classroom_data.txt");
            string line;
            while (getline(file, line)) {
                stringstream ss(line);
                string classid, cname, temail;
                getline(ss, classid, '|');
                getline(ss, cname, '|');
                getline(ss, temail, '|');
                if (classid == cid && temail == t.getemail()) {
                    owns = true;
                    break;
                }
            }
            file.close();
            if (!owns) {
                cout << "You do not own this classroom.\n";
                continue;
            }
            cout << "Enter Announcement Title: ";
            string title;
            getline(cin, title);
            cout << "Enter Announcement Content: ";
            string content;
            getline(cin, content);
            string aid = announcement::generate_announcement_id();
            announcement a(aid, title, content, t.getemail(), cid);
            a.save();
            show_announcement(a);
            cout << "Announcement posted for Classroom " << cid << " with ID: " << aid << "\n";
        }
        else if (choice == "6")
        {
            // View Announcement Comments
            cout << "Enter Classroom ID to view your announcements: ";
            string cid;
            getline(cin, cid);
            // Show all announcements for this classroom by this teacher
            ifstream afile("announcements.txt");
            string line;
            vector<string> aids;
            while (getline(afile, line)) {
                stringstream ss(line);
                string aid, title, content, temail, classid, date;
                getline(ss, aid, '|');
                getline(ss, title, '|');
                getline(ss, content, '|');
                getline(ss, temail, '|');
                getline(ss, classid, '|');
                getline(ss, date, '|');
                if (classid == cid && temail == t.getemail()) {
                    cout << "Announcement ID: " << aid << " | Title: " << title << "\n";
                    aids.push_back(aid);
                }
            }
            afile.close();
            if (aids.empty()) {
                cout << "No announcements found for this classroom.\n";
                continue;
            }
            cout << "Enter Announcement ID to view comments: ";
            string aid;
            getline(cin, aid);
            bool valid = false;
            for (auto &a : aids) if (a == aid) valid = true;
            if (!valid) {
                cout << "Invalid Announcement ID.\n";
                continue;
            }
            // Show comments for this announcement
            announcement::show_announcement_comments(aid);
        }
        else if (choice == "7")
        {
            cout << "Logging out...\n";
            break;
        }
        else
        {
            cout << "Invalid choice!\n";
        }
        }
        catch (const exception &e) {
            cerr << "An error occurred in teacher menu: " << e.what() << "\n";
        }
    }
}
