/*SNHU CS300 FINAL
AUTHOR: RUSSELL K CHIMUNYA
08/17/25
*/
// ProjectTwo.cpp
// Single-file implementation for ABCU Advising Assistance Program (CS 300 Project Two)
// Reads a CSV of courses and prerequisites, stores them in a BST keyed by course number,
// prints an alphanumeric course list, and prints info for a specific course.
//
// Build (Windows, g++ example):
//   g++ -std=c++17 -O2 -o ProjectTwo ProjectTwo.cpp
//
// Sample menu/output format follows the provided assignment sample.


#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
#include <cctype>

using namespace std;

//Utility helpers /
static inline string trim(const string& s) {
    size_t start = 0;
    while (start < s.size() && isspace(static_cast<unsigned char>(s[start]))) ++start;
    size_t end = s.size();
    while (end > start && isspace(static_cast<unsigned char>(s[end - 1]))) --end;
    return s.substr(start, end - start);
}

static inline string toUpper(string s) {
    for (char& ch : s) ch = static_cast<char>(toupper(static_cast<unsigned char>(ch))); //
    return s;
}

// Split a CSV line by commas (no quoted-field handling needed for the provided input)
static vector<string> splitCSV(const string& line) {
    vector<string> fields;
    string field;
    stringstream ss(line);
    while (getline(ss, field, ',')) {
        fields.push_back(trim(field));
    }
    return fields;
}

//----------------------- Domain model -----------------------//
struct Course {
    string number;                 // e.g., "CSCI200"
    string title;                  // e.g., "Data Structures"
    vector<string> prerequisites;  // e.g., {"CSCI101", "MATH201"}
};

//----------------------- BST implementation -----------------------//
struct Node {
    Course data;
    Node* left = nullptr;
    Node* right = nullptr;
    explicit Node(const Course& c) : data(c) {}
};

class CourseBST {
public:
    ~CourseBST() { destroy(root); }

    // Insert or upsert by course number
    void insert(const Course& c) {
        root = insertRec(root, c);
    }

    // Find a course by number; returns nullptr if not found
    const Course* find(const string& courseNum) const {
        Node* cur = root;
        while (cur) {
            if (courseNum == cur->data.number) return &cur->data;
            if (courseNum < cur->data.number) cur = cur->left;
            else cur = cur->right;
        }
        return nullptr;
    }

    // In-order traversal printing "CSCI100, Introduction to Computer Science"
    void printInOrder() const {
        inOrderRec(root);
    }

    // Optional: collect all courses in-order (not required for assignment output)
    vector<Course> toVector() const {
        vector<Course> out;
        out.reserve(countNodes(root));
        toVectorRec(root, out);
        return out;
    }

    bool empty() const { return root == nullptr; }

private:
    Node* root = nullptr;

    static Node* insertRec(Node* node, const Course& c) {
        if (!node) return new Node(c);
        if (c.number == node->data.number) {
            // Upsert: replace title and prerequisites if the course already exists
            node->data.title = c.title;
            node->data.prerequisites = c.prerequisites;
        } else if (c.number < node->data.number) {
            node->left = insertRec(node->left, c);
        } else {
            node->right = insertRec(node->right, c);
        }
        return node;
    }

    static void inOrderRec(Node* node) {
        if (!node) return;
        inOrderRec(node->left);
        cout << node->data.number << ", " << node->data.title << "\n\n";
        inOrderRec(node->right);
    }

    static void toVectorRec(Node* node, vector<Course>& out) {
        if (!node) return;
        toVectorRec(node->left, out);
        out.push_back(node->data);
        toVectorRec(node->right, out);
    }

    static size_t countNodes(Node* node) {
        if (!node) return 0;
        return 1 + countNodes(node->left) + countNodes(node->right);
    }

    static void destroy(Node* node) {
        if (!node) return;
        destroy(node->left);
        destroy(node->right);
        delete node;
    }
};

//----------------------- CSV loading -----------------------//
struct LoadResult {
    size_t loaded = 0;
    size_t skipped = 0;
    vector<string> errors;
};

