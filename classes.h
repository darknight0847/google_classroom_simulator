#ifndef CLASSES_H
#define CLASSES_H

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <ctime>

using namespace std;

class User {
protected:
    string* name;
    string* email;
    string* password;
    string* role;
public:
    User(string uname = "Unknown", string uemail = "unknown@gmail.com", string upass = "password", string urole = "User") {
        name = new string(uname);
        email = new string(uemail);
        password = new string(upass);
        role = new string(urole);
    }
    User(const User& other) {
        name = new string(*other.name);
        email = new string(*other.email);
        password = new string(*other.password);
        role = new string(*other.role);
    }
    virtual ~User() {
        delete name;
        delete email;
        delete password;
        delete role;
    }
    string getname() { return *name; }
    string getemail() { return *email; }
    string getrole() { return *role; }
    void setname(string n) { *name = n; }
    void setemail(string e) { *email = e; }
    void setpassword(string p) { *password = p; }
    void setrole(string r) { *role = r; }
};

class student : public User
{
public:
    student(string sname = "Unknown", string semail = "unknown@gmail.com", string spass = "password");
    student(const student& other); 
    student(string sname, int studentId); 
    ~student();

    void save();
    void display();

    friend void show_student(const student& s);
    bool operator==(const student& other) const;
    friend ostream& operator<<(ostream& os, const student& s);
};

class teacher : public User
{
public:
    teacher(string tname = "Unknown", string temail = "unknown@gmail.com", string tpass = "password");
    teacher(const teacher& other); 
    teacher(string tname, string department); 
    ~teacher();

    void save();
    void display();

    friend void show_teacher(const teacher& t);
    bool operator==(const teacher& other) const;
    friend ostream& operator<<(ostream& os, const teacher& t);
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
    friend ostream& operator<<(ostream& os, const classroom& c);
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
    assignment(const assignment& other); 
    assignment(string aid, string atitle, int maxPoints); 
    ~assignment();

    void save();
    static void show_assignments(string cid);
    static string generate_assignment_id();

    friend void show_assignment(const assignment& a);
    bool operator==(const assignment& other) const;
    friend ostream& operator<<(ostream& os, const assignment& a);
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
    bool operator==(const submission& other) const;
    friend ostream& operator<<(ostream& os, const submission& s);
};

// Function declarations for authentication
bool userexists(string name, string email, string pass, string role);
bool check_email(string email);
void signup(string role);
bool login(string role);


// Announcement class for managing classroom announcements
class announcement {
private:
    string* id;                 // Unique identifier for the announcement
    string* title;             // Title of the announcement
    string* content;           // Content of the announcement
    string* teacher_email;     // Email of the teacher who made the announcement
    string* class_id;          // ID of the classroom where announcement is made
    string* date;              // Date when announcement was made
    vector<pair<string, string>>* comments;  // Vector of student comments (student_email, comment)

public:
    // Constructors and destructor
    announcement(string aid = "", string atitle = "", string acontent = "", string temail = "", string cid = "");
    announcement(const announcement& other);
    ~announcement();

    // Member functions
    void save();
    void add_comment(string student_email, string comment);
    static void show_announcements(string class_id);
    static void show_announcement_comments(string announcement_id);
    static string generate_announcement_id();

    // Operator overloading and friend functions
    friend void show_announcement(const announcement& a);
    bool operator==(const announcement& other) const;
    friend ostream& operator<<(ostream& os, const announcement& a);
};

// Function declarations for menus
void student_menu(student &s);
void teacher_menu(teacher &t);

#endif
