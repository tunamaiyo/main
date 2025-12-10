# Student Grade Calculator (v0.1)

This project is a simple C++ console application that calculates final student grades.  
It uses a `Person` class, follows the Rule of Three, and allows grade calculation using  
either the average or the median of homework results.

## Basic Formula
Final grade = 0.4 * Homework + 0.6 * Exam

## Features
- Class `Person` with constructors, copy constructor, destructor, and assignment operator
- Overloaded input/output operators
- Homework stored in `std::vector<int>`
- User chooses average or median calculation
- Random grade generator option
- Reads students from `Students.txt`
- Outputs sorted results in formatted table
