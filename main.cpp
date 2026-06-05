#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <fstream>
#include <map> 
#include <string>
#include <vector>
#include <iomanip>
#include <sstream>

using namespace std;

/* FILE PATH CONFIGURATION
Defines the path where grade data is stored.*/


// OPTION 1 (recommended): relative path
const string GRADES_FILE = "grades.txt"; // <---- Use this if you run the program locally (e.g., from an IDE)
//  The file will be created/read in the same directory as the executable.*/

//OPTION 2 : absolute path
//const string GRADES_FILE = "C:\\Users\\aless\\Desktop\\Grades\\Grades\\Grades\\grades.txt";
/* IMPORTANT: Update this path to a valid location on your system before running the program.
This file is used to store and load grades persistently.*/ 




/* DATA STRUCTURES
   These maps store all course-related information:
   - grades: assessment scores per course
   - weights: percentage weight of each assessment
   - bonuses: extra points (e.g., participation, sessions)
   - courseNames: mapping of course codes to course titles */

map<string, vector<double>> grades;
map<string, vector<double>> weights;
map<string, vector<bool>> bonuses;
map<string, string> courseNames;

/* INITIALIZATION FUNCTION
   Initializes course names and allocates default values
   for grades, weights, and bonus flags. */

void initData() {
    courseNames["COMP-1001"] = "Technical English";
    courseNames["COMP-1002"] = "Computer Networks";
    courseNames["COMP-1003"] = "Programming Principles";
    courseNames["COMP-1004"] = "Computer Architectures";
    courseNames["COMP-1005"] = "ICT Fundamentals";

    // Initialize data containers for each course
    for (auto& c : courseNames) {
        grades[c.first] = vector<double>(4, 0.0);
        weights[c.first] = vector<double>(4, 0.0);
        bonuses[c.first] = vector<bool>(2, false);
    }
}

/*   LOAD FUNCTION
   Reads stored data from file and populates data structures.
   Each record contains:
   course code, assessment index, grade, weight, bonus flags */

void loadGrades() {
    ifstream file(GRADES_FILE);
    if (!file.is_open()) return;

    string course;
    int index;
    double grade, weight;
    int b1, b2;

    while (file >> course >> index >> grade >> weight >> b1 >> b2) {
        grades[course][index] = grade;
        weights[course][index] = weight;
        bonuses[course][0] = b1;
        bonuses[course][1] = b2;
    }

    file.close();
}

/*  SAVE FUNCTION
   Writes all current data to file to ensure persistence.*/

void saveGrades() {
    ofstream file(GRADES_FILE);

    for (auto& g : grades) {
        for (int i = 0; i < 4; i++) {
            file << g.first << " " << i << " "
                << g.second[i] << " "
                << weights[g.first][i] << " "
                << bonuses[g.first][0] << " "
                << bonuses[g.first][1] << endl;
        }
    }

    file.close();
}

/*AVERAGE CALCULATION
Computes the weighted average of assessments for a course.*/

double calculateAverage(string course) {
    double sum = 0, total = 0;

    for (int i = 0; i < 4; i++) {
        sum += grades[course][i] * weights[course][i];
        total += weights[course][i];
    }

    if (total == 0) return 0;

    return sum / total;
}

/*   BONUS CALCULATION
   Adds extra points based on enabled bonus conditions.
   Each bonus contributes +5% at the total average of any course.*/
double getBonus(string course) {
    double b = 0;
    if (bonuses[course][0]) b += 5;
    if (bonuses[course][1]) b += 5;
    return b;
}
/*   FINAL GRADE CALCULATION
   Combines weighted average and bonus.
   Caps the result at 100%.*/

double calculateFinal(string course) {
    double final = calculateAverage(course) + getBonus(course);
    return (final > 100) ? 100 : final;
}



/*   UPDATE FUNCTION
   Allows the user to input or modify grades and weights.
   Includes input validation and formatting.*/

void updateGrade() {
    string input;
    int assn;

    cout << "\nCourses:\n";
    for (auto& c : courseNames) {
        cout << c.first.substr(5) << " - " << c.second << endl;
    }

    cout << "\nCourse: ";
    cin >> input;

    string key = "COMP-" + input;

    if (grades.find(key) == grades.end()) {
        cout << "Course not found!\n";
        return;
    }

    cout << "Assessment (1-4): ";
    cin >> assn;

    if (assn < 1 || assn > 4) {
        cout << "Invalid assessment!\n";
        return;
    }

    int idx = assn - 1;

    string g;
    cout << "Grade: ";
    cin >> g;

    // Replace comma with dot for decimal compatibility

    for (char& c : g) if (c == ',') c = '.';
    double newGrade = stod(g);

    double newWeight;
    cout << "Weight (%): ";
    cin >> newWeight;

    grades[key][idx] = newGrade;
    weights[key][idx] = newWeight;

    saveGrades();

    cout << "Updated!\n";
}

/*    BONUS MANAGEMENT
   Allows toggling of bonus conditions for a course. */

void setBonus() {
    string input;
    cout << "\nCourse: ";
    cin >> input;

    string key = "COMP-" + input;

    if (bonuses.find(key) == bonuses.end()) {
        cout << "Course not found!\n";
        return;
    }

    cout << "1. Practices (+5%)\n";
    cout << "2. Live Sessions (+5%)\n";
    cout << "Choice: ";

    int c;
    cin >> c;

    if (c == 1 || c == 2) {
        bonuses[key][c - 1] = !bonuses[key][c - 1];
        saveGrades();
        cout << "Bonus updated!\n";
    }
}

/*   DISPLAY FUNCTION
   Outputs all course data including:
   - individual assessments
   - weighted average
   - bonuses
   - final grade */


void viewGrades() {
    cout << "\n=== GRADES ===\n\n";

    for (auto& g : grades) {
        cout << g.first << " - " << courseNames[g.first] << endl;

        for (int i = 0; i < 4; i++) {
            stringstream ss;
            ss << fixed << setprecision(2)
                << g.second[i] << "% ("
                << setprecision(0)
                << weights[g.first][i] << "%)";
            cout << "A" << i + 1 << ": " << ss.str() << endl;
        }

        cout << "Average: " << fixed << setprecision(2)
            << calculateAverage(g.first) << "%\n";

        cout << "Bonus: +" << getBonus(g.first) << "%\n";

        cout << "Final: " << fixed << setprecision(2)
            << calculateFinal(g.first) << "%\n\n";
    }
}

/*   MAIN FUNCTION
   Entry point of the application.
   Handles menu navigation and user interaction loop.*/

int main() {
    initData();
    loadGrades();

    int choice;

    while (true) {
        cout << "\n1.Update Grades\n2.View Grades\n3.Set Bonus\n4.Exit\nChoice: ";
        cin >> choice;

        switch (choice) {
        case 1: updateGrade(); break;
        case 2: viewGrades(); break;
        case 3: setBonus(); break;
        case 4: return 0;
        default: cout << "Choose 1-4!\n";
        }
    }
}
