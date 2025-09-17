#ifndef CLASSES_H
#define CLASSES_H

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>

using namespace std;

class student
{
    string* name;
    string* email;
    string* password;
    string* role;

public:
    student(string sname = "Unknown", string semail = "unknown@gmail.com", string spass = "password");
    ~student();

    string getname();
    string getemail();
    string getrole();

    void setname(string n);
    void setemail(string e);
    void setpassword(string p);
    void setrole(string r);

    void save();
    void display();

    friend void show_student(const student& s);
};

class teacher
{
    string* name;
    string* email;
    string* password;
    string* role;

public:
    teacher(string tname = "Unknown", string temail = "unknown@gmail.com", string tpass = "password");
    ~teacher();

    string getname();
    string getemail();
    string getrole();

    void setname(string n);
    void setemail(string e);
    void setpassword(string p);
    void setrole(string r);

    void save();
    void display();

    friend void show_teacher(const teacher& t);
};

class classroom
{
    string* classid;
    string* classname;
    string* teacher_email;
    vector<pair<string, string>>* students;

public:
    classroom();
    classroom(string cid, string cname, string temail);
    ~classroom();

    void save();
    void add_student(string sname, string semail);
    void show_students();
    static void show_classrooms();
    static string generate_classid();

    friend void show_classroom(const classroom& c);
};

class assignment
{
    string* id;
    string* title;
    string* description;
    string* due_date;
    string* teacher_email;
    string* class_id;

public:
    assignment(string aid, string atitle, string adesc, string adue, string temail, string cid);
    ~assignment();

    void save();
    static void show_assignments(string cid);
    static string generate_assignment_id();

    friend void show_assignment(const assignment& a);
};

class submission
{
    string* assignment_id;
    string* class_id;
    string* student_name;
    string* student_email;
    string* content;
    string* grade;
    string* feedback;

public:
    submission(string aid, string cid, string sname, string semail, string scontent, string sgrade = "", string sfeedback = "");
    ~submission();

    void save();
    static void show_submissions(string aid);

    void set_grade(string g);
    void set_feedback(string f);
    string get_grade();
    string get_feedback();
    static void assign_grade_and_feedback(string aid, string semail, string grade, string feedback);

    friend void show_submission(const submission& s);
};

// Function declarations for authentication
bool userexists(string name, string email, string pass, string role);
bool check_email(string email);
void signup(string role);
bool login(string role);

// Function declarations for menus
void student_menu(student &s);
void teacher_menu(teacher &t);

#endif