static LoadResult loadCoursesFromCSV(const string& filename, CourseBST& bst) {
    LoadResult res;
    ifstream in(filename);
    if (!in) {
        res.errors.push_back("Error: Could not open file '" + filename + "'.");
        return res;
    }

    string line;
    size_t lineNo = 0;
    while (getline(in, line)) {
        ++lineNo;
        // Handle potential Windows CR at end of line
        if (!line.empty() && line.back() == '\r') line.pop_back();
        if (trim(line).empty()) continue; // skip blank lines

        vector<string> fields = splitCSV(line);
        if (fields.size() < 2) {
            res.errors.push_back("Line " + to_string(lineNo) + ": format error (need at least course number and title).");
            ++res.skipped;
            continue;
        }

        Course c;
        c.number = toUpper(fields[0]);
        c.title = fields[1];

        // Remaining fields are prerequisites (if any)
        for (size_t i = 2; i < fields.size(); ++i) {
            string p = toUpper(fields[i]);
            if (!p.empty()) c.prerequisites.push_back(p);
        }

        bst.insert(c);
        ++res.loaded;
    }

    return res;
}

//----------------------- Program UI -----------------------//
static void printMenu() {
    cout << "1. Load Data Structure.\n";
    cout << "2. Print Course List.\n";
    cout << "3. Print Course.\n";
    cout << "9. Exit\n\n";
}

static void printWelcome() {
    cout << "Welcome to the course planner.\n\n";
}

static bool handlePrintCourse(const CourseBST& bst) {
    cout << "What course do you want to know about? ";
    string input;
    if (!getline(cin, input)) return false;
    input = toUpper(trim(input));
    cout << "\n";
    if (input.empty()) {
        cout << "No course entered.\n\n";
        return true;
    }

    const Course* c = bst.find(input);
    if (!c) {
        cout << "Course not found.\n\n";
        return true;
    }

    cout << c->number << ", " << c->title << "\n\n";
    if (c->prerequisites.empty()) {
        cout << "Prerequisites: None\n\n";
    } else {
        cout << "Prerequisites: ";
        for (size_t i = 0; i < c->prerequisites.size(); ++i) {
            cout << c->prerequisites[i];
            if (i + 1 < c->prerequisites.size()) cout << ", ";
        }
        cout << "\n\n";
    }
    return true;
}

// Main entry point for the ABCU Advising Assistance Program.
// Handles user interaction and menu navigation.
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    CourseBST bst;
    bool dataLoaded = false;

    printWelcome();

    while (true) {
        printMenu();
        cout << "What would you like to do? ";
        string choiceLine;
        if (!getline(cin, choiceLine)) break;
        string choiceTrimmed = trim(choiceLine);

        cout << "\n";
        if (choiceTrimmed.empty() || !all_of(choiceTrimmed.begin(), choiceTrimmed.end(), ::isdigit)) { 
            cout << choiceTrimmed << " is not a valid option.\n\n";
            continue;
        }

        int choice = stoi(choiceTrimmed);

        if (choice == 1) {
            cout << "Enter the file name to load: ";
            string filename;
            if (!getline(cin, filename)) break;
            filename = trim(filename);
            cout << "\n";

            LoadResult res = loadCoursesFromCSV(filename, bst);
            if (!res.errors.empty()) {
                for (const auto& err : res.errors) {
                    cout << err << "\n";
                }
                cout << "\n";
            }
            if (res.loaded > 0) {
                dataLoaded = true;
                cout << "Loaded " << res.loaded << " course(s).";
                if (res.skipped > 0) cout << " Skipped " << res.skipped << " invalid line(s).";
                cout << "\n\n";
            } else if (res.errors.empty()) {
                cout << "No data loaded.\n\n";
            }
        }
        else if (choice == 2) {
            if (!dataLoaded || bst.empty()) {
                cout << "No data loaded. Please choose option 1 first.\n\n";
                continue;
            }
            cout << "Here is a sample schedule:\n\n";
            bst.printInOrder();
        }
        else if (choice == 3) {
            if (!dataLoaded || bst.empty()) {
                cout << "No data loaded. Please choose option 1 first.\n\n";
                continue;
            }
            handlePrintCourse(bst);
        }
        else if (choice == 9) {
            cout << "Thank you for using the course planner!\n";
            break;
        }
        else {
            cout << choice << " is not a valid option.\n\n";
        }
    }

    return 0;
}
