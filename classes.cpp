#include "classes.h"

// Student class implementation

student::student(string sname, string semail, string spass)
{
    name = new string(sname);
    email = new string(semail);
    password = new string(spass);
    role = new string("Student");
}


student::student(const student& other)
{
    name = new string(*other.name);
    email = new string(*other.email);
    password = new string(*other.password);
    role = new string(*other.role);
}

student::student(string sname, int studentId)
{
    name = new string(sname);
    email = new string(sname + to_string(studentId) + "@gmail.com");
    password = new string("pass" + to_string(studentId));
    role = new string("Student");
}

student::~student() {
    delete name;
    delete email;
    delete password;
    delete role;
}


string student::getname() { return *name; }
string student::getemail() { return *email; }
string student::getrole() { return *role; }

void student::setname(string n) { *name = n; }
void student::setemail(string e) { *email = e; }
void student::setpassword(string p) { *password = p; }
void student::setrole(string r) { *role = r; }


void student::save()
{
    ofstream file("student_data.txt", ios::app);
    file << *name << "|" << *email << "|" << *password << "|" << *role << "\n";
    file.close();
}


void student::display()
{
    cout << "\n===== " << *role << " Dashboard =====\n";
    cout << "Welcome, " << *name << "\n";
    cout << "Role: " << *role << "\n";
    cout << "=============================\n";
}

void show_student(const student& s) {
    cout << "Student: " << *s.name << " | Email: " << *s.email << "\n";
}

// Teacher class implementation

teacher::teacher(string tname, string temail, string tpass)
{
    name = new string(tname);
    email = new string(temail);
    password = new string(tpass);
    role = new string("Teacher");
}


teacher::teacher(const teacher& other)
{
    name = new string(*other.name);
    email = new string(*other.email);
    password = new string(*other.password);
    role = new string(*other.role);
}


teacher::teacher(string tname, string department)
{
    name = new string(tname);
    email = new string(tname + "." + department + "@gmail.com");
    password = new string("pass" + department);
    role = new string("Teacher");
}

teacher::~teacher() {
    delete name;
    delete email;
    delete password;
    delete role;
}


string teacher::getname() { return *name; }
string teacher::getemail() { return *email; }
string teacher::getrole() { return *role; }

void teacher::setname(string n) { *name = n; }
void teacher::setemail(string e) { *email = e; }
void teacher::setpassword(string p) { *password = p; }
void teacher::setrole(string r) { *role = r; }


void teacher::save()
{
    ofstream file("teacher_data.txt", ios::app);
    file << *name << "|" << *email << "|" << *password << "|" << *role << "\n";
    file.close();
}


void teacher::display()
{
    cout << "\n===== " << *role << " Dashboard =====\n";
    cout << "Welcome, " << *name << "\n";
    cout << "Role: " << *role << "\n";
    cout << "=============================\n";
}

void show_teacher(const teacher& t) {
    cout << "Teacher: " << *t.name << " | Email: " << *t.email << "\n";
}

// Classroom class implementation

classroom::classroom() {
    classid = new string("");
    classname = new string("");
    teacher_email = new string("");
    students = new vector<pair<string, string>>();
}

classroom::classroom(string cid, string cname, string temail)
{
    classid = new string(cid);
    classname = new string(cname);
    teacher_email = new string(temail);
    students = new vector<pair<string, string>>();
}

classroom::~classroom() {
    delete classid;
    delete classname;
    delete teacher_email;
    delete students;
}


void classroom::save()
{
    ofstream file("classroom_data.txt", ios::app);
    file << *classid << "|" << *classname << "|" << *teacher_email << "\n";
    file.close();
}


void classroom::add_student(string sname, string semail)
{
    students->push_back({sname, semail});
    ofstream file("classroom_students.txt", ios::app);
    file << *classid << "|" << sname << "|" << semail << "\n";
    file.close();
}


void classroom::show_students()
{
    cout << "\n=== students in classroom " << *classname << " (" << *classid << ") ===\n";
    for (auto &s : *students)
    {
        cout << "name: " << s.first << " | email: " << s.second << "\n";
    }
    if (students->empty())
    {
        cout << "no students yet.\n";
    }
}

