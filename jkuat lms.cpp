

#include <iostream>#include <vector>#include <string>#include <iomanip>
using namespace std;
// Structure to store grades for a specific unitstruct UnitGrade {
    string unitCode;
    string unitName;
    double assignmentScore = 0.0;
    double catScore = 0.0;
    double examScore = 0.0;
    double totalScore = 0.0;
    bool isGraded = false;

// Structure to represent a Studentstruct Student {
    string studentId;
    string name;
    string registeredUnits;

// Global data stores (Simulating a synchronized database)vector<Student> studentDatabase;
// Helper function to find a student by IDStudent* findStudent(const string& id) {
    for (auto& student : studentDatabase) {
        if (student.studentId == id) {
            return &student;
        }
    }
    return nullptr;
}
// Seed initial mock data for JKUAT systemvoid initializeSystemData() {
    Student s1 = {"CIT-211-001/2024", "John Doe", {
        {"ICS2101", "Introduction to Programming", 0, 0, 0, 0, false},
        {"ICS2104", "Object Oriented Programming", 0, 0, 0, 0, false}
    }};
    Student s2 = {"CIT-211-002/2024", "Jane Smith", {
        {"ICS2101", "Introduction to Programming", 0, 0, 0, 0, false},
        {"SMA2100", "Calculus I", 0, 0, 0, 0, false}
    }};
    
    studentDatabase.push_back(s1);
    studentDatabase.push_back(s2);
}
// --- MODULE 1: LECTURER MANAGEMENT SYSTEM ---void lecturerModule() {
    cout << "\n========================================\n";
    cout << "  JKUAT LMS - LECTURER INTERFACE        \n";
    cout << "========================================\n";
    
    string searchId, unitCode;
    cout << "Enter Student ID: ";
    cin.ignore();
    getline(cin, searchId);
    
    Student* student = findStudent(searchId);
    if (!student) {
        cout << "Error: Student not found in the system.\n";
        return;
    }
    
    cout << "\nRegistered units for " << student->name << ":\n";
    for (const auto& unit : student->registeredUnits) {
        cout << "- " << unit.unitCode << ": " << unit.unitName << "\n";
    }
    
    cout << "\nEnter Unit Code to grade: ";
    cin >> unitCode;
    
    bool unitFound = false;
    for (auto& unit : student->registeredUnits) {
        if (unit.unitCode == unitCode) {
            unitFound = true;
            
            cout << "Enter Assignment Score (Max 20): ";
            cin >> unit.assignmentScore;
            cout << "Enter CAT Score (Max 20): ";
            cin >> unit.catScore;
            cout << "Enter Final Exam Score (Max 60): ";
            cin >> unit.examScore;
            
            unit.totalScore = unit.assignmentScore + unit.catScore + unit.examScore;
            unit.isGraded = true;
            
            cout << "\nMarks entered successfully on LMS and synchronized with Portal.\n";
            break;
        }
    }
    
    if (!unitFound) {
        cout << "Error: Student is not registered for this unit.\n";
    }
}
// --- MODULE 2: STUDENT PORTAL ---void studentModule() {
    cout << "\n========================================\n";
    cout << "  JKUAT OFFICIAL STUDENT PORTAL         \n";
    cout << "========================================\n";
    
    string searchId;
    cout << "Enter your Student ID to log in: ";
    cin.ignore();
    getline(cin, searchId);
    
    Student* student = findStudent(searchId);
    if (!student) {
        cout << "Error: Verification failed. Invalid Student ID.\n";
        return;
    }
    
    cout << "\nWelcome, " << student->name << "\n";
    cout << "----------------------------------------------------------------------\n";
    cout << left << setw(12) << "Unit Code" << setw(32) << "Unit Name" << "Score/Grade\n";
    cout << "----------------------------------------------------------------------\n";
    
    for (const auto& unit : student->registeredUnits) {
        cout << left << setw(12) << unit.unitCode << setw(32) << unit.unitName;
        if (unit.isGraded) {
            cout << unit.totalScore << " / 100\n";
        } else {
            cout << "Not Graded Yet\n";
        }
    }
    cout << "----------------------------------------------------------------------\n";
}
// --- MAIN MENU ROUTER ---int main() {
    initializeSystemData();
    int choice = 0;
    
    while (choice != 3) {
        cout << "\n========================================\n";
        cout << "  JKUAT INFORMATION MANAGEMENT SYSTEM   \n";
        cout << "========================================\n";
        cout << "1. Access Lecturer Module (LMS)\n";
        cout << "2. Access Student Module (Portal)\n";
        cout << "3. Exit System\n";
        cout << "Choose an option: ";
        cin >> choice;
        
        switch (choice) {
            case 1:
                lecturerModule();
                break;
            case 2:
                studentModule();
                break;
            case 3:
                cout << "Exiting JKUAT System. Goodbye!\n";
                break;
            default:
                cout << "Invalid option. Please try again.\n";
        }
    }
    return 0;
}

