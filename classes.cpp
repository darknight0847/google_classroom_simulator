#include "classes.h"
#include <exception>
#include <stdexcept>

// ==================== STUDENT CLASS ====================
student::student(string sname, string semail, string spass)
    : User(sname, semail, spass, "Student") {}

student::student(const student& other)
    : User(other) {}

student::student(string sname, int studentId)
    : User(sname, "", "", "Student") {}

student::~student() {}

void student::save()
{
    try {
        ofstream file("student_data.txt", ios::app);
        if (!file.is_open())
            throw runtime_error("Unable to open student_data.txt for writing");
        file << *name << "|" << *email << "|" << *password << "|" << *role << "\n";
        file.close();
    } catch (const exception &e) {
        cerr << "Error saving student: " << e.what() << "\n";
    }
}

void student::display()
{
    cout << "Name: " << *name << "\nEmail: " << *email << "\nRole: " << *role << "\n";
}

bool student::operator==(const student& other) const {
    return *email == *other.email;
}

ostream& operator<<(ostream& os, const student& s)
{
    os << "Student: " << *s.name << " | Email: " << *s.email;
    return os;
}

void show_student(const student& s)
{
    cout << "Student: " << *s.name << " | Email: " << *s.email << "\n";
}

// ==================== TEACHER CLASS ====================
teacher::teacher(string tname, string temail, string tpass)
    : User(tname, temail, tpass, "Teacher") {}

teacher::teacher(const teacher& other)
    : User(other) {}

teacher::teacher(string tname, string department)
    : User(tname, "", "", "Teacher") {}

teacher::~teacher() {}

void teacher::save()
{
    try {
        ofstream file("teacher_data.txt", ios::app);
        if (!file.is_open())
            throw runtime_error("Unable to open teacher_data.txt for writing");
        file << *name << "|" << *email << "|" << *password << "|" << *role << "\n";
        file.close();
    } catch (const exception &e) {
        cerr << "Error saving teacher: " << e.what() << "\n";
    }
}

void teacher::display()
{
    cout << "Name: " << *name << "\nEmail: " << *email << "\nRole: " << *role << "\n";
}

bool teacher::operator==(const teacher& other) const {
    return *email == *other.email;
}

ostream& operator<<(ostream& os, const teacher& t)
{
    os << "Teacher: " << *t.name << " | Email: " << *t.email;
    return os;
}

void show_teacher(const teacher& t)
{
    cout << "Teacher: " << *t.name << " | Email: " << *t.email << "\n";
}

// ==================== CLASSROOM CLASS ====================
classroom::classroom()
{
    try {
        classid = new string("");
        classname = new string("");
        teacher_email = new string("");
        students = new vector<pair<string, string>>();
    } catch (const bad_alloc &e) {
        cerr << "Memory allocation failed in classroom constructor: " << e.what() << "\n";
        throw;
    }
}

classroom::classroom(string cid, string cname, string temail)
{
    try {
        classid = new string(cid);
        classname = new string(cname);
        teacher_email = new string(temail);
        students = new vector<pair<string, string>>();
    } catch (const bad_alloc &e) {
        cerr << "Memory allocation failed in classroom parameterized constructor: " << e.what() << "\n";
        throw;
    }
}

classroom::~classroom()
{
    delete classid;
    delete classname;
    delete teacher_email;
    delete students;
}

void classroom::save()
{
    try {
        ofstream file("classroom_data.txt", ios::app);
        if (!file.is_open())
            throw runtime_error("Unable to open classroom_data.txt for writing");
        file << *classid << "|" << *classname << "|" << *teacher_email << "\n";
        file.close();
    } catch (const exception &e) {
        cerr << "Error saving classroom: " << e.what() << "\n";
    }
}

void classroom::add_student(string sname, string semail)
{
    students->push_back({sname, semail});
    try {
        ofstream file("classroom_students.txt", ios::app);
        if (!file.is_open())
            throw runtime_error("Unable to open classroom_students.txt for writing");
        file << *classid << "|" << sname << "|" << semail << "\n";
        file.close();
    } catch (const exception &e) {
        cerr << "Error adding student to classroom: " << e.what() << "\n";
    }
}

void classroom::show_students()
{
    cout << "\n=== Students in Classroom " << *classid << " ===\n";
    for (auto& s : *students)
        cout << "Name: " << s.first << " | Email: " << s.second << "\n";
}