void show_classroom(const classroom& c) {
    cout << "Classroom: " << *c.classid << " | Name: " << *c.classname << "\n";
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
    id = new string(aid);
    title = new string(atitle);
    description = new string(adesc);
    due_date = new string(adue);
    teacher_email = new string(temail);
    class_id = new string(cid);
}

assignment::assignment(const assignment& other)
{
    id = new string(*other.id);
    title = new string(*other.title);
    description = new string(*other.description);
    due_date = new string(*other.due_date);
    teacher_email = new string(*other.teacher_email);
    class_id = new string(*other.class_id);
}

assignment::assignment(string aid, string atitle, int maxPoints)
{
    id = new string(aid);
    title = new string(atitle);
    description = new string("Maximum points: " + to_string(maxPoints));
    due_date = new string("2025-12-31"); // Default end of year
    teacher_email = new string("automated@gmail.com");
    class_id = new string("AUTO");
}

assignment::~assignment() {
    delete id;
    delete title;
    delete description;
    delete due_date;
    delete teacher_email;
    delete class_id;
}


void assignment::save()
{
    ofstream file("assignments.txt", ios::app);
    file << *id << "|" << *title << "|" << *description << "|" << *due_date << "|" << *teacher_email << "|" << *class_id << "\n";
    file.close();
}

void show_assignment(const assignment& a) {
    cout << "Assignment: " << *a.id << " | Title: " << *a.title << "\n";
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

submission::submission(string aid, string cid, string sname, string semail, string scontent, string sgrade, string sfeedback)
{
    assignment_id = new string(aid);
    class_id = new string(cid);
    student_name = new string(sname);
    student_email = new string(semail);
    content = new string(scontent);
    grade = new string(sgrade);
    feedback = new string(sfeedback);
}

submission::~submission() {
    delete assignment_id;
    delete class_id;
    delete student_name;
    delete student_email;
    delete content;
    delete grade;
    delete feedback;
}


void submission::save()
{
    ofstream file("submissions.txt", ios::app);
    file << *assignment_id << "|" << *class_id << "|" << *student_name << "|" << *student_email << "|" << *content << "|" << *grade << "|" << *feedback << "\n";
    file.close();
}

void show_submission(const submission& s) {
    cout << "Submission by: " << *s.student_name << " | Assignment: " << *s.assignment_id << "\n";
    cout << "Grade: " << *s.grade << " | Feedback: " << *s.feedback << "\n";
}

void submission::show_submissions(string aid)
{
    ifstream file("submissions.txt");
    string line;
    cout << "\n=== Submissions for Assignment " << aid << " ===\n";
    while (getline(file, line))
    {
        stringstream ss(line);
        string id, classid, sname, semail, scontent, sgrade, sfeedback;
        getline(ss, id, '|');
        getline(ss, classid, '|');
        getline(ss, sname, '|');
        getline(ss, semail, '|');
        getline(ss, scontent, '|');
        getline(ss, sgrade, '|');
        getline(ss, sfeedback, '|');

        if (id == aid)
        {
            cout << "Class: " << classid << "\n";
            cout << "Student: " << sname << " (" << semail << ")\n";
            cout << "Content: " << scontent << "\n";
            cout << "Grade: " << sgrade << "\n";
            cout << "Feedback: " << sfeedback << "\n\n";
        }
    }
    file.close();
}

void submission::set_grade(string g) { *grade = g; }
void submission::set_feedback(string f) { *feedback = f; }
string submission::get_grade() { return *grade; }
string submission::get_feedback() { return *feedback; }

void submission::assign_grade_and_feedback(string aid, string semail, string grade, string feedback) {
    // Read all submissions, update the matching one, and rewrite the file
    ifstream infile("submissions.txt");
    vector<string> lines;
    string line;
    while (getline(infile, line)) {
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
            // Update grade and feedback
            ostringstream updated;
            updated << id << "|" << classid << "|" << sname << "|" << email << "|" << content << "|" << grade << "|" << feedback;
            lines.push_back(updated.str());
        } else {
            lines.push_back(line);
        }
    }
    infile.close();
    ofstream outfile("submissions.txt");
    for (const auto& l : lines) {
        outfile << l << "\n";
    }
    outfile.close();
}