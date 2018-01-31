/**
 * Author: David Mascharka
 * Last Updated: 6 April 2017
 *
 * Handles reading through the student and courses CSV files
 */

#ifndef __PARSER__
#define __PARSER__

#include "student.h"
#include "course.h"
#include <fstream>
#include <iostream>

// read through a CSV file that contains students and their FYS preferences,
// pulling out all the useful information we need
std::vector<student*> parse_student_file(string file) {
    // last name,first name,id,choice 1,choice 2,...,choice N
    std::vector<student*> ret;
    ifstream students_file_stream;

    // open the file - if there's a problem, immediately return
    students_file_stream.open(file);
    if (!students_file_stream.is_open()) {
        return ret;
    }

    string line;
    int begin_idx = 0;
    int idx;
    string last_name;
    string first_name;
    int id_number;
    int num_fys; // number of FYS picks
    while (getline(students_file_stream, line)) { // loop through the students
        begin_idx = 0;
        idx = line.find(',');
        last_name = line.substr(begin_idx, idx-begin_idx);

        begin_idx = idx + 1;
        idx = line.find(',', begin_idx);
        first_name = line.substr(begin_idx, idx-begin_idx);

        begin_idx = idx + 1;
        idx = line.find(',', begin_idx);
        id_number = stoi(line.substr(begin_idx, idx-begin_idx));

        begin_idx = idx + 1;
        idx = line.find(',', begin_idx);
        num_fys = stoi(line.substr(begin_idx, idx-begin_idx));

        student *the_student = new student(last_name, first_name, id_number);
        for (int i = 0; i < num_fys; ++i) {
            begin_idx = idx + 1;
            idx = line.find(',', begin_idx);
            if (idx == string::npos) {
                idx = line.length();
            }
            the_student->add_fys_preference(line.substr(begin_idx, idx-begin_idx));
        }
        ret.push_back(the_student);
    }
    return ret;
}

// read through a CSV file that contains a list of FYS course information,
// pulling out all the useful information we need
vector<course*> parse_course_file(string file) {
    std::vector<course*> ret;
    ifstream courses_file_stream;

    // open the file - if there's a problem, immediately return
    courses_file_stream.open(file);
    if (!courses_file_stream.is_open()) {
        return ret;
    }

    string line;
    getline(courses_file_stream, line); // throw away the header

    int begin_idx = 0;
    int idx;
    string course_number;
    int crn;
    int slots_available;
    while (getline(courses_file_stream, line)) { // loop through the courses
        begin_idx = 0;
        idx = line.find(',');
        course_number = line.substr(begin_idx, idx-begin_idx);

        begin_idx = idx + 1;
        idx = line.find(',', begin_idx);
        crn = stoi(line.substr(begin_idx, idx-begin_idx));

        begin_idx = idx + 1;
        idx = line.find(',', begin_idx);
        slots_available = stoi(line.substr(begin_idx, idx-begin_idx));

        course *the_course = new course(course_number, crn, slots_available);

        ret.push_back(the_course);
    }
    return ret;
}

#endif
