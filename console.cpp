/**
 * Author: David Mascharka
 * Last Updated: 6 April 2017
 *
 * Runs the FYS assignment program from the command line
 */

#include <string>
#include <vector>
#include <iostream>
#include "student.h"
#include "course.h"
#include "parser.h"
#include "assign.h"

using namespace std;

int main(int argc, char* argv[]) {
    // program name and three additional arguments required
    if (argc != 4) {
        cout << "Usage: " << argv[0] << " <student file> <courses file> <save file>" << endl;
        return 1;
    }
    
    string student_file_path = argv[1]; // get the path to the student info file
    string courses_file_path = argv[2]; // get the path to the course info file
    string save_file_path = argv[3];    // get the path to save to

    // read through the students
    std::vector<student*> students = parse_student_file(student_file_path);

    // read through the courses
    std::vector<course*> courses = parse_course_file(courses_file_path);

    // try performing the assignment, throw a code if something went wrong
    if (!perform_assignment(students, courses, save_file_path)) {
        return 2;
    }
    return 0;
}
