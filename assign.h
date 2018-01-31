/**
 * Author: David Mascharka
 * Last Updated: 6 April 2017
 *
 * Handles assigning students to their top FYS picks
 */

#ifndef __ASSIGN__
#define __ASSIGN__

#include <dlib/optimization/max_cost_assignment.h> // where the magic is
#include <string>
#include <vector>
#include <map>
#include <fstream>
#include "student.h"
#include "course.h"

using namespace std;
using namespace dlib;

/* assign a list of students to their top FYS picks, write those to a file
 * returns a boolean representing the success of the assignment
 */
bool perform_assignment(std::vector<student*>& students,
                        std::vector<course*>& courses,
                        string out_file_path) {
    // figure out how many total course slots are available
    int num_course_slots = 0;
    for (int i = 0; i < courses.size(); ++i) {
        num_course_slots += courses[i]->get_num_slots_available();
    }

    // need a square matrix -- set size to max(num_course_slots, num_students)
    int size = (num_course_slots > students.size() ? num_course_slots : students.size());
    
    matrix<int> cost(size, size); // initialize this to 0
    for (int i = 0; i < cost.nr(); ++i) {
        for (int j = 0; j < cost.nc(); ++j) {
            cost(i,j) = 0;
        }
    }

    // get a mapping from FYS number to CRN and from CRN to FYS number
    std::map<string, int> fys_num_to_crn;
    std::map<int, string> crn_to_fys_num;
    for (course *c : courses) {
        fys_num_to_crn.emplace(c->get_course_number(), c->get_crn());
        crn_to_fys_num.emplace(c->get_crn(), c->get_course_number());
    }

    // now we build the cost matrix, which looks like this:
    // student_1: FYS_1_slot_1_pref FYS_1_slot_2_pref ... FYS_1_slot_n_pref ... FYS_n_slot_n_pref
    // student_2: FYS_1_slot_1_pref ... FYS_n_slot_n_pref
    // ...
    // student_n: FYS_1_slot_1_pref ... FYS_n_slot_n_pref

    // the header will hold:
    // FYS_1_slot_1 ... FYS_1_slot_n FYS_2_slot_1 ... FYS_n_slot_1 ... FYS_n_slot_n
    // so we have a way to map from an index to the FYS CRN
    std::vector<int> the_fys_header;
    for (course *c : courses) {
        for (int i = 0; i < c->get_num_slots_available(); ++i) {
            the_fys_header.push_back(c->get_crn());
        }
    }

    // go through and assign numeric values for each student's preferences
    for (int student = 0; student < students.size(); ++student) {
        for (string pref : students[student]->get_fys_preferences()) {
            int crn = fys_num_to_crn[pref]; // get the CRN for a course preference

            // populate the matrix
            for (int course = 0; course < the_fys_header.size(); ++course) {
                if (the_fys_header[course] == crn) {
                    cost(student, course) = 10;
                }
            }
        }
    }

    // assign placeholder students to prefer every FYS until the matrix is full
    if (students.size() < num_course_slots) {
        for (int i = students.size(); i < num_course_slots; ++i) {
            for (int j = 0; j < num_course_slots; ++j) {
                cost(i,j) = 5;
            }
        }
    }

    // perform the assignment
    std::vector<long> assignment = max_cost_assignment(cost);

    // write the assignment to a CSV file
    ofstream output_file(out_file_path);
    output_file << "Last Name, First Name, ID, FYS Course Number, CRN" << endl;
    for (int i = 0; i < students.size(); ++i) {
        output_file << students[i]->get_last_name() << ", " << students[i]->get_first_name()
                    << ", " << students[i]->get_id_number() << ", ";

        // figure out if the assignment is alright (matched one of their picks)
        bool assignment_alright = false;
        int assigned_crn = the_fys_header[assignment[i]];
        for (string pref : students[i]->get_fys_preferences()) {
            if (assigned_crn == fys_num_to_crn[pref]) {
                assignment_alright = true;
                break;
            }
        }

        // if the student got assigned to one of their top picks, write that
        // otherwise, indicate we did not handle the assignment
        if (assignment_alright) {
            output_file << crn_to_fys_num[assigned_crn] << ", " << assigned_crn;
        } else {
            output_file << "NOT ASSIGNED, NOT ASSIGNED";
        }
        output_file << endl;
    }
    output_file.close();

    return true;
}

#endif
