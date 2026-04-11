# Grade Management System (C++)

## Overview

This project is a Grade Management System developed in C++.
It allows users to manage, update, and calculate grades for multiple courses using weighted averages and bonus points.

The system includes file persistence, enabling data to be saved and loaded across program executions.

---

## Features

* Update grades for multiple courses
* Assign weights to each assessment
* Calculate weighted averages
* Apply bonus points
* Display final grades (capped at 100%)
* Save and load data from a file

---

## Technologies Used

* C++
* Standard Template Library (map, vector)
* File handling (fstream)
* Input/output formatting (iomanip, sstream)

---

## Program Structure

Each course includes:

* 4 assessments
* Corresponding weights
* 2 optional bonus conditions

The final grade is calculated as:

> weighted average + bonus (maximum 100%)

---

## File Configuration

The program stores data in a file.

**Default (recommended):**

```cpp
const string GRADES_FILE = "grades.txt";
```

The file will be created and read in the same directory as the executable.

**Optional:**
You can use an absolute path if needed by modifying the constant in the source code.

---

## How to Run

1. Compile the program:

```bash
g++ main.cpp -o grades
```

2. Run the executable:

```bash
./grades
```

---

## Example Output

=== GRADES ===

COMP-1001 - Technical English
A1: 75.00% (20%)
A2: 96.50% (20%)
A3: 97.60% (25%)
A4: 0.00% (0%)
Average: 90.31%
Bonus: +0.00%
Final: 90.31%

COMP-1002 - Computer Networks
A1: 100.00% (30%)
A2: 100.00% (30%)
A3: 100.00% (30%)
A4: 0.00% (0%)
Average: 100.00%
Bonus: +0.00%
Final: 100.00%

COMP-1003 - Programming Principles
A1: 100.00% (40%)
A2: 0.00% (0%)
A3: 0.00% (0%)
A4: 0.00% (0%)
Average: 100.00%
Bonus: +5.00%
Final: 100.00%

## Academic Context

This project was developed as part of coursework at OPIT
and received positive feedback from the instructor.

---

## Author

Alessandro Benevelli

---

## Notes

This project demonstrates:

* Use of data structures (map, vector)
* File persistence
* Modular programming
* Basic input validation and user interaction
