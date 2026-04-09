# Grade Management System (C++)

## Overview

This project is a Grade Management System developed in C++.
It allows users to store, update, and calculate grades for multiple courses, including weighted averages and bonus points.

The program uses file handling to ensure data persistence between executions.

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

Each course contains:

* 4 assessments
* Corresponding weights
* 2 optional bonus conditions

The final grade is calculated as a weighted average plus bonus, with a maximum limit of 100%.

---

## File Configuration

The program uses a file to store grades.

Option 1 (default):
An absolute path is used. This must be updated according to your system.

Option 2 (recommended):
A relative path can be used:
const string GRADES_FILE = "grades.txt";

In this case, the file will be created and read in the same directory as the executable.

---

## How to Run

1. Compile the program:
   g++ main.cpp -o grades

2. Run the executable:
   ./grades

---


## Author

Alessandro Benevelli

---

## Notes

This project demonstrates the use of data structures, file persistence, modular programming, and basic error handling.