void classroom::show_classrooms()
{
    try {
        ifstream file("classroom_data.txt");
        if (!file.is_open())
        {
            cout << "No classrooms available.\n";
            return;
        }
        cout << "\n=== Available Classrooms ===\n";
        string line;
        while (getline(file, line))
        {
            stringstream ss(line);
            string cid, cname, temail;
            getline(ss, cid, '|');
            getline(ss, cname, '|');
            getline(ss, temail, '|');
            cout << "ID: " << cid << " | Name: " << cname << " | Teacher: " << temail << "\n";
        }
        file.close();
    } catch (const exception &e) {
        cerr << "Error showing classrooms: " << e.what() << "\n";
    }
}

string classroom::generate_classid()
{
    return "C" + to_string(time(0));
}

ostream& operator<<(ostream& os, const classroom& c)
{
    os << "Classroom: " << *c.classname << " | ID: " << *c.classid;
    return os;
}

void show_classroom(const classroom& c)
{
    cout << "Classroom: " << *c.classname << " | ID: " << *c.classid << "\n";
}

// ==================== ASSIGNMENT CLASS ====================
assignment::assignment(string aid, string atitle, string adesc, string adue, string temail, string cid)
{
    try {
        id = new string(aid);
        title = new string(atitle);
        description = new string(adesc);
        due_date = new string(adue);
        teacher_email = new string(temail);
        class_id = new string(cid);
    } catch (const bad_alloc &e) {
        cerr << "Memory allocation failed in assignment constructor: " << e.what() << "\n";
        throw;
    }
}

assignment::assignment(const assignment& other)
{
    try {
        id = new string(*other.id);
        title = new string(*other.title);
        description = new string(*other.description);
        due_date = new string(*other.due_date);
        teacher_email = new string(*other.teacher_email);
        class_id = new string(*other.class_id);
    } catch (const bad_alloc &e) {
        cerr << "Memory allocation failed in assignment copy constructor: " << e.what() << "\n";
        throw;
    }
}

assignment::assignment(string aid, string atitle, int maxPoints)
{
    try {
        id = new string(aid);
        title = new string(atitle);
        description = new string("");
        due_date = new string("");
        teacher_email = new string("");
        class_id = new string("");
    } catch (const bad_alloc &e) {
        cerr << "Memory allocation failed in assignment simple constructor: " << e.what() << "\n";
        throw;
    }
}

assignment::~assignment()
{
    delete id;
    delete title;
    delete description;
    delete due_date;
    delete teacher_email;
    delete class_id;
}

void assignment::save()
{
    try {
        ofstream file("assignments.txt", ios::app);
        if (!file.is_open())
            throw runtime_error("Unable to open assignments.txt for writing");
        file << *id << "|" << *title << "|" << *description << "|" << *due_date << "|" << *teacher_email << "|" << *class_id << "\n";
        file.close();
    } catch (const exception &e) {
        cerr << "Error saving assignment: " << e.what() << "\n";
    }
}

void assignment::show_assignments(string cid)
{
    try {
        ifstream file("assignments.txt");
        if (!file.is_open())
        {
            cout << "No assignments yet.\n";
            return;
        }
        cout << "\n=== Assignments for Classroom " << cid << " ===\n";
        string line;
        bool found = false;
        while (getline(file, line))
        {
            stringstream ss(line);
            string aid, title, desc, due, temail, classid;
            getline(ss, aid, '|');
            getline(ss, title, '|');
            getline(ss, desc, '|');
            getline(ss, due, '|');
            getline(ss, temail, '|');
            getline(ss, classid, '|');
            if (classid == cid)
            {
                found = true;
                cout << "\nAssignment ID: " << aid;
                cout << "\nTitle: " << title;
                cout << "\nDescription: " << desc;
                cout << "\nDue Date: " << due;
                cout << "\n-------------------\n";
            }
        }
        file.close();
        if (!found)
            cout << "No assignments in this classroom.\n";
    } catch (const exception &e) {
        cerr << "Error showing assignments: " << e.what() << "\n";
    }
}

string assignment::generate_assignment_id()
{
    return "AS" + to_string(time(0));
}

bool assignment::operator==(const assignment& other) const
{
    return *id == *other.id;
}

ostream& operator<<(ostream& os, const assignment& a)
{
    os << "Assignment: " << *a.title << " | ID: " << *a.id;
    return os;
}

