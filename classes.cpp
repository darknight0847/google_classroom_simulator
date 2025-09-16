#include "classes.h"

// Student class implementation
student::student(string sname, string semail, string spass)
{
    setname(sname);
    setemail(semail);
    setpassword(spass);
    setrole("Student");
}

string student::getname() { return name; }
string student::getemail() { return email; }
string student::getrole() { return role; }

void student::setname(string n) { name = n; }
void student::setemail(string e) { email = e; }
void student::setpassword(string p) { password = p; }
void student::setrole(string r) { role = r; }

void student::save()
{
    ofstream file("student_data.txt", ios::app);
    file << name << "|" << email << "|" << password << "|" << role << "\n";
    file.close();
}

void student::display()
{
    cout << "\n===== " << role << " Dashboard =====\n";
    cout << "Welcome, " << name << "\n";
    cout << "Role: " << role << "\n";
    cout << "=============================\n";
}

// Teacher class implementation
teacher::teacher(string tname, string temail, string tpass)
{
    setname(tname);
    setemail(temail);
    setpassword(tpass);
    setrole("Teacher");
}

string teacher::getname() { return name; }
string teacher::getemail() { return email; }
string teacher::getrole() { return role; }

void teacher::setname(string n) { name = n; }
void teacher::setemail(string e) { email = e; }
void teacher::setpassword(string p) { password = p; }
void teacher::setrole(string r) { role = r; }

void teacher::save()
{
    ofstream file("teacher_data.txt", ios::app);
    file << name << "|" << email << "|" << password << "|" << role << "\n";
    file.close();
}

void teacher::display()
{
    cout << "\n===== " << role << " Dashboard =====\n";
    cout << "Welcome, " << name << "\n";
    cout << "Role: " << role << "\n";
    cout << "=============================\n";
}

// Classroom class implementation
classroom::classroom() {}

classroom::classroom(string cid, string cname, string temail)
{
    classid = cid;
    classname = cname;
    teacher_email = temail;
}

void classroom::save()
{
    ofstream file("classroom_data.txt", ios::app);
    file << classid << "|" << classname << "|" << teacher_email << "\n";
    file.close();
}

void classroom::add_student(string sname, string semail)
{
    students.push_back({sname, semail});
    ofstream file("classroom_students.txt", ios::app);
    file << classid << "|" << sname << "|" << semail << "\n";
    file.close();
}

void classroom::show_students()
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

void classroom::show_classrooms()
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

string classroom::generate_classid()
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

// Assignment class implementation
assignment::assignment(string aid, string atitle, string adesc, string adue, string temail, string cid)
{
    id = aid;
    title = atitle;
    description = adesc;
    due_date = adue;
    teacher_email = temail;
    class_id = cid;
}

void assignment::save()
{
    ofstream file("assignments.txt", ios::app);
    file << id << "|" << title << "|" << description << "|" << due_date << "|" << teacher_email << "|" << class_id << "\n";
    file.close();
}

void assignment::show_assignments(string cid) {
    ifstream file("assignments.txt");
    string line;
    cout << "\n=== Assignments for Classroom " << cid << " ===\n";
    while (getline(file, line)) {
        stringstream ss(line);
        string id, title, desc, due, temail, classid;
        getline(ss, id, '|');
        getline(ss, title, '|');
        getline(ss, desc, '|');
        getline(ss, due, '|');
        getline(ss, temail, '|');
        getline(ss, classid, '|');

        if (classid == cid) {
            cout << "ID: " << id << " | Title: " << title << " | Due: " << due << "\n";
            cout << "Description: " << desc << "\n\n";
        }
    }
    file.close();
}

string assignment::generate_assignment_id()
{
    ifstream file("assignments.txt");
    int count = 1;
    string line;
    while (getline(file, line))
        count++;
    file.close();
    return "A" + to_string(count);
}

// Submission class implementation
submission::submission(string aid, string cid, string sname, string semail, string scontent)
{
    assignment_id = aid;
    class_id = cid;
    student_name = sname;
    student_email = semail;
    content = scontent;
}

void submission::save()
{
    ofstream file("submissions.txt", ios::app);
    file << assignment_id << "|" << class_id << "|" << student_name << "|" << student_email << "|" << content << "\n";
    file.close();
}

void submission::show_submissions(string aid)
{
    ifstream file("submissions.txt");
    string line;
    cout << "\n=== Submissions for Assignment " << aid << " ===\n";
    while (getline(file, line))
    {
        stringstream ss(line);
        string id, classid, sname, semail, scontent;
        getline(ss, id, '|');
        getline(ss, classid, '|');
        getline(ss, sname, '|');
        getline(ss, semail, '|');
        getline(ss, scontent, '|');

        if (id == aid)
        {
            cout << "Class: " << classid << "\n";
            cout << "Student: " << sname << " (" << semail << ")\n";
            cout << "Content: " << scontent << "\n\n";
        }
    }
    file.close();
}