void show_assignment(const assignment& a)
{
    cout << "Assignment: " << *a.title << " | ID: " << *a.id << "\n";
}

// ==================== SUBMISSION CLASS ====================
submission::submission(string aid, string cid, string sname, string semail, string scontent, string sgrade, string sfeedback)
{
    try {
        assignment_id = new string(aid);
        class_id = new string(cid);
        student_name = new string(sname);
        student_email = new string(semail);
        content = new string(scontent);
        grade = new string(sgrade);
        feedback = new string(sfeedback);
    } catch (const bad_alloc &e) {
        cerr << "Memory allocation failed in submission constructor: " << e.what() << "\n";
        throw;
    }
}

submission::~submission()
{
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
    try {
        ofstream file("submissions.txt", ios::app);
        if (!file.is_open())
            throw runtime_error("Unable to open submissions.txt for writing");
        file << *assignment_id << "|" << *class_id << "|" << *student_name << "|" << *student_email << "|" << *content << "|" << *grade << "|" << *feedback << "\n";
        file.close();
    } catch (const exception &e) {
        cerr << "Error saving submission: " << e.what() << "\n";
    }
}

void submission::show_submissions(string aid)
{
    try {
        ifstream file("submissions.txt");
        if (!file.is_open())
        {
            cout << "No submissions yet.\n";
            return;
        }
        cout << "\n=== Submissions for Assignment " << aid << " ===\n";
        string line;
        bool found = false;
        while (getline(file, line))
        {
            stringstream ss(line);
            string id, classid, sname, semail, content, grade, feedback;
            getline(ss, id, '|');
            getline(ss, classid, '|');
            getline(ss, sname, '|');
            getline(ss, semail, '|');
            getline(ss, content, '|');
            getline(ss, grade, '|');
            getline(ss, feedback, '|');
            if (id == aid)
            {
                found = true;
                cout << "\nStudent: " << sname << " (" << semail << ")";
                cout << "\nContent: " << content;
                cout << "\nGrade: " << grade;
                cout << "\nFeedback: " << feedback;
                cout << "\n-------------------\n";
            }
        }
        file.close();
        if (!found)
            cout << "No submissions for this assignment.\n";
    } catch (const exception &e) {
        cerr << "Error showing submissions: " << e.what() << "\n";
    }
}

void submission::set_grade(string g) { *grade = g; }
void submission::set_feedback(string f) { *feedback = f; }
string submission::get_grade() { return *grade; }
string submission::get_feedback() { return *feedback; }

void submission::assign_grade_and_feedback(string aid, string semail, string grade, string feedback)
{
    try {
        ifstream file("submissions.txt");
        ofstream temp("temp.txt");
        if (!file.is_open() || !temp.is_open())
            throw runtime_error("Unable to open submissions.txt or temp.txt for updating");
        string line;
        while (getline(file, line))
        {
            stringstream ss(line);
            string id, classid, sname, email, content, old_grade, old_feedback;
            getline(ss, id, '|');
            getline(ss, classid, '|');
            getline(ss, sname, '|');
            getline(ss, email, '|');
            getline(ss, content, '|');
            getline(ss, old_grade, '|');
            getline(ss, old_feedback, '|');
            if (id == aid && email == semail)
            {
                temp << id << "|" << classid << "|" << sname << "|" << email << "|" << content << "|" << grade << "|" << feedback << "\n";
            }
            else
            {
                temp << line << "\n";
            }
        }
        file.close();
        temp.close();
        remove("submissions.txt");
        rename("temp.txt", "submissions.txt");
    } catch (const exception &e) {
        cerr << "Error assigning grade/feedback: " << e.what() << "\n";
    }
}

bool submission::operator==(const submission& other) const
{
    return *assignment_id == *other.assignment_id && *student_email == *other.student_email;
}

ostream& operator<<(ostream& os, const submission& s)
{
    os << "Submission by: " << *s.student_name << " for Assignment: " << *s.assignment_id;
    return os;
}

void show_submission(const submission& s)
{
    cout << "Submission by: " << *s.student_name << " for Assignment: " << *s.assignment_id << "\n";
}


// ==================== ANNOUNCEMENT CLASS ====================
announcement::announcement(string aid, string atitle, string acontent, string temail, string cid)
{
    try {
        id = new string(aid);
        title = new string(atitle);
        content = new string(acontent);
        teacher_email = new string(temail);
        class_id = new string(cid);
        date = new string(to_string(time(0)));
        comments = new vector<pair<string, string>>();
    } catch (const bad_alloc &e) {
        cerr << "Memory allocation failed in announcement constructor: " << e.what() << "\n";
        throw;
    }
}

announcement::announcement(const announcement& other)
{
    try {
        id = new string(*other.id);
        title = new string(*other.title);
        content = new string(*other.content);
        teacher_email = new string(*other.teacher_email);
        class_id = new string(*other.class_id);
        date = new string(*other.date);
        comments = new vector<pair<string, string>>(*other.comments);
    } catch (const bad_alloc &e) {
        cerr << "Memory allocation failed in announcement copy constructor: " << e.what() << "\n";
        throw;
    }
}

announcement::~announcement()
{
    delete id;
    delete title;
    delete content;
    delete teacher_email;
    delete class_id;
    delete date;
    delete comments;
}

void announcement::save()
{
    try {
        ofstream file("announcements.txt", ios::app);
        if (!file.is_open())
            throw runtime_error("Unable to open announcements.txt for writing");
        file << *id << "|" << *title << "|" << *content << "|" << *teacher_email << "|" << *class_id << "|" << *date << "\n";
        file.close();
    } catch (const exception &e) {
        cerr << "Error saving announcement: " << e.what() << "\n";
    }
}

void announcement::add_comment(string student_email, string comment)
{
    try {
        ofstream file("announcement_comments.txt", ios::app);
        if (!file.is_open())
            throw runtime_error("Unable to open announcement_comments.txt for writing");
        file << *id << "|" << student_email << "|" << comment << "\n";
        file.close();
        if (comments)
            comments->push_back({student_email, comment});
    } catch (const exception &e) {
        cerr << "Error adding announcement comment: " << e.what() << "\n";
    }
}

void announcement::show_announcements(string class_id)
{
    try {
        ifstream file("announcements.txt");
        if (!file.is_open())
        {
            cout << "No announcements yet.\n";
            return;
        }

        cout << "\n=== Announcements ===\n";
        string line;
        bool found = false;
        while (getline(file, line))
        {
            stringstream ss(line);
            string aid, title, content, temail, cid, date;
            getline(ss, aid, '|');
            getline(ss, title, '|');
            getline(ss, content, '|');
            getline(ss, temail, '|');
            getline(ss, cid, '|');
            getline(ss, date, '|');

            if (cid == class_id)
            {
                found = true;
                cout << "\nAnnouncement ID: " << aid;
                cout << "\nTitle: " << title;
                cout << "\nContent: " << content;
                cout << "\nPosted by: " << temail;
                cout << "\nDate: " << date;
                cout << "\n-------------------\n";
            }
        }
        file.close();

        if (!found)
            cout << "No announcements in this classroom.\n";
    } catch (const exception &e) {
        cerr << "Error showing announcements: " << e.what() << "\n";
    }
}

void announcement::show_announcement_comments(string announcement_id)
{
    try {
        ifstream file("announcement_comments.txt");
        if (!file.is_open())
        {
            cout << "No comments yet.\n";
            return;
        }

        cout << "\n=== Comments (Visible only to Teacher) ===\n";
        string line;
        bool found = false;
        while (getline(file, line))
        {
            stringstream ss(line);
            string aid, semail, comment;
            getline(ss, aid, '|');
            getline(ss, semail, '|');
            getline(ss, comment, '|');

            if (aid == announcement_id)
            {
                found = true;
                cout << "\nFrom: " << semail;
                cout << "\nComment: " << comment;
                cout << "\n-------------------\n";
            }
        }
        file.close();

        if (!found)
            cout << "No comments on this announcement.\n";
    } catch (const exception &e) {
        cerr << "Error showing announcement comments: " << e.what() << "\n";
    }
}

string announcement::generate_announcement_id()
{
    return "A" + to_string(time(0));
}

bool announcement::operator==(const announcement& other) const
{
    return *id == *other.id;
}

ostream& operator<<(ostream& os, const announcement& a)
{
    os << "Announcement: " << *a.title << " | Posted by: " << *a.teacher_email;
    return os;
}

void show_announcement(const announcement& a)
{
    cout << "Announcement: " << *a.title << " | Posted by: " << *a.teacher_email << "\n";
